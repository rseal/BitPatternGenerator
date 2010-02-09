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
#ifndef STATUS_H
#define STATUS_H

#include <bpg-v2/Instruments/Rpg/okFrontPanelDLL.h>
#include <bpg-v2/Instruments/Rpg/ControlStatus.hpp>
#include <bpg-v2/Instruments/Rpg/Console/Console.hpp>

typedef ColorConsole CC;

///\brief retrieve system status from FPGA
class Status: public Command{
  okCUsbFrontPanel& okFrontPanel_;
  ControlStatus& controlStatus_;
  Console& console_;
public:
  Status(const std::string& name, const std::string& description,
	 okCUsbFrontPanel& okFrontPanel, ControlStatus& controlStatus,
	 Console& console):
    Command(name,description), okFrontPanel_(okFrontPanel), 
    controlStatus_(controlStatus), console_(console){}
  virtual ~Status(){};

  virtual void Execute(){ 
    console_.SystemPrompt("[STATUS] ");
    console_.Write("Port A status = 0x", CC::SYSTEM);
    std::cout << controlStatus_.Status(ControlStatus::PORTA) << std::endl;
    console_.Write("Port B status = 0x", CC::SYSTEM);
    std::cout << controlStatus_.Status(ControlStatus::PORTB) << std::endl;
  }
};

#endif
