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
#ifndef LCD_HPP
#define LCD_HPP

#include <vector>
#include <iostream>
#include <termios.h>
#include <stdexcept>
#include <boost/tuple/tuple.hpp>

namespace lcd{
  typedef unsigned int uint;
  typedef boost::tuple<std::string, uint> Tuple;
};

//Using NVI with one public virtual function
class LCD {

  //private virtual function defintions
  virtual void Location(const lcd::uint& line, const lcd::uint& column)=0;
  virtual void Write(const std::string& str)=0;
  virtual void CommInit()=0;
  virtual void Home()      =0;
  virtual void Control(const int& num)=0;

  //member to optimize/minimize character display updates
  const std::vector<lcd::Tuple> Compare(std::string& newStr, std::string& oldStr);
  std::vector<std::string> oldMessage_;
  std::vector<std::string> newMessage_;

protected:
  const std::string location_;
  int fileDescriptor_;
  termios oldParams_;
  termios newParams_;
  int columns_;

public:
  
  LCD(const lcd::uint line, const lcd::uint columns):
    newMessage_(line), oldMessage_(line), columns_(columns){}

  void Init() throw( std::runtime_error ) {

    //setup communication
    CommInit(); 
   
    //these may or may not be effective - depending
    //on LCD model - default behavior does nothing
    Brightness(45);
    Contrast(60);

    //clear
    Home();

    //all following options will have to be changed to a generic member 
    //name so they can be set for all LCD models
    //but for now, I'm lazy.

    //scroll off
    Control(20);
    //wrap off
    Control(24);
    //hide cursor
    Control(4);
    
    BootScreen();

  }

  virtual void Brightness(const int num){}
  virtual void Contrast(const int num){}

  void BootScreen(){
    Message(0,"  BPG Version 2.0  ");
    Message(1," October 24, 2010  ");
    Message(2," ASPIRL Laboratory ");
    Message(3,"   <Penn State>   ");
    Update();
  }

  void Update();

  virtual ~LCD(){}
 
  void Message(const lcd::uint line, const std::string str){
    if(line > newMessage_.size()) 
      throw std::runtime_error(" Requested LCD line number too large");
    newMessage_[line] = str;
  };
};

void LCD::Update(){
  std::vector<lcd::Tuple> vec;
  lcd::uint lines = newMessage_.size();
  lcd::uint vecSize;

  for(lcd::uint i=0; i<lines; ++i){
    vec = Compare(newMessage_[i],oldMessage_[i]);
    vecSize = vec.size();
    for(lcd::uint j=0; j<vecSize; ++j){
      Location(i,vec[j].get<1>());
      Write(vec[j].get<0>());
    }
  }
  oldMessage_ = newMessage_;
};

//This member was added to minimize screen updates, which will, under normal
//circumstances, minimize screen writes and usb bandwidth. The worst-case scenario
//w.r.t this algorithm would occur if every other character in the line matched since
//we have to transmit at least one extra byte to position the cursor on the proper
//column.
const std::vector<lcd::Tuple> LCD::Compare(std::string& newStr, std::string& oldStr){
  lcd::uint size = newStr.size() < oldStr.size() ? newStr.size() : oldStr.size();
  lcd::uint start=0;
  bool mark=false;
  std::vector<lcd::Tuple> vec;
  
  //if screen hasn't been setup, return with full string
  if(size == 0){
    vec.push_back(lcd::Tuple(newStr,start));
    return vec;
  }

  //resize strings to fill entire screen range
  size = columns_;
  newStr.resize(size,' ');
  oldStr.resize(size,' ');

  //if no change in string then return
  if(newStr!=oldStr) {
    for(lcd::uint i=0; i<size; ++i){

      if((newStr[i] != oldStr[i]) && !mark){ 
	start=i; 
	mark=true;
      }

      if((newStr[i] == oldStr[i]) && mark){ 
	vec.push_back(lcd::Tuple(newStr.substr(start,i-start),start));
	mark=false;
      }
    }

    //if mark was set and string index went to end, write
    //substring from mark to end of string
    if(mark)
      vec.push_back(lcd::Tuple(newStr.substr(start,-1),start));

  }
  return vec;
};

#endif
