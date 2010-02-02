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
