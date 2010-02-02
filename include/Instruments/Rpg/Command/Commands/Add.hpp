#ifndef ADD_H
#define ADD_H

#include <bpg-v2/Instruments/Rpg/okFrontPanelDLL.h>
#include <bpg-v2/Instruments/Rpg/Mode/ModeArray.hpp>
#include <bpg-v2/Instruments/Rpg/ControlStatus.hpp>
#include <sthread/Lock.hpp>
#include <bpg-v2/Instruments/Rpg/Console/Console.hpp>
#include <bpg-v2/Instruments/Rpg/Command/Constants.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <fstream>

typedef ColorConsole CC;

///\brief load a new mode into system memory.
class Add: public Command{

   okCUsbFrontPanel& okFrontPanel_;
   ControlStatus& controlStatus_;
   ModeArray& modeArray_;
   int dataSize_;
   Mutex& mutex_;
   Console& console_;

   const bool Load(const std::string& name);
   void InitializeFPGA(std::vector<short>& data);

   public:
   Add(const std::string& name, const std::string& description,
         okCUsbFrontPanel& okFrontPanel, ModeArray& modes, 
         ControlStatus& controlStatus, Mutex& mutex, Console& console):
      Command(name,description), okFrontPanel_(okFrontPanel), 
      controlStatus_(controlStatus), modeArray_(modes), dataSize_(8196),
      mutex_(mutex), console_(console){}

   virtual ~Add(){};
   virtual void Execute(); 

};


const bool Add::Load(const std::string& name){

   bool ret= false;
   std::string input;
   std::vector<short> data;

   std::string fileName = MODE_PATH + name + MODE_EXT;
   std::ifstream in(fileName.c_str(), std::ios::in);

   if(in){

      while(!in.eof()){
         getline(in,input);
         data.push_back(boost::lexical_cast<int>(input));
      }

      if(data.size() != dataSize_) 
         console_.Write("WARNING: size mismatch - found " +
               boost::lexical_cast<std::string>(data.size()) +
               " entries\n",CC::SYSTEM);

      //add mode
      modeArray_.Add(Mode(data,name));

      if(modeArray_.NumModes() == 1) InitializeFPGA(data);

      ret = true;
   }
   return ret;
}

void Add::InitializeFPGA(std::vector<short>& data){

   //if this is the first mode - initialize the fpga with it
   unsigned char *porta = 
      reinterpret_cast<unsigned char*> (&data[0]);
   unsigned char *portb = 
      reinterpret_cast<unsigned char*>(&data[4098]);

   mutex_.Lock();
   okFrontPanel_.WriteToPipeIn(0x80, dataSize_, porta);
   okFrontPanel_.WriteToPipeIn(0x81, dataSize_, portb);
   mutex_.Unlock();

   //add a delay giving the update thread a chance to receive new status
   // I will find a better place to put this soon as debugging is over
   usleep(10000);

   if(!controlStatus_.Ready(ControlStatus::PORTA)) 
      console_.Write("ERROR: PORTA load failed\n",CC::SYSTEM);  
}


void Add::Execute(){

   bool valid = false;
   std::string token;
   ArgList modeList;

   console_.SystemPrompt("[ADD] ");
   console_.UserPrompt("[ADD] ");

   if(Interact()){
      console_.Write("Enter the mode names (mode1, mode2, ... , modeN)\n", CC::SYSTEM);
      console_.UserPrompt();

      //modified to properly read entire line
      std::getline(std::cin,token);
      boost::erase_all(token," ");
      //parse input into to tokens and store in modeList
      boost::split(modeList,token, boost::is_any_of(","));

   }
   else modeList = argList_;

   ArgList::const_iterator iter = modeList.begin();

   while(iter != modeList.end()){
      console_.SystemPrompt();
      if(Load(*iter))
         console_.Write(CC::GREEN, "Successfully added " + *iter + "\n");
      else
         console_.Write(CC::RED,"Failed to add " + *iter + "\n");
      ++iter;
   }
}

#endif
