#ifndef RESET_H
#define RESET_H

#include <bpg-v2/Instruments/Rpg/ControlStatus.hpp>
#include <bpg-v2/Instruments/Rpg/Console/Console.hpp>

typedef ColorConsole CC;

class Reset: public Command
{
  ControlStatus& controlStatus_;
  Console& console_;

public:
  Reset(const std::string& name, const std::string& description,
	ControlStatus& controlStatus, Console& console): 
    Command(name,description),controlStatus_(controlStatus),
    console_(console) {
    argMap_["set"]   = ControlStatus::SET;
    argMap_["clear"] = ControlStatus::CLEAR;
  }

  virtual void Execute();

};

void Reset::Execute(){
    std::string method;

    console_.SystemPrompt("[RESET] ");
    console_.UserPrompt("[RESET] ");

    if(Interact()){
      console_.Write("Which method (clear, set) ?\n", CC::SYSTEM);
      console_.UserPrompt();
      std::getline(std::cin,method);
      boost::erase_all(method," ");
    }
    else method = argList_[0];

    ArgMap::iterator iter = argMap_.find(method);
	
    if(iter != argMap_.end())
      controlStatus_.Control(ControlStatus::RESET, ControlStatus::PORTAB, iter->second);
    else
      console_.Write("Invalid request\n", CC::SYSTEM);
  }

#endif
