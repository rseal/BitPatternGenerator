#ifndef TIMER_HPP
#define TIMER_HPP

#include <sthread/SThread.hpp>
#include <bpg-v2/Instruments/Rpg/Command/Command.hpp>
#include <boost/shared_ptr.hpp>

class Timer: public SThread
{
   typedef boost::shared_ptr<Command> CommandPtr;
   CommandPtr command_;

   //timeout value in seconds
   const unsigned int timeOut_;

   public:

   Timer(const unsigned int timeOut): timeOut_(timeOut){}

   void Run() {

      unsigned int counter=0;

      while(counter != timeOut_) { 
         Sleep(sthread::sec, 1);
         ++counter;
      }

      // trigger the callback when timeout is reached
      command_->Execute();
   }

   void Register( CommandPtr command ){ command_ = command; }

};

#endif 
