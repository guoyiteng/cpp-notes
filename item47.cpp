struct input_iterator_tag {};
struct forward_iterator_tag: public input_iterator_tag {};
struct bidirectional_iterator_tag: public forward_iterator_tag {};
struct random_access_iterator_tag: public bidirectional_iterator_tag {};

template <typename IterT>
struct iterator_traits {
    using iterator_category = typename IterT::iterator_category;
};

template <typename T>
struct iterator_traits<T*> { // partial template specialization
    using iterator_category = random_access_iterator_tag;
};

class array {
public:
    class iterator {
    public:
        using iterator_category = random_access_iterator_tag;
    };
};

class list {
public:
    class iterator {
    public:
        using iterator_category = bidirectional_iterator_tag;
    };
};

// use function overloading to distinguish between different tags.
template <typename IterT>
void doAdvance(IterT& iter, int dist, random_access_iterator_tag) {
}

template <typename IterT>
void doAdvance(IterT& iter, int dist, bidirectional_iterator_tag) {
}

template <typename IterT>
void advance(IterT& iter, int dist) {
    doAdvance(iter, dist, typename iterator_traits<IterT>::iterator_category());
}
