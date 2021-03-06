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
#ifndef ADD_H
#define ADD_H

#include <cstdint>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

#pragma GCC system_header
#include <bpg-v2/Instruments/Rpg/okFrontPanelDLL.h>

#include <bpg-v2/Instruments/Rpg/Mode/ModeArray.hpp>
#include <bpg-v2/Instruments/Rpg/ControlStatus.hpp>
#include <sthread/Lock.hpp>
#include <bpg-v2/Instruments/Rpg/Console/Console.hpp>
#include <bpg-v2/Instruments/Rpg/Command/Constants.hpp>
#include <boost/lexical_cast.hpp>

typedef ColorConsole CC;

///\brief load a new mode into system memory.
class Add: public Command
{
   private:

      typedef std::vector<uint16_t> DataVector;

      okCUsbFrontPanel& okFrontPanel_;
      ControlStatus& controlStatus_;
      ModeArray& modeArray_;
      Mutex& mutex_;
      Console& console_;

      bool Load(const std::string& name);
      void InitializeFPGA(DataVector& data);

   public:

      Add(
            const std::string& name, 
            const std::string& description,
            okCUsbFrontPanel& okFrontPanel, 
            ModeArray& modes, 
            ControlStatus& controlStatus, 
            Mutex& mutex, 
            Console& console
         ): 
         Command(name,description), okFrontPanel_(okFrontPanel), 
         controlStatus_(controlStatus), modeArray_(modes), mutex_(mutex), 
         console_(console)
   {

   }

      virtual ~Add(){};
      virtual void Execute(); 

      static const uint16_t NUM_ELEMENTS = 8196;
      static const uint16_t PORTA_IDX    = 0;
      static const uint16_t PORTB_IDX    = 4098;
      static const int  PIPEA_ADDRESS    = 0x80;
      static const int  PIPEB_ADDRESS    = 0x81;



};


bool Add::Load(const std::string& name)
{
   bool ret= false;
   std::string input;
   DataVector data;

   std::string fileName = MODE_PATH + name + MODE_EXT;
   std::ifstream in(fileName.c_str(), std::ios::in);

   if(in)
   {
      while(!in.eof())
      {
         getline(in,input);
         data.push_back(boost::lexical_cast<int>(input));
      }

      if(data.size() != NUM_ELEMENTS) 
      {
         console_.Write("WARNING: size mismatch - found " +
               boost::lexical_cast<std::string>(data.size()) +
               " entries\n",CC::SYSTEM);
      }

      //add mode
      modeArray_.Add(Mode(data,name));

      if(modeArray_.NumModes() == 1) InitializeFPGA(data);

      ret = true;
   }

   return ret;
};

void Add::InitializeFPGA(DataVector& data)
{
   mutex_.Lock();
   okFrontPanel_.WriteToPipeIn(PIPEA_ADDRESS, NUM_ELEMENTS, 
         (unsigned char*)&data[PORTA_IDX]);
   mutex_.Unlock();

   //add a delay giving the update thread a chance to receive new status
   // I will find a better place to put this soon as debugging is over
   std::this_thread::sleep_for(std::chrono::milliseconds(100));

   if(!controlStatus_.Ready(ControlStatus::PORTA)) 
      console_.Write("ERROR: PORTA load failed\n",CC::SYSTEM);  

   mutex_.Lock();
   okFrontPanel_.WriteToPipeIn(PIPEB_ADDRESS, NUM_ELEMENTS,
         (unsigned char*)&data[PORTB_IDX]);
   mutex_.Unlock();

   //add a delay giving the update thread a chance to receive new status
   // I will find a better place to put this soon as debugging is over
   std::this_thread::sleep_for(std::chrono::milliseconds(100));

   if(!controlStatus_.Ready(ControlStatus::PORTB)) 
      console_.Write("ERROR: PORTB load failed\n",CC::SYSTEM);  
}


void Add::Execute()
{
   std::string token;
   ArgList modeList;

   console_.SystemPrompt("[ADD] ");
   console_.UserPrompt("[ADD] ");

   if(Interact())
   {
      console_.Write("Enter the mode names (mode1, mode2, ... , modeN)\n", CC::SYSTEM);
      console_.UserPrompt();

      //modified to properly read entire line
      std::getline(std::cin,token);
      boost::erase_all(token," ");
      //parse input into to tokens and store in modeList
      boost::split(modeList,token, boost::is_any_of(","));
   }
   else 
   {
      modeList = argList_;
   }

   ArgList::const_iterator iter = modeList.begin();

   while(iter != modeList.end())
   {
      console_.SystemPrompt();
      if(Load(*iter))
      {
         console_.Write(CC::GREEN, "Successfully added " + *iter + "\n");
      }
      else
      {
         console_.Write(CC::RED,"Failed to add " + *iter + "\n");
      }

      ++iter;
   }
}

#endif
