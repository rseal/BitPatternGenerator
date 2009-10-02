#include "../include/Keywords.hpp"

#define BOOST_TEST_MODULE TRKeywordTest
#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <functional>

using namespace std;


BOOST_AUTO_TEST_CASE(tr_keyword_test){

  KeywordVector   keyVector;
  ParameterVector pm;

  TRKeyword key1;
  key1.Process("TR = a.1,a.2,b.3, (10 usec, 14 usec)");
  key1.Print();
  keyVector.push_back(key1);

  TXAKeyword key2;
  key2.Process("TXA = a.1,a.2,b.3, 160 usec");
  key2.Print();
  keyVector.push_back(key2);

  CODEKeyword key3;
  key3.Process("CODE = a.1,b.2,b.3, {+5 -2 +2 -1 +1 -1 +1}");
  key3.Print(); 
  keyVector.push_back(key3);

  SAKeyword key4;
  key4.Process("SA0 = a.1,a.2,a.3, (100 km, 120 km)");
  key4.Print();
  keyVector.push_back(key4);

  GenericKeyword key5;
  key5.Process("a.15 = {+100 -10 +20 -5}");
  key5.Print();
  keyVector.push_back(key5);

  TYPE1Keyword key6;
  key6.Process("BAUD = 100 usec");
  key6.Print();
  keyVector.push_back(key6);

  TYPE2Keyword key7;
  key7.Process("mode=normal");
  key7.Print();
  keyVector.push_back(key7);
  
  vector<Keyword>::iterator iter = keyVector.begin();
  
  while(iter != keyVector.end()){
    cout << "name = " << (*iter)() << endl;
    if( iter->Match("type2")) 
      break;
    ++iter;
  }

  if(iter != keyVector.end()){
    cout << "found it!" << endl;
    pm = iter->GetParameterRef();
  }

  for(int i=0; i<pm.size(); ++i)
    cout << pm[i].id << endl;

  
  BOOST_CHECK(key7.Match("type2") == true);
}
