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

//Using NVI with one public virtual function
class LCD {

  virtual void Location(const int& line, const int& column)=0;
  virtual void Write(const string& str)=0;

protected:
  const std::string location_;
  int fileDescriptor_;
  termios oldParams_;
  termios newParams_;
  int columns_;
  std::vector<std::string> message_;

public:
  
  LCD(const int& line, const int& columns):
    message_(line), columns_(columns){}

  virtual void Init()=0;
  virtual void BootScreen()=0;
  virtual void Home()=0;

  void Update(){
    uint sz = message_.size();
    for(uint i=0; i<sz; ++i){
      Location(i,0);
      Write(message_[i]);
    }
  }

  virtual ~LCD(){}
 
  void Message(const int& line, const string& str){
    if(line > message_.size()) 
      throw std::runtime_error(" Requested LCD line number too large");
    message_[line] = str;
  };
};


#endif
