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

#include <fstream>
#include <stdexcept>
#include <boost/algorithm/string.hpp>
#include <bpg-v2/Common/IInstrumentDefinition.hpp>
#include <bpg-v2/Common/InstrumentFactory.hpp>
#include <bpg-v2/Common/InstrumentFinder.hpp>


using namespace std;
using namespace boost;

IInstrumentDefinition& InstrumentFinder::Find(const File& fileName) {

  bool found = false;
  string buffer;
  ifstream in(fileName.c_str());
  
  if(!in) throw runtime_error("FindInstrument:: Could not open " + fileName);
  
  while(!in.eof() && !found){
    getline(in,buffer);

    //remove all whitespace from the input string
    replace_all(buffer," ","");
    to_lower(buffer);
    int idx = buffer.find("#");
    buffer = buffer.substr(0,idx);
      
    if(buffer.find("instrument") != string::npos){
      int idx = buffer.find("=");
      instrument_ = buffer.substr(idx+1,buffer.length());
      found = true;
    }
  }

  if(!found) throw runtime_error("FindInstrument:: Could not locate " + instrument_ + " Instrument");

  return *InstrumentFactory::Instance().Create(instrument_);
}
