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
#ifndef SYNC_H
#define SYNC_H

#include <bpg-v2/Instruments/Rpg/ControlStatus.hpp>
#include <bpg-v2/Instruments/Rpg/Console/Console.hpp>
#include <iostream>

typedef ColorConsole CC;

class Sync: public Command{
  ControlStatus& controlStatus_;
  Console& console_;
public:
  explicit Sync(const std::string& name, const std::string& description,
		ControlStatus& controlStatus, Console& console): 
    Command(name,description),controlStatus_(controlStatus),
    console_(console){
    argMap_["int"]   = ControlStatus::INT_SYNC;
    argMap_["1pps"]  = ControlStatus::PPS1_SYNC;
    argMap_["10pps"] = ControlStatus::PPS10_SYNC;
    argMap_["ext"]   = ControlStatus::EXT_SYNC;
  }

  virtual void Execute();

};


void Sync::Execute(){
  std::string type;

  console_.SystemPrompt("[SYNC] ");
  console_.UserPrompt("[SYNC] ");
	
  if(Interact()){
    console_.Write("Set sync source (int, 1pps, 10pps, ext)\n", CC::SYSTEM);
    console_.UserPrompt();
    //modified to properly read entire line
    std::getline(std::cin,type);
    boost::erase_all(type," ");
  }
  else type = argList_[0];
	
  ArgMap::iterator iter = argMap_.find(type);
  if(iter != argMap_.end())
    controlStatus_.Sync(iter->second);
  else
    console_.Write("Invalid request\n", CC::SYSTEM); 
}


#endif
