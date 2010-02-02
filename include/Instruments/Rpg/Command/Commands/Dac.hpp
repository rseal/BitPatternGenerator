#ifndef DAC_H
#define DAC_H

#include <bpg-v2/Instruments/Rpg/ControlStatus.hpp>
#include <bpg-v2/Instruments/Rpg/Console/Console.hpp>
#include <iostream>

typedef ColorConsole CC;

class Dac: public Command{
  ControlStatus& controlStatus_;
  Console& console_;
public:
  Dac(const std::string& name, const std::string& description,
      ControlStatus& controlStatus, Console& console): 
    Command(name,description),controlStatus_(controlStatus),
    console_(console){
    argMap_["on"]  = 1;
    argMap_["off"] = 0;
  }
  virtual ~Dac(){};
    
  virtual void Execute(){
    std::string status;

    console_.SystemPrompt("[DAC] ");
    console_.UserPrompt("[DAC] ");
	
    if(Interact()){
      console_.Write("DAC status (on, off) ?\n", CC::SYSTEM);
      console_.UserPrompt();
      std::getline(std::cin, status);
      boost::erase_all(status, " ");
    }
    else status = argList_[0];
	
    ArgMap::iterator iter = argMap_.find(status);
    if(iter != argMap_.end())
      controlStatus_.UseDAC(iter->second);
    else
      console_.Write("Invalid request\n", CC::SYSTEM);
  }
};


#endif
