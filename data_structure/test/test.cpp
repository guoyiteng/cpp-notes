#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE my_unit_tests
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "hashtable.h"

BOOST_AUTO_TEST_SUITE(my_testsuite)

    BOOST_AUTO_TEST_CASE(ht1)
    {
        hashtable<int, int> ht(1);
        ht.put(1, 10);
        ht.put(2, 20);
        BOOST_CHECK_EQUAL(ht.get(1), 10);
        BOOST_CHECK_EQUAL(ht.get(2), 20);
        ht[3] = 30;
        int a = ht[4];
        BOOST_CHECK_EQUAL(ht.get(3), 30);
        BOOST_CHECK_EQUAL(ht.get(4), 0);
        BOOST_CHECK_EQUAL(ht[5], 0);
        BOOST_CHECK_EQUAL(ht.size(), 5);
        hashtable<double, double> htd(1);
        htd.putAll(ht);
        BOOST_CHECK_EQUAL(htd.size(), 5);
        BOOST_CHECK_EQUAL(htd[1], 10);
    }

BOOST_AUTO_TEST_SUITE_END()