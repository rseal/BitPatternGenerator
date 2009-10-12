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

#include <boost/any.hpp>
#include <boost/bind.hpp>
#include <bpg-v2/Common/InstrumentRuleFactory.hpp>
#include <bpg-v2/Rules/PSU/Type1/Keywords.hpp>
#include <bpg-v2/Common/Parameter.hpp>
#include <bpg-v2/Instruments/Rpg/RpgRules.hpp>

class PSU1Rules: public RpgRules{

  //due to spirit rules non-copy problem, we can't simply
  //create a vector here.
  TRKeyword      trKey;
  TXAKeyword     txaKey;
  CODEKeyword    codeKey;
  GenericKeyword gKey;
  TYPE1Keyword   t1Key;
  TYPE2Keyword   t2Key;
  SAKeyword      saKey;

  const int ChIndex(const LocationVector& lv, const int& chNum){
    return lv[chNum].channel + ((lv[chNum].port == 'a') ? 0 : 16);
  }

  //protected:
  void Detect(const TokenVector& tv);

  const bool Verify();

  void Build() { 
    std::cout << "BUILDING SIGNALS" << std::endl;
  }

public:

  ~PSU1Rules(){
    InstrumentRuleFactory::Instance().UnregisterRule("psu1");
  }
};


#endif  

