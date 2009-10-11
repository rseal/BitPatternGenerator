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
#include <bpg-v2/Rules/Arecibo/Keywords/Type1.hpp>
#define BOOST_TEST_MODULE Type1KeywordTest
#include <boost/test/included/unit_test.hpp>
#include <boost/any.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/bind.hpp>
#include <memory>


using namespace std;

void Print(const Location& loc){ cout << loc.port << " " << loc.channel << endl;}

BOOST_AUTO_TEST_CASE(type1_keyword_test){
  
  Type1Keyword t1Key;
  ParameterVector t1Tuple;
  LocationVector lv;
  
  t1Key.Process("TXIPP = a.1,a.2,b.3,a.8");
  BOOST_CHECK(t1Key.Set() == true);
  t1Tuple = t1Key.GetTupleRef();
  lv = boost::any_cast<LocationVector>(param::FindParameter(t1Tuple,"txipp").value);
  for_each(lv.begin(), lv.end(), boost::bind(Print,_1));

  t1Key.Process("RXIPP = a.4,a.5,b.6,b.7");
  BOOST_CHECK(t1Key.Set() == true);
  t1Tuple = t1Key.GetTupleRef();
  lv = boost::any_cast<LocationVector>(param::FindParameter(t1Tuple,"rxipp").value);
  for_each(lv.begin(), lv.end(), boost::bind(Print,_1));

  t1Key.Process("R  f = a.8,a.9,a.10,b.11,b.12");
  BOOST_CHECK(t1Key.Set() == true);
  t1Tuple = t1Key.GetTupleRef();
  lv = boost::any_cast<LocationVector>(param::FindParameter(t1Tuple,"rf").value);
  for_each(lv.begin(), lv.end(), boost::bind(Print,_1));

  t1Key.Process("IF = a.11,a.12,a.13,b.14,b.15");
  BOOST_CHECK(t1Key.Set() == false);
  
  BOOST_CHECK(true);
}
