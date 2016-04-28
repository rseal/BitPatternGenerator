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
#ifndef CLOCK_H
#define CLOCK_H

#pragma GCC system_header
#include <bpg-v2/Instruments/Rpg/okFrontPanelDLL.h>

#include <bpg-v2/Instruments/Rpg/ControlStatus.hpp>
#include <bpg-v2/Instruments/Rpg/Console/Console.hpp>

typedef ColorConsole CC;

class Clock: public Command
{
  okCUsbFrontPanel& okFrontPanel_;
  ControlStatus& controlStatus_;
  Console& console_;

public:
  Clock(const std::string& name, const std::string& description,
	okCUsbFrontPanel& okFrontPanel, ControlStatus& controlStatus, Console& Console):
    Command(name,description), okFrontPanel_(okFrontPanel),
    controlStatus_(controlStatus), console_(Console){
    argMap_["std"] = ControlStatus::STD_CLK;
    argMap_["drf"] = ControlStatus::DRIFTED_CLK;
    argMap_["int"] = ControlStatus::INT_CLK;
  }
  virtual ~Clock(){};
    
  virtual void Execute(){
    std::string type;

    console_.SystemPrompt("[CLOCK] ");
    console_.UserPrompt("[CLOCK] ");
	
    if(Interact()){
      console_.Write("Which clock source (std, drf, int) ?\n",CC::SYSTEM);
      console_.UserPrompt();
      std::getline(std::cin,type);
      boost::erase_all(type," ");
    }
    else type = argList_[0];
    
    ArgMap::iterator iter = argMap_.find(type);
    if(iter != argMap_.end()){
      controlStatus_.ClockSource(iter->second);
      console_.Write("Clock source set to " + iter->first + "\n", CC::SYSTEM);
    }
    else console_.Write("Invalid Clock source entry.\n", CC::SYSTEM);
  }
};

#endif
