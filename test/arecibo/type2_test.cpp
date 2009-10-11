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
#include <bpg-v2/Rules/Arecibo/Keywords/Type2.hpp>
#define BOOST_TEST_MODULE Type1KeywordTest
#include <boost/test/included/unit_test.hpp>
#include <boost/any.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/bind.hpp>
#include <memory>


using namespace std;

void Print(const Location& loc){ cout << loc.port << " " << loc.channel << endl;}

BOOST_AUTO_TEST_CASE(type2_keyword_test){
  
  Type2Keyword t2Key;
  ParameterVector t2Tuple;
  LocationVector lv;
  
  t2Key.Process("REFCLK = 20 MHz");
  BOOST_CHECK(t2Key.Set() == true);
  t2Tuple = t2Key.GetTupleRef();
  const float refclk = boost::any_cast<float>(
					      param::FindParameter(t2Tuple,"refclk").value
					      );
  cout << "refclk = " << refclk << endl;

  t2Key.Process("IPP = 20 msec");
  BOOST_CHECK(t2Key.Set() == true);
  t2Tuple = t2Key.GetTupleRef();
  const float ipp = boost::any_cast<float>(
					   param::FindParameter(t2Tuple,"ipp").value
					   );
  cout << "ipp = " << ipp << endl;

  t2Key.Process("REFIPP = 20 msec");
  BOOST_CHECK(t2Key.Set() == false);
  
  BOOST_CHECK(true);
}
