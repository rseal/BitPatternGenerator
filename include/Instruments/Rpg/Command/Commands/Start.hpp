#ifndef START_H
#define START_H

#include <bpg-v2/Instruments/Rpg/okFrontPanelDLL.h>
#include <bpg-v2/Instruments/Rpg/Mode/ModeArray.hpp>
#include <bpg-v2/Instruments/Rpg/ControlStatus.hpp>
#include <bpg-v2/Instruments/Rpg/Console/Console.hpp>
#include <iostream>

typedef ColorConsole CC;

class Start: public Command{
  okCUsbFrontPanel& okFrontPanel_;
  ModeArray& modeArray_;
  ControlStatus& controlStatus_;
  std::string port_;
  Console& console_;
public:
  Start(const std::string& name, const std::string& description,
	okCUsbFrontPanel& okFrontPanel, ModeArray& modeArray, 
	ControlStatus& controlStatus, Console& console):
    Command(name,description), okFrontPanel_(okFrontPanel), 
    modeArray_(modeArray), controlStatus_(controlStatus),
    console_(console){
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
    }
  }
  else console_.Write("Invalid Start entry\n", CC::SYSTEM);

 ret: return;
}   


#endif 
