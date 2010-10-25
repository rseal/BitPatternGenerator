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
#ifndef START_H
#define START_H

#include <bpg-v2/Instruments/Rpg/okFrontPanelDLL.h>
#include <bpg-v2/Instruments/Rpg/Mode/ModeArray.hpp>
#include <bpg-v2/Instruments/Rpg/ControlStatus.hpp>
#include <bpg-v2/Instruments/Rpg/Console/Console.hpp>
#include <bpg-v2/Common/LCDController.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>

typedef ColorConsole CC;

class Start: public Command{
  
  typedef boost::shared_ptr< LCDController > LcdControllerPtr;
  LcdControllerPtr lcdController_;
  okCUsbFrontPanel& okFrontPanel_;
  ModeArray& modeArray_;
  ControlStatus& controlStatus_;
  std::string port_;
  Console& console_;
public:
  Start(const std::string& name, 
	const std::string& description,
	okCUsbFrontPanel& okFrontPanel, 
	ModeArray& modeArray, 
	ControlStatus& controlStatus, 
	LcdControllerPtr lcdController,
	Console& console):
    Command(name,description), okFrontPanel_(okFrontPanel), 
    modeArray_(modeArray), controlStatus_(controlStatus),
    lcdController_( lcdController ), console_(console){
    argMap_["a"]   = ControlStatus::PORTA;
    argMap_["b"]   = ControlStatus::PORTB;
    argMap_["all"] = ControlStatus::PORTAB;
  }

  virtual ~Start() {};

  virtual void Execute();

};

void Start::Execute(){
  std::string port;
  
  console_.SystemPrompt("[START] ");
  console_.UserPrompt("[START] ");
  
  if(Interact()){
    console_.Write("Start port (a, b, all):\n", CC::SYSTEM);
    console_.UserPrompt();
    std::getline(std::cin,port);
    boost::erase_all(port, " ");
  }
  else port = argList_[0];
  
  ArgMap::iterator iter = argMap_.find(port);
  
  if(iter != argMap_.end()){
    
    if(controlStatus_.Ready(iter->second))
      controlStatus_.Control(ControlStatus::START, iter->second, 
			     ControlStatus::SET);
    else{
      console_.Write("PORT not ready (did you configure channels?)\n", 
		     CC::SYSTEM);
      goto ret;
    }
    
    int i=0;
    for(i; i <10000; ++i){
      if(controlStatus_.Active(iter->second)) break;
      usleep(1000);
    }
    
    if(i == 10000) console_.Write("ERROR: PORT failed to start\n", CC::SYSTEM);
    else{
      controlStatus_.Control(ControlStatus::START, iter->second, 
			     ControlStatus::CLEAR);
      console_.Write("PORT active\n", CC::SYSTEM);
      lcdController_->Start();
    }
  }
  else console_.Write("Invalid Start entry\n", CC::SYSTEM);

 ret: return;
}   


#endif 
