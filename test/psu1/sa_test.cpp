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
#include <bpg-v2/Rules/PSU/Type1/SAKeyword.hpp>
#define BOOST_TEST_MODULE SATest
#include <boost/test/included/unit_test.hpp>
#include <boost/any.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/bind.hpp>
#include <memory>


using namespace std;
using namespace psu1;

void Print(const Location& loc){ cout << loc.port << " " << loc.channel << endl;}

BOOST_AUTO_TEST_CASE(sa_keyword_test){

   SAKeyword saKey;

   saKey.Process("SA0 = a.5,a.6,   (70 km, 140 km)");
   BOOST_CHECK(saKey.Set() == true);
   const SaTuple& saTuple = saKey.GetTupleRef()[0];
   LocationVector lv = saTuple.get<0>();
   const int sz = lv.size();
   const bool negate = saTuple.get<1>();
  const float h0 = saTuple.get<2>();
  const float hf = saTuple.get<3>();
   for(int i=0; i<sz; ++i){
      lv[i].Print(cout);
   }
  cout << "SA Window negation = " << negate << endl;
  cout << "H0 = " << h0 << " HF = " << hf << endl;
}
