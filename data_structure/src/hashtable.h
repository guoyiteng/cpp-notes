#pragma once

#include <memory>
#include <list>
#include <functional>
#include <exception>
#include <optional>

template<typename K, typename V>
class hashtable {
public:
    hashtable(size_t initNumBuckets, float load_factor)
            : _numOfBuckets(initNumBuckets),
              _buckets(std::make_unique<std::list<std::pair<K, V>>[]>(initNumBuckets)),
              _size(0), _load_factor(load_factor) {}

    hashtable(size_t initNumBuckets): hashtable(initNumBuckets, 1.5) {}

    size_t size() const {
        return _size;
    }

    bool isEmpty() const {
        return _size == 0;
    }

    bool containsKey(const K& key) const {
        size_t hashed = _keyHash(key);
        size_t bucketIdx = hashed % _numOfBuckets;
        for (const std::pair<K, V> &pair : _buckets[bucketIdx]) {
            if (pair.first == key) {
                return true;
            }
        }
        return false;
    }

    bool containsValue(const V& val) const {
        for (size_t bucketIdx = 0; bucketIdx < _numOfBuckets; ++bucketIdx) {
            for (const std::pair<K, V> &pair : _buckets[bucketIdx]) {
                if (pair.second == val) {
                    return true;
                }
            }
        }
        return false;
    }

    const V &get(const K& key) const {
        size_t hashed = _keyHash(key);
        size_t bucketIdx = hashed % _numOfBuckets;
        for (const std::pair<K, V> &pair : _buckets[bucketIdx]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        throw std::out_of_range("no such an element");
    }

    V &operator[](const K &key) {
        rehash();
        size_t hashed = _keyHash(key);
        size_t bucketIdx = hashed % _numOfBuckets;
        for (std::pair<K, V> &pair : _buckets[bucketIdx]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        _buckets[bucketIdx].push_back(std::make_pair(key, V()));
        ++_size;
        return _buckets[bucketIdx].back().second;
    }

    std::optional<V> put(const K &key, const V &val) {
        rehash();
        size_t hashed = _keyHash(key);
        size_t bucketIdx = hashed % _numOfBuckets;
        std::optional<V> result;
        for (std::pair<K, V> &pair : _buckets[bucketIdx]) {
            if (pair.first == key) {
                result = pair.second;
                pair.second = val;
            }
        }
        if (!result) {
            _buckets[bucketIdx].push_back(std::make_pair(key, val));
            ++_size;
        }
        return result;
    }

    std::optional<V> remove(const K &key) {
        size_t hashed = _keyHash(key);
        size_t bucketIdx = hashed % _numOfBuckets;
        std::optional<V> result;
        typename std::list<std::pair<K, V>>::iterator iter = _buckets[bucketIdx].begin();
        while (iter != _buckets[bucketIdx].end()) {
            if (iter->first == key) {
                result = iter->second;
                _buckets[bucketIdx].erase(iter);
                _size--;
                break;
            }
            iter++;
        }
        return result;
    }

    template<typename Ko, typename Vo>
    void putAll(const hashtable<Ko, Vo> &other) {
        for (size_t bucketIdx = 0; bucketIdx < other._numOfBuckets; ++bucketIdx) {
            for (const std::pair<K, V> &pair : other._buckets[bucketIdx]) {
                put(pair.first, pair.second);
            }
        }
    }

    void clear() {
        for (size_t bucketIdx = 0; bucketIdx < _numOfBuckets; ++bucketIdx) {
            _buckets[bucketIdx].clear();
        }
        _size = 0;
    }


private:
    std::unique_ptr<std::list<std::pair<K, V>>[]> _buckets;
    std::hash<K> _keyHash;
    size_t _size;
    size_t _numOfBuckets;
    float _load_factor;

    template <typename, typename>
    friend class hashtable;

    void rehash() {
        if (_size > _numOfBuckets * _load_factor) {
            std::unique_ptr<std::list<std::pair<K, V>>[]> oldBuckets = std::move(_buckets);
            size_t oldNumOfBuckets = _numOfBuckets;
            _buckets = std::make_unique<std::list<std::pair<K, V>>[]>(oldNumOfBuckets * 2);
            _numOfBuckets = oldNumOfBuckets * 2;
            clear();
            for (size_t bucketIdx = 0; bucketIdx < oldNumOfBuckets; ++bucketIdx) {
                for (std::pair<K, V> &pair : oldBuckets[bucketIdx]) {
                    put(pair.first, pair.second);
                }
            }
        }
    }
};