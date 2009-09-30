#include "../include/Keyword.hpp"
#define BOOST_TEST_MODULE KeywordTest
#include <boost/test/included/unit_test.hpp>

#include <iostream>

BOOST_AUTO_TEST_CASE(keyword_test){

  Keyword key1("key1");
  BOOST_CHECK(key1.Set() == true);
  //key1.Required(true);
  //BOOST_CHECK(key1.Required() == true);
  BOOST_CHECK_EQUAL("key1",key1.Name());
  key1.Name("key2");
  BOOST_CHECK_EQUAL("key2",key1.Name());
}
