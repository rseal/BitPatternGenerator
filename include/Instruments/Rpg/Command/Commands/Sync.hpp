#ifndef SYNC_H
#define SYNC_H

#include <bpg-v2/Instruments/Rpg/ControlStatus.hpp>
#include <bpg-v2/Instruments/Rpg/Console/Console.hpp>
#include <iostream>

typedef ColorConsole CC;

class Sync: public Command{
  ControlStatus& controlStatus_;
  Console& console_;
public:
  explicit Sync(const std::string& name, const std::string& description,
		ControlStatus& controlStatus, Console& console): 
    Command(name,description),controlStatus_(controlStatus),
    console_(console){
    argMap_["int"]   = ControlStatus::INT_SYNC;
    argMap_["1pps"]  = ControlStatus::PPS1_SYNC;
    argMap_["10pps"] = ControlStatus::PPS10_SYNC;
    argMap_["ext"]   = ControlStatus::EXT_SYNC;
  }

  virtual void Execute();

};


void Sync::Execute(){
  std::string type;

  console_.SystemPrompt("[SYNC] ");
  console_.UserPrompt("[SYNC] ");
	
  if(Interact()){
    console_.Write("Set sync source (int, 1pps, 10pps, ext)\n", CC::SYSTEM);
    console_.UserPrompt();
    //modified to properly read entire line
    std::getline(std::cin,type);
    boost::erase_all(type," ");
  }
  else type = argList_[0];
	
  ArgMap::iterator iter = argMap_.find(type);
  if(iter != argMap_.end())
    controlStatus_.Sync(iter->second);
  else
    console_.Write("Invalid request\n", CC::SYSTEM); 
}


#endif
