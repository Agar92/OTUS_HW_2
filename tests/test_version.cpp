/*
#define BOOST_TEST_MODULE test_version

#include "lib.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_version)

BOOST_AUTO_TEST_CASE(test_valid_version)
{
    BOOST_CHECK(version() != 100);
}

BOOST_AUTO_TEST_SUITE_END()
*/
#include <iostream>
#include <gtest/gtest.h>
#include <MakeIP/makeip.h>
#include <version/lib.h>

TEST(TEST_GOOGLETEST, Test1)
{
    std::cout<<"version="<<version()<<std::endl;

    ASSERT_NE(version(), 100);
    ASSRRT_EQ(10,5*2);
}
