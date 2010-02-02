#ifndef CLOCK_H
#define CLOCK_H

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
