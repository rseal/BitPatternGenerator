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
#ifndef CLP_H
#define CLP_H

#include <bpg-v2/Instruments/Rpg/ControlStatus.hpp>
#include <bpg-v2/Instruments/Rpg/Console/Console.hpp>
#include <iostream>

typedef ColorConsole CC;

class Clp: public Command{
  ControlStatus& controlStatus_;
  Console& console_;
public:
  Clp(const std::string& name, const std::string& description,
      ControlStatus& controlStatus, Console& console): 
    Command(name,description), controlStatus_(controlStatus),
    console_(console){
    argMap_["on"]  = 1;
    argMap_["off"] = 0;
  }

  virtual ~Clp(){};
  virtual void Execute();

};


void Clp::Execute(){

    std::string status;

    console_.SystemPrompt("[CLP] ");
    console_.UserPrompt("[CLP] ");
	
    if(Interact()){
      console_.Write("CLP Output (on, off):\n", CC::SYSTEM);
      console_.UserPrompt();
      std::getline(std::cin,status);
      boost::erase_all(status, " ");
    }
    else status = argList_[0];

    ArgMap::iterator iter = argMap_.find(status);
    if(iter != argMap_.end()){
      controlStatus_.UseCLP(iter->second);
      console_.Write("CLP is " + iter->first + "\n",CC::SYSTEM);
    }
    else console_.Write("CLP setting is invalid\n", CC::SYSTEM);
  }


#endif
