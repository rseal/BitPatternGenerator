#ifndef FPGAIMAGE_H
#define FPGAIMAGE_H

#include <bpg-v2/Common/Lock.hpp>
#include <iostream>
#include <bpg-v2/Instruments/Rpg/okFrontPanelDll.h>
#include <bpg-v2/Instruments/Rpg/Console/Console.hpp>

///\brief Load a new fpga image other than the default.
class FPGAImage: public Command{
  okCUsbFrontPanel& okFrontPanel_;
  Mutex& mutex_;
  std::string fileName_;
  Console& console_;
public:
  FPGAImage(const string& name, const string& description, 
	 okCUsbFrontPanel& okFrontPanel, Mutex& mutex, Console& console):
    Command(name,description), okFrontPanel_(okFrontPanel), mutex_(mutex), 
    console_(console)
  {};
  
  virtual ~FPGAImage(){};

  virtual void Execute(){

    bool valid = false;
    string input;

    console_.SystemPrompt("[CONFIG] ");
    console_.UserPrompt("[CONFIG] ");
    
    if(Interact())
      {
    	console_.Write("Enter the new FPGA image\n",CC::SYSTEM);
    	console_.UserPrompt();
    	getline(cin, input);
	erase_all(input, " ");
      }
    else input = argList_[0];

    fileName_ = IMAGE_PATH + input + IMAGE_EXT;
    ifstream in(fileName_.c_str(), std::ios::in);
   
    if(!in) 
      console_.Write(input + " does not exist\n",CC::SYSTEM);
    else{
      valid = true;
      mutex_.Lock();
      if(okFrontPanel_.ConfigureFPGA(fileName_) < 0)
	console_.Write("failed to load" + fileName_ + "\n" ,CC::SYSTEM);
      else 
	console_.Write("Loaded" + fileName_ + "\n",CC::SYSTEM);
      mutex_.Unlock();
    }
  }  
};


#endif
