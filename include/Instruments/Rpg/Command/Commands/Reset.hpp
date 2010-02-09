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
#ifndef RESET_H
#define RESET_H

#include <bpg-v2/Instruments/Rpg/ControlStatus.hpp>
#include <bpg-v2/Instruments/Rpg/Console/Console.hpp>

typedef ColorConsole CC;

class Reset: public Command
{
  ControlStatus& controlStatus_;
  Console& console_;

public:
  Reset(const std::string& name, const std::string& description,
	ControlStatus& controlStatus, Console& console): 
    Command(name,description),controlStatus_(controlStatus),
    console_(console) {
    argMap_["set"]   = ControlStatus::SET;
    argMap_["clear"] = ControlStatus::CLEAR;
  }

  virtual void Execute();

};

void Reset::Execute(){
    std::string method;

    console_.SystemPrompt("[RESET] ");
    console_.UserPrompt("[RESET] ");

    if(Interact()){
      console_.Write("Which method (clear, set) ?\n", CC::SYSTEM);
      console_.UserPrompt();
      std::getline(std::cin,method);
      boost::erase_all(method," ");
    }
    else method = argList_[0];

    ArgMap::iterator iter = argMap_.find(method);
	
    if(iter != argMap_.end())
      controlStatus_.Control(ControlStatus::RESET, ControlStatus::PORTAB, iter->second);
    else
      console_.Write("Invalid request\n", CC::SYSTEM);
  }

#endif
