#ifndef SWITCH_H
#define SWITCH_H

#include <bpg-v2/Instruments/Rpg/okFrontPanelDLL.h>
#include <bpg-v2/Instruments/Rpg/Mode/ModeArray.hpp>
#include <bpg-v2/Instruments/Rpg/ControlStatus.hpp>
#include <bpg-v2/Instruments/Rpg/Console/Console.hpp>
#include <bpg-v2/Common/LCDController.hpp>
#include <iostream>

typedef ColorConsole CC;

class Switch: public Command{
  okCUsbFrontPanel& okFrontPanel_;
  ModeArray& modeArray_;
  ControlStatus& controlStatus_;
  Console& console_;
  LCDController& lcdController_;
  int dataSize_;

public:
  Switch(const std::string& name, const std::string& description,
	 okCUsbFrontPanel& okFrontPanel, ModeArray& modes, 
	 ControlStatus& controlStatus, LCDController& lcdController, Console& console):
    Command(name,description),okFrontPanel_(okFrontPanel), modeArray_(modes),
    controlStatus_(controlStatus), lcdController_(lcdController), dataSize_(DATA_SIZE),
    console_(console){
    argMap_["a"]   = ControlStatus::PORTA;
    argMap_["b"]   = ControlStatus::PORTB;
    argMap_["all"] = ControlStatus::PORTAB;
  }

  virtual  ~Switch(){};

  virtual void Execute();

};


void Switch::Execute(){
  std::string port;
  
  console_.SystemPrompt("[SWITCH] ");
  console_.UserPrompt("[SWITCH] ");
  
  if(Interact()){
    console_.Write("Switch port (a, b, all): \n", CC::SYSTEM);
    console_.UserPrompt();
    std::getline(std::cin,port);
    boost::erase_all(port, " ");
  }
  else port = argList_[0];

  ArgMap::iterator iter = argMap_.find(port);
    
  if(iter != argMap_.end()){
      
    controlStatus_.Control(ControlStatus::SWITCH, iter->second, ControlStatus::SET);
      
    int i=0;
    for(i; i < 1000; ++i){
      if(controlStatus_.Preload(iter->second)) break;
      usleep(1000);
    }
      
    if(i == 1000) console_.Write("ERROR: Port timed out when attempting to switch modes\n", CC::SYSTEM);
    else{
      // clear the switch bit
      controlStatus_.Control(ControlStatus::SWITCH, iter->second, ControlStatus::CLEAR);
      Mode mode(modeArray_.Next());
		
      // get next buffer
      std::vector<short> dataVector_(mode.Data());
      unsigned char* porta = reinterpret_cast<unsigned char*>(&dataVector_[0]);
		
      //write mode to FPGA
      okFrontPanel_.WriteToPipeIn(0x80, dataSize_, porta);
      if(controlStatus_.LoadComplete(iter->second)){
	console_.Write("New mode: ", CC::SYSTEM); 
	console_.Write(mode.Name());
		    
	//Send mode name to LCD screen.
	lcdController_.Mode(mode.Name());
      }
      else console_.Write("Port failed while loading new mode\n", CC::SYSTEM); 
    }
  }
  else console_.Write("Invalid request\n", CC::SYSTEM);
}

#endif
