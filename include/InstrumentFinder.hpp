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
#ifndef INSTRUMENT_FINDER_H
#define INSTRUMENT_FINDER_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <boost/algorithm/string.hpp>
#include "InstrumentFactory.hpp"

//#include "IRules.hpp"
//#include "PSU1Rules.hpp"

using namespace std;
using namespace boost;

//Rule interface
class InstrumentFinder{

  typedef vector<string> TokenVector;
  typedef string File;
  TokenVector tokens_;
  
public:

  IInstrumentDefinition* FindInstrument(const File& fileName){
    string instrument;
    string buffer;

    ifstream in(fileName.c_str());

    if(!in) throw runtime_error("FindInstrument:: Could not open " + fileName);
    
    while(!in.eof()){
      getline(in,buffer);

      //remove all whitespace from the input string
      replace_all(buffer," ","");
      to_lower(buffer);
      int idx = buffer.find("#");
      buffer = buffer.substr(0,idx);

      if(buffer.find("instrument") != string::npos){
	int idx = buffer.find("=");
	instrument = buffer.substr(idx+1,buffer.length());
      }
    }
    return InstrumentFactory::Instance().Create(instrument);
  }

  //virtual void WriteIIF()=0;
};

#endif
