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
#ifndef REMOVE_H
#define REMOVE_H

#include <cctype>
#include <vector>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <bpg-v2/Instruments/Rpg/Console/Console.hpp>

typedef ColorConsole CC;

///\brief remove a mode that was previously loaded.
class Remove: public Command{
  ModeArray& modeArray_;
  std::vector<Mode>& arrayList_;
  Console& console_;
public:
  Remove(const std::string& name, const std::string& description,
	 ModeArray& modeArray, Console& console): 
    Command(name,description),modeArray_(modeArray),
    arrayList_(modeArray.GetArray()), console_(console){}
  virtual ~Remove() {};
  virtual void Execute();
};


void Remove::Execute(){
	
    std::string name;
    std::vector<std::string> names = modeArray_.Names();

    console_.SystemPrompt("[REMOVE] ");
    console_.UserPrompt("[REMOVE] ");

    if(Interact()){
      console_.SystemPrompt();
      console_.Write(CC::BLUE,"Currently Loaded Modes:\n");

      console_.SystemPrompt();

      for(int i=0; i<names.size(); ++i){
	console_.Write(CC::YELLOW, "[" + boost::lexical_cast<std::string>(i) + "] ");
	console_.Write(CC::WHITE, names[i] + (i==names.size()-1 ? "" : ", "));
      }
      console_.Write(CC::WHITE,"\n");

      console_.Write("Enter the mode's name or index number to remove\n", CC::SYSTEM);
      console_.UserPrompt();
      std::getline(std::cin,name);
      boost::trim(name);
    }
    else name = argList_[0];

    //check and see if first character is a digit - if so, assume index requested
    if(isdigit(name[0])){
      unsigned int idx = boost::lexical_cast<unsigned int>(name);
      if(idx < names.size()) name = names[idx];
    }

    if(!modeArray_.Remove(name)){
      console_.SystemPrompt();
      console_.Write(CC::RED, "Mode ");
      console_.Write(CC::YELLOW, name);
      console_.Write(CC::RED, " is not loaded\n");
    }
    else{
      console_.SystemPrompt();
      console_.Write(CC::GREEN, "Mode ");
      console_.Write(CC::YELLOW, name);
      console_.Write(CC::GREEN, " has been removed.\n");
    }
  }

#endif
