#ifndef LIST_H
#define LIST_H

#include <bpg-v2/Instruments/Rpg/Mode/ModeArray.hpp>
#include <bpg-v2/Instruments/Rpg/Console/Console.hpp>
#include <iostream>
#include <boost/lexical_cast.hpp>

typedef ColorConsole CC;

class List: public Command
{
  ModeArray& modeArray_;
  Console& console_;
    
public:
  List(const std::string& name, const std::string& description, ModeArray& modeArray,
       Console& console): 
    Command(name,description), modeArray_(modeArray), console_(console){};

  virtual ~List() {};
  virtual void Execute();
};

void List::Execute(){
  int idx=0;
  console_.SystemPrompt("[LIST] ");
  console_.Write("Loaded Modes: \n",CC::SYSTEM,true);
  std::vector<std::string> names = modeArray_.Names();
  console_.SystemPrompt();
  for(int i=0; i<names.size(); ++i){
    console_.Write(CC::YELLOW, "[" + boost::lexical_cast<std::string>(i) + "] ");
    console_.Write(CC::WHITE, names[i] + (i==names.size()-1 ? "" : ", "));
  }
  console_.Write(CC::WHITE,"\n");
}

#endif
