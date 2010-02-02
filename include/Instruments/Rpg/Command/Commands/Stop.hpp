#ifndef STOP_H
#define STOP_H

#include <bpg-v2/Instruments/Rpg/okFrontPanelDLL.h>
#include <bpg-v2/Instruments/Rpg/ControlStatus.hpp>
#include <bpg-v2/Instruments/Rpg/Console/Console.hpp>
#include <iostream>

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
