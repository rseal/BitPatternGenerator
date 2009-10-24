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
#ifndef CFA634_H
#define CFA634_H

#include <bpg-v2/Common/LCD.hpp>
#include <stdexcept>
#include <termios.h>
#include <fcntl.h>

class CFA634: public LCD{

  const std::string port_;

  void Init(){
    
    const speed_t baudRate = B19200;
    
    fileDescriptor_ = open(port_.c_str(), O_RDWR | O_NOCTTY | O_NONBLOCK);
    
    if(fileDescriptor_ == -1)
      throw std::runtime_error("\nError opening port " + port_);

    //get current settings
    tcgetattr(fileDescriptor_,&oldParams_);
    tcgetattr(fileDescriptor_, &newParams_);
  
    //input modes
    newParams_.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|INPCK|ISTRIP|INLCR|IGNCR|ICRNL
			    |IXON|IXOFF);
    newParams_.c_iflag |= IGNPAR;
    
    //output modes
    newParams_.c_oflag &= ~(OPOST|ONLCR|OCRNL|ONOCR|ONLRET|OFILL
			    |OFDEL|NLDLY|CRDLY|TABDLY|BSDLY|VTDLY|FFDLY);
    
    //control modes
    newParams_.c_cflag &= ~(CSIZE|PARENB|PARODD|HUPCL|CRTSCTS);
    newParams_.c_cflag |= CREAD|CS8|CSTOPB|CLOCAL;
    
    //local modes
    newParams_.c_lflag &= ~(ISIG|ICANON|IEXTEN|ECHO);
    newParams_.c_lflag |= NOFLSH;

    //set baud rate
    cfsetospeed(&newParams_, baudRate);
    cfsetispeed(&newParams_, baudRate);

    tcsetattr(fileDescriptor_, TCSANOW, &newParams_);
 
    Brightness(45);
    Contrast(60);

    //clear
    Home();

    //scroll off
    Control(20);

    //wrap off
    Control(24);

    //hide cursor
    Control(4);
    
    BootScreen();

  }

  void Home(){ Control(12); }

  void Location(const int& line, const int& column){
    unsigned char buf[3] = {17, column, line};
    write(fileDescriptor_, &buf, 3);
  }

  void Write(const std::string& str){
    write(fileDescriptor_, &str[0], str.size());
  }

public:

  CFA634(const std::string& port, const int& lines, const int& columns): LCD(lines,columns), port_(port) {}

  ~CFA634(){ BootScreen(); }
  
  void BootScreen(){
    Home();
    Message(0,"  RPG Version 2.0  ");
    Message(1," October 20, 2009  ");
    Message(2," ASPIRL Laboratory ");
    Message(3,"   <Penn State>   ");
    Update();
  }

  void Brightness(const int& num){
    //0-100
    unsigned char buf[2] = {14,num};
    write(fileDescriptor_, &buf,2);
  }

  void Contrast(const int& num){
    //0-100
    unsigned char buf[2] = {15,num};
    write(fileDescriptor_, &buf,2);
  }
  
  void Control(const int& num){
    unsigned char buf = num;
    write(fileDescriptor_, &buf, 1);
  }
};

#endif
