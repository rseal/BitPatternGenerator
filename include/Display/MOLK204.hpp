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
#ifndef MO_LK204_H
#define MO_LK204_H

#include <bpg-v2/Common/LCD.hpp>
#include <bpg-v2/Instruments/Rpg/Mode/Mode.hpp>

//matrix orbital usb-based LCD LK204 series.

class MOLK204 : public LCD {

   public:
      MOLK204(Mode first, int number) : LCD(first, number) {
      }

      virtual void Display()
      {
         modeName_ = currentMode_.Name();

         std::string tempStr;
         int temp;

         // clears the screen and returns cursor to top left
         temp = 254;
         write(fd_,(const void *)temp, sizeof(int));
         temp = 88;
         write(fd_, (const void *)temp, sizeof(int));


         tempStr = "Mode: ";
         write(fd_, tempStr.c_str(), tempStr.size());
         write(fd_, modeName_.c_str(), modeName_.size());

         // sets curssor position to 1,0
         temp = 254;
         write(fd_, (const void *)temp, sizeof(int));
         temp = 71;
         write(fd_, (const void *)temp, sizeof(int));
         temp = 1;
         write(fd_, (const void *)temp, sizeof(int));
         temp = 0;
         write(fd_, (const void *)temp, sizeof(int));

         tempStr = "Mode #: ";
         write(fd_, tempStr.c_str(), tempStr.size());

         tempStr = boost::lexical_cast<std::string>(modeNumber_); 
         write(fd_, tempStr.c_str(), tempStr.size());

         temp = 254;
         write(fd_, (const void *)temp, sizeof(int));
         temp = 71;
         write(fd_, (const void *)temp, sizeof(int));
         temp = 2;
         write(fd_, (const void *)temp, sizeof(int));
         temp = 0;
         write(fd_, (const void *)temp, sizeof(int));

         tempStr = "Start: ";
         write(fd_, tempStr.c_str(), tempStr.size());
         write(fd_, stime_, 9);

         temp = 254;
         write(fd_, (const void *)temp, sizeof(int));
         temp = 71;
         write(fd_, (const void *)temp, sizeof(int));
         temp = 3;
         write(fd_, (const void *)temp, sizeof(int));
         temp = 0;
         write(fd_, (const void *)temp, sizeof(int));


         tempStr = "Elapsed: ";
         write(fd_, tempStr.c_str(), tempStr.size());


         time (&elapsedTime_);
         timeInfo_ = localtime (&elapsedTime_);

         etimeStr_ = "";

         if(((elapsedTime_ - startTime_) / 60 ) > 0)
         {
            std::string hour, min, sec;

            if(((elapsedTime_ - startTime_) / 3600 ) > 0)
            {
               hour = boost::lexical_cast<std::string>(static_cast<int>((elapsedTime_ - startTime_) / 3600));
               etimeStr_ += hour;

               etimeStr_ += ":";

               //sprintf(min, "%d", static_cast<int>((ElapsedTime
            }

            min = boost::lexical_cast<std::string>(static_cast<int>((elapsedTime_ - startTime_) / 60));
            sec = boost::lexical_cast<std::string>(static_cast<int>((elapsedTime_ - startTime_) % 60));

            etimeStr_ += min;
            etimeStr_ += ":";

            if(((elapsedTime_ - startTime_) % 60 ) < 10)
               etimeStr_ += "0";

            etimeStr_ += sec;
         }
         else{
            etimeStr_ = boost::lexical_cast<std::string>(static_cast<int>((elapsedTime_ - startTime_)));
         }

         write(fd_, etimeStr_.c_str(), etimeStr_.size());
      }

      //void Exit() { exit_ = true;}
};

#endif
