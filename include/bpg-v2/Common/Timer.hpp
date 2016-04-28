// Copyright (c) 2010 Ryan Seal <rlseal -at- gmail.com>
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
