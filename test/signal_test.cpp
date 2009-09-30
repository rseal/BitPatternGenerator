#include "../include/Signal.hpp"
#define BOOST_TEST_MODULE SignalTest
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(signal_test){

  Signal signal1("sig1");
  
  BOOST_CHECK(signal1.Name() == "sig1");
  BOOST_CHECK(signal1.Set() == true);
}
