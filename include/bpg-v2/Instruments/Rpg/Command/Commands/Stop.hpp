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
#ifndef STOP_H
#define STOP_H

#include <iostream>

#pragma GCC system_header
#include <bpg-v2/Instruments/Rpg/okFrontPanelDLL.h>
#include <bpg-v2/Instruments/Rpg/ControlStatus.hpp>
#include <bpg-v2/Instruments/Rpg/Console/Console.hpp>

typedef ColorConsole CC;

class Stop: public Command{
  okCUsbFrontPanel& okFrontPanel_;
  ControlStatus& controlStatus_;
  Console& console_;
public:
  Stop(const std::string& name, const std::string& description,
       okCUsbFrontPanel& okFrontPanel, ControlStatus& controlStatus,
       Console& console):
    Command(name,description), okFrontPanel_(okFrontPanel),
    controlStatus_(controlStatus), console_(console){
    argMap_["a"]   = ControlStatus::PORTA;
    argMap_["b"]   = ControlStatus::PORTB;
    argMap_["all"] = ControlStatus::PORTAB;
  }
  virtual ~Stop(){};
  virtual void Execute();

};

void Stop::Execute(){
  std::string port;

  console_.SystemPrompt("[STOP] ");
  console_.UserPrompt("[STOP] ");

  if(Interact()){
    console_.Write("Stop port (a, b, all):\n", CC::SYSTEM);
    console_.UserPrompt();
    std::getline(std::cin, port);
    boost::erase_all(port, " ");
  }
  else port = argList_[0];

	
  ArgMap::iterator iter = argMap_.find(port);
	
  if(iter != argMap_.end()){

    if(controlStatus_.Active(iter->second)){
      console_.Write("Stopping Port\n", CC::SYSTEM);
      controlStatus_.Control(ControlStatus::STOP, iter->second, ControlStatus::SET);
		
      // stop waits for the current IPP to complete - 1 second delay
      int i=0;
      for(i; i < 1000; ++i){
	if(!controlStatus_.Active(ControlStatus::PORTA)) break;
	usleep(1000);
      }
      if(i == 1000) console_.Write("ERROR: Port stop command failed to respond. Port is active.\n", CC::SYSTEM);
      else{
	console_.Write("Port has been stopped.\n", CC::SYSTEM);
	controlStatus_.Control(ControlStatus::STOP, iter->second, ControlStatus::CLEAR);
      }
    }
  }
  else console_.Write("Invalid request\n", CC::SYSTEM);
}

#endif
