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
#include "IInstrumentDefinition.hpp"
#include "InstrumentRuleFactory.hpp"
#include "InstrumentFactory.hpp"
#include "IRules.hpp"
#include "Rules/PSU1Rules.hpp"

using namespace std;
using namespace boost;

class RadarPulseGenerator: public IInstrumentDefinition{

  typedef vector<string> TokenVector;
  TokenVector tokens_;

  void StripToken(string& token){
      //remove all whitespace and comments 
      replace_all(token," ","");
      to_lower(token);
      int idx = token.find("#");
      token = token.substr(0,idx);
  }

public:

  void WriteIIF(){ cout << "writing output file" << endl;}
  
  IRules* GetRules(const string& fileName){
    
    string transmitter;
    string buffer;

    ifstream in(fileName.c_str());

    if(!in) throw runtime_error("RadarPulseGenerator::GetRules - Could not open" + fileName);
    
    while(!in.eof()){
      getline(in,buffer);

      StripToken(buffer);

      if(buffer.find("rules") != string::npos){
	int idx = buffer.find("=");
	transmitter = buffer.substr(idx+1,buffer.length());
      }
    }
    return InstrumentRuleFactory::Instance().Create(transmitter);
  }

  //custom tokenizer for RPG Rules
  const TokenVector& Tokenize(const string& fileName){
    string buffer;
    ifstream in(fileName.c_str());

    if(!in) throw runtime_error("FindInstrument:: Could not open" + fileName);
    
    while(!in.eof()){
      getline(in,buffer);
      
      StripToken(buffer);

      if(buffer.find("instrument")==string::npos && 
	 buffer.find("rules")==string::npos &&
	 buffer[0]!='\n' && !buffer.empty()){
	tokens_.push_back(buffer);
      }
    }

    return tokens_;
  }


};

//using anonymous namespace to register callback with factory
namespace RPG
{
  //static callback for factory registration
  IInstrumentDefinition* Callback(){
    return new RadarPulseGenerator();
  }

  const string id = "rpg";
  bool result = InstrumentFactory::Instance().RegisterInstrument(id,Callback);
}


#endif
