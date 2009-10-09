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
#ifndef RADAR_PULSE_GENERATOR_H
#define RADAR_PULSE_GENERATOR_H

#include <iostream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <bpg-v2/Instruments/Rpg/RpgIIF.hpp>
#include <bpg-v2/Common/IInstrumentDefinition.hpp>
#include <bpg-v2/Common/InstrumentRuleFactory.hpp>
#include <bpg-v2/Common/InstrumentFactory.hpp>

class IRules;
class RpgRules;

class RadarPulseGenerator: public IInstrumentDefinition{

  RpgIIF iif_;
  std::string transmitter_;
  RpgRules* rules_;

  void StripToken(std::string& token){
    //remove all whitespace and comments 
    boost::replace_all(token," ","");
    boost::to_lower(token);
    int idx = token.find("#");
    token = token.substr(0,idx);
  }

  IRules& GetRules(const std::string& fileName);
  void WriteIIF(const std::string& fileName);
  
  //custom tokenizer for RPG Rules
  void Tokenize(const std::string& fileName);

public:
  
  ~RadarPulseGenerator(){
    delete rules_;
    InstrumentFactory::Instance().UnregisterInstrument("rpg");
  }

};
#endif
