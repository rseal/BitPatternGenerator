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
#ifndef FPGAIMAGE_H
#define FPGAIMAGE_H

#include <iostream>
#include <fstream>

#pragma GCC system_header
#include <bpg-v2/Instruments/Rpg/okFrontPanelDLL.h>

#include <bpg-v2/Instruments/Rpg/Command/Constants.hpp>
#include <bpg-v2/Instruments/Rpg/Console/Console.hpp>
#include <sthread/Lock.hpp>

typedef ColorConsole CC;

///\brief Load a new fpga image other than the default.
class FPGAImage: public Command
{
   private:

      okCUsbFrontPanel& okFrontPanel_;
      Mutex& mutex_;
      std::string fileName_;
      Console& console_;

   public:

      FPGAImage(const std::string& name, const std::string& description, 
            okCUsbFrontPanel& okFrontPanel, Mutex& mutex, Console& console):
         Command(name,description), okFrontPanel_(okFrontPanel), mutex_(mutex), 
         console_(console) {};

      virtual ~FPGAImage(){};
      virtual void Execute();
};


void FPGAImage::Execute()
{
   std::string input;

   console_.SystemPrompt("[IMAGE] ");
   console_.UserPrompt("[IMAGE] ");

   if(Interact())
   {
      console_.Write("Enter the new FPGA image\n",CC::SYSTEM);
      console_.UserPrompt();
      std::getline(std::cin, input);
      boost::erase_all(input, " ");
   }
   else input = argList_[0];

   fileName_ = IMAGE_PATH + input + IMAGE_EXT;
   std::ifstream in(fileName_.c_str(), std::ios::in);

   if(!in) 
   {
      console_.Write(input + " does not exist\n",CC::SYSTEM);
   }
   else
   {
      mutex_.Lock();
      if(okFrontPanel_.ConfigureFPGA(fileName_) < 0)
         console_.Write("failed to load" + fileName_ + "\n" ,CC::SYSTEM);
      else 
         console_.Write("Loaded" + fileName_ + "\n",CC::SYSTEM);
      mutex_.Unlock();
   }
}  
#endif
