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
#include <bpg-v2/Rules/PSU/Type1/Keywords.hpp>
#define BOOST_TEST_MODULE TRKeywordTest
#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include <functional>

using namespace std;
using namespace psu1;

BOOST_AUTO_TEST_CASE(tr_keyword_test){

  //  typedef vector<Keyword> KeywordVector;
  //  KeywordVector   keyVector;
  ParameterVector pm;

  TRKeyword key1;
  key1.Process("TR = a.1,a.2,b.3, (10 usec, 10 usec)");
  key1.Print();
  //keyVector.push_back(key1);

  TXAKeyword key2;
  key2.Process("TXA = a.1,a.2,b.3, 140 usec");
  key2.Print();
  //keyVector.push_back(key2);

  CODEKeyword key3;
  key3.Process("CODE = a.1,b.2,b.3, {+5 -2 +2 -1 +1 -1 +1}");
  key3.Print(); 
  //keyVector.push_back(key3);

  SAKeyword key4;
  key4.Process("SA0 = a.1,a.2,a.3, (100 km, 120 km)");
  key4.Print();
  //keyVector.push_back(key4);

  GenericKeyword key5;
  key5.Process("a.15 = {+100 -10 +20 -5}");
  key5.Print();
  //keyVector.push_back(key5);

  TYPE1Keyword key6;
  key6.Process("BAUD = 100 usec");
  key6.Print();
  //keyVector.push_back(key6);

  TYPE2Keyword key7;
  key7.Process("mode=normal");
  key7.Print();
  //keyVector.push_back(key7);
  
  // vector<Keyword>::iterator iter = keyVector.begin();
  
  // while(iter != keyVector.end()){
  //   cout << "name = " << (*iter)() << endl;
  //   if( iter->Match("type2")) 
  //     break;
  //   ++iter;
  // }

  // if(iter != keyVector.end()){
  //   cout << "found it!" << endl;
  //   pm = iter->GetParameterRef();
  // }

  // for(int i=0; i<pm.size(); ++i)
  //   cout << pm[i].id << endl;

  
  BOOST_CHECK(key7.Set() == true);
}
