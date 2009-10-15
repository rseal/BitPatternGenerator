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
#include <bpg-v2/Rules/Arecibo/Keywords/Type3.hpp>
#define BOOST_TEST_MODULE Type3KeywordTest
#include <boost/test/included/unit_test.hpp>
#include <boost/any.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/bind.hpp>
#include <memory>


using namespace std;
using namespace arecibo;

void Print(const Location& loc){ cout << loc.port << " " << loc.channel << endl;}

BOOST_AUTO_TEST_CASE(type3_keyword_test){
  
  Type3Keyword t3Key;
  ParameterVector t3Tuple;
  LocationVector lv;
  
  t3Key.Process("beam = a.1,a.2,a.3, 150 usec");
  BOOST_CHECK(t3Key.Set() == true);
  t3Tuple = t3Key.GetTupleRef();
  const float beam = boost::any_cast<Type3Tuple>(
					    param::FindParameter(t3Tuple,"beam").value
						 ).get<1>();
  cout << "beam = " << beam << endl;

  t3Key.Process("txwin = a.4,a.5,a.6, 20 samples");
  BOOST_CHECK(t3Key.Set() == true);
  t3Tuple = t3Key.GetTupleRef();
  const float txwin = boost::any_cast<Type3Tuple>(
  					   param::FindParameter(t3Tuple,"txwin").value
						).get<1>();
  cout << "txwin = " << txwin << endl;

  //should fail
  t3Key.Process("REFIPP = 20 msec");
  BOOST_CHECK(t3Key.Set() == false);
  
  BOOST_CHECK(true);
}
