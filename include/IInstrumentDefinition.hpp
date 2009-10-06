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
#ifndef IINSTRUMENT_DEFINITION_H
#define IINSTRUMENT_DEFINITION_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <boost/algorithm/string.hpp>

#include "IRules.hpp"
//#include "PSU1Rules.hpp"

using std::vector;
//using namespace boost;

//Rule interface
class IInstrumentDefinition{

public:
  typedef vector<string> TokenVector;

  virtual void WriteIIF()=0;
  virtual IRules& GetRules(const string& fileName)=0;
  virtual const TokenVector& Tokenize(const string& fileName)=0; 
  virtual ~IInstrumentDefinition(){};
};

#endif
