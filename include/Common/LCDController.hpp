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
#ifndef LCD_CONTROLLER_H
#define LCD_CONTROLLER_H

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/shared_ptr.hpp>
#include <sthread/SThread.hpp>
#include <bpg-v2/Common/LCD.hpp>
#include <sstream>
#include <iostream>

//class uses aggregate LCD object to control display 
//and updating via a separate thread of execution
//inherited from the SThread class
class LCDController : public SThread {

  typedef boost::posix_time::ptime Time;
  typedef boost::posix_time::time_duration Duration;
  typedef boost::shared_ptr< boost::posix_time::time_facet > TimeFacet;
  
  typedef boost::shared_ptr< LCD > LcdPtr;
  LcdPtr lcd_;

  bool running_;
  bool exit_;
  std::string mode_;
  std::stringstream ostr;

  TimeFacet tFacet_;
  Time startTime_;
  Time modeTime_;
  Time currentTime_;
  Duration elapsedTime_;
  Mutex mutex_;
  bool newMode_;

  //use boost date_time libraries to compute
  //time elapsed in current mode
  const std::string ElapsedTime(){
    static bool init=false;

    if(!init){
      elapsedTime_ = boost::posix_time::hours(0) + 
	boost::posix_time::minutes(0) + 
	boost::posix_time::seconds(0);
      init=true;
    }
    else{
      elapsedTime_ = currentTime_ - modeTime_;
    }

    ostr.str("");
    ostr << elapsedTime_ << "   ";
    return ostr.str();
  }

  //use boost date_time library to get current system time
  const std::string CurrentTime(){
    ostr.str("");
    currentTime_ = boost::posix_time::second_clock::local_time();
    ostr << currentTime_;
    return ostr.str();
  }

  //return time that the bpg started running
  const std::string StartTime(){
    ostr.str("");
    ostr << startTime_;
    return ostr.str();
  }

public:

  //ctor initializes time format display for LCD
  explicit LCDController(LcdPtr lcd) throw( std::runtime_error )
  : lcd_(lcd), exit_(false), running_(false), newMode_(true){

    // ATTENTION: this call can throw
    lcd_->Init(); 

    tFacet_ = TimeFacet( new boost::posix_time::time_facet("%r %z") );
    ostr.imbue(std::locale(ostr.getloc(), tFacet_.get() ));
  }

  //no functionality yet
  void Stop() { running_ = false; }

  //switch modes
  void Mode(const std::string& mode) { 
    mode_=mode;
    newMode_ = true;
  }

  //virtual function defining separate thread of execution
  //Makes use of Sleep() function to put thread to sleep for 1 second
  //followed by an display update
  void Run(){

    startTime_ = boost::posix_time::second_clock::local_time();
    running_ = true;

    while (!exit_) {

      //sleep for one second then update display
      Sleep(sthread::sec,1);

      if(newMode_){
	    modeTime_ = boost::posix_time::second_clock::local_time();
	    newMode_  = false;
      }
      std::string cTime = CurrentTime();
      std::string eTime = ElapsedTime();

      //using a mutex to prevent possible asynchronous updating
      //of Message strings via BootScreen() member of LCD
      mutex_.Lock();
      lcd_->Message(0,"   Mode: " + mode_);
      lcd_->Message(1,"Elapsed: " + eTime);
      lcd_->Message(2,"  Start: " + StartTime());
      lcd_->Message(3," System: " + cTime); 
      lcd_->Update();
      mutex_.Unlock();
    }
  }
  
  //dtor reset display to boot screen and destroys time_facet object
  //dynamic allocation of tFacet_ required for proper operation
  ~LCDController(){
	  exit_ = true;
	  Wait();
    lcd_->BootScreen();
  }

};


#endif
