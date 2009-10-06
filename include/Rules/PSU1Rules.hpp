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
#ifndef PSU1RULES_H
#define PSU1RULES_H

#include "../Keywords.hpp"
#include "../Unit.hpp"
#include "../Location.hpp"
#include "../IRules.hpp"
#include "../InstrumentRuleFactory.hpp"

#include <boost/dynamic_bitset.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/bind.hpp>
#include <vector>
#include <iostream>

using namespace std;
using namespace boost::spirit::classic;
using namespace boost;

class PSU1Rules: public IRules{
  typedef dynamic_bitset<> Pattern;
  typedef vector<Pattern> PatternVector;

  PatternVector ports_;

  //due to spirit rules non-copy problem, we can't simply
  //create a vector here.
  TRKeyword      trKey;
  TXAKeyword     txaKey;
  CODEKeyword    codeKey;
  GenericKeyword gKey;
  TYPE1Keyword   t1Key;
  TYPE2Keyword   t2Key;
  SAKeyword      saKey;

  template<typename T>
  const T FindParam(const ParameterVector& pv, const string& id){
    ParameterVector::const_iterator iter = 
      std::find_if(pv.begin(), pv.end(), 
		   bind(&Parameter::id, _1) == id);
    if(iter == pv.end()) throw std::runtime_error("Parameter " + id + " could not be found");
    return any_cast<T>(iter->value);
  }

  const int GetChOffset(const LocationVector& lv, const int& chNum){
    return lv[chNum].channel + ((lv[chNum].port == 'a') ? 0 : 16);
  }

public:

  PSU1Rules(): ports_(32){};

  void Detect(const TokenVector& tv);
  const bool Verify();

  ~PSU1Rules(){
    InstrumentRuleFactory::Instance().UnregisterRule("psu1");
  }
};


#endif  

