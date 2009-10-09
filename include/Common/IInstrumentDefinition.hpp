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

#include <bpg-v2/Common/IRules.hpp>
#include <boost/algorithm/string.hpp>

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <cassert>

//Nonvirtual Instrument Definition Interface
class IInstrumentDefinition{
  
  typedef std::vector<std::string> TokenVector;

protected:
  TokenVector tokens_;
  
  //Custom Rule sets
  virtual IRules& GetRules(const std::string& fileName)=0;
  //Custom configuration file writer
  virtual void WriteIIF(const std::string& fileName)=0;
  //Custom HIF Tokenizer
  virtual void Tokenize(const std::string& fileName)=0; 

public:
  virtual ~IInstrumentDefinition(){};

  //The Init() function is the only member exposed
  //All customization is encapsulated in the private virtual members
  const bool Init(const std::string& inFile, const std::string& outFile){
    IRules& rules = GetRules(inFile);

    if(inFile == outFile) throw std::runtime_error(inFile + " == " + outFile);

    //    assert(inFile != outFile);
    
    Tokenize(inFile);
    rules.Init(tokens_);
    WriteIIF(outFile);
    return true;
  }    
};

#endif
