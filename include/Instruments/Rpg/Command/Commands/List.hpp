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
#ifndef LIST_H
#define LIST_H

#include <bpg-v2/Instruments/Rpg/Mode/ModeArray.hpp>
#include <bpg-v2/Instruments/Rpg/Console/Console.hpp>
#include <iostream>
#include <boost/lexical_cast.hpp>

typedef ColorConsole CC;

class List: public Command
{
  ModeArray& modeArray_;
  Console& console_;
    
public:
  List(const std::string& name, const std::string& description, ModeArray& modeArray,
       Console& console): 
    Command(name,description), modeArray_(modeArray), console_(console){};

  virtual ~List() {};
  virtual void Execute();
};

void List::Execute(){
  int idx=0;
  console_.SystemPrompt("[LIST] ");
  console_.Write("Loaded Modes: \n",CC::SYSTEM,true);
  std::vector<std::string> names = modeArray_.Names();
  console_.SystemPrompt();
  for(int i=0; i<names.size(); ++i){
    console_.Write(CC::YELLOW, "[" + boost::lexical_cast<std::string>(i) + "] ");
    console_.Write(CC::WHITE, names[i] + (i==names.size()-1 ? "" : ", "));
  }
  console_.Write(CC::WHITE,"\n");
}

#endif
