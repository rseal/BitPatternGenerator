// Copyright (c) 2009 Ryan Seal <rlseal -at- gmail.com>
//
// This file is part of Bit Pattern Generator (BPG) Software.
//
// BPG is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//  
// BPG is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with BPG.  If not, see <http://www.gnu.org/licenses/>.
#include "../include/Signal.hpp"
#define BOOST_TEST_MODULE SignalTest
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(signal_test){

  Signal signal1("sig1");
  
  BOOST_CHECK(signal1.Name() == "sig1");
  BOOST_CHECK(signal1.Set() == true);
}
