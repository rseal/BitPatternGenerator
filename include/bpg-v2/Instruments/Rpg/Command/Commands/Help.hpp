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
#ifndef HELP_H
#define HELP_H

#include <bpg-v2/Instruments/Rpg/Console/Console.hpp>
#include <bpg-v2/Instruments/Rpg/Command/CommandArray.hpp>
#include <iostream>

typedef ColorConsole CC;

///\brief Print a list of commands and their usage.                           
class Help: public Command{
  CommandArray& commands_;
  Console& console_;
public:
  Help(const std::string& name, const std::string& description, CommandArray& commands,
       Console& console):
    Command(name,description), commands_(commands), console_(console){};
  virtual ~Help(){};
  virtual void Execute();
};


void Help::Execute(){
  console_.SystemPrompt("[HELP] ");
  console_.Write("Commands are as follows:\n", CC::SYSTEM,true);
  std::vector<std::string> names = commands_.Names();
  std::vector<std::string>::const_iterator iter = names.begin();
  while(iter != names.end()){
    console_.Write(*iter,CC::SYSTEM);
    ++iter;
  }
}  


#endif
