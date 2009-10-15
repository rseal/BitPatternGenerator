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
#include <bpg-v2/Rules/Arecibo/Keywords/Baudwidth.hpp>
#define BOOST_TEST_MODULE BaudwidthTest
#include <boost/test/included/unit_test.hpp>
#include <boost/any.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/bind.hpp>
#include <memory>


using namespace std;
using namespace arecibo;

void Print(const Location& loc){ cout << loc.port << " " << loc.channel << endl;}

BOOST_AUTO_TEST_CASE(type3_keyword_test){
  
  BaudwidthKeyword baudKey;
  vector<BaudwidthTuple> baudTuple;
  
  baudKey.Process("baudwidth = 10 usec, 10 usec");
  BOOST_CHECK(baudKey.Set() == true);
  baudTuple = boost::any_cast<vector<BaudwidthTuple> >(baudKey.GetTupleRef());
  cout << "baudwidth = " << baudTuple[0].get<0>() << " , " << baudTuple[0].get<1>() << endl;
}
