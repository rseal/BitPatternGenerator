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
#ifndef ARECIBO_RULES_H
#define ARECIBO_RULES_H

#include <boost/any.hpp>
#include <boost/bind.hpp>
#include <bpg-v2/Common/InstrumentRuleFactory.hpp>
#include <bpg-v2/Rules/Arecibo/Keywords.hpp>
#include <bpg-v2/Common/Parameter.hpp>
#include <bpg-v2/Instruments/Rpg/RpgRules.hpp>

namespace arecibo{

  class Rules: public RpgRules{
    
    //due to spirit rules non-copy problem, we can't simply
    //create a vector here.
    PhaseKeyword phaseKey;
    BaudwidthKeyword bwKey;
    Type1Keyword t1Key;
    Type2Keyword t2Key;
    Type3Keyword t3Key;
    GenericKeyword gKey;
    SAKeyword      saKey;

    int ChIndex(const LocationVector& lv, const int& chNum){
      return lv[chNum].channel + ((lv[chNum].port == 'a') ? 0 : 16);
    }

    //protected:
    void Detect(const TokenVector& tv);

    bool Verify();

    void Build() { 
      std::cout << "BUILDING SIGNALS" << std::endl;
    }

  public:

    ~Rules(){
      InstrumentRuleFactory::Instance().UnregisterRule("arecibo");
    }

  }; //class Rules

}; //namespace arecibo

#endif  

