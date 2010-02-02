#ifndef HELP_H
#define HELP_H

#include <bpg-v2/Instruments/Rpg/Console/Console.hpp>
#include <bpg-v2/Instruments/Rpg/Command/CommandArray.hpp>
#include <iostream>

typedef ColorConsole CC;

///\brief Print a list of commands and their usage.                           
class Help: public Command{
  CommandArray& commands_;
  Console& console_;
public:
  Help(const std::string& name, const std::string& description, CommandArray& commands,
       Console& console):
    Command(name,description), commands_(commands), console_(console){};
  virtual ~Help(){};
  virtual void Execute();
};


void Help::Execute(){
  console_.SystemPrompt("[HELP] ");
  console_.Write("Commands are as follows:\n", CC::SYSTEM,true);
  std::vector<std::string> names = commands_.Names();
  std::vector<std::string>::const_iterator iter = names.begin();
  while(iter != names.end()){
    console_.Write(*iter,CC::SYSTEM);
    ++iter;
  }
}  


#endif
