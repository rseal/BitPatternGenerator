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

#include <bpg-v2/Common/InstrumentFactory.hpp>

using namespace std;
using namespace boost;

//Rule interface
struct InstrumentFinder{

  string instrument_;
  typedef vector<string> TokenVector;
  typedef string File;
  TokenVector tokens_;
  
public:

  IInstrumentDefinition& Find(const File& fileName);

  ~InstrumentFinder(){
    InstrumentFactory::Instance().UnregisterInstrument(instrument_);
  }
};

#endif
