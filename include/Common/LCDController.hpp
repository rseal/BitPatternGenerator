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
#include <bpg-v2/Common/SThread.hpp>
#include <bpg-v2/Common/LCD.hpp>
#include <sstream>
#include <iostream>

class LCDController : public SThread {

  typedef boost::posix_time::ptime Time;
  typedef boost::posix_time::time_duration Duration;
  
  LCD& lcd_;

  bool running_;
  bool exit_;
  std::string mode_;
  std::stringstream ostr;

  boost::posix_time::time_facet* tFacet_;
  Time startTime_;
  Time modeTime_;
  Time currentTime_;
  Duration elapsedTime_;
  Mutex mutex_;
  bool newMode_;

  const string ElapsedTime(){
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

  const string CurrentTime(){
    ostr.str("");
    currentTime_ = boost::posix_time::second_clock::local_time();
    ostr << currentTime_;
    return ostr.str();
  }

  const string StartTime(){
    ostr.str("");
    ostr << startTime_;
    return ostr.str();
  }

public:

  LCDController(LCD& lcd): lcd_(lcd), exit_(false), running_(false), newMode_(true){
    tFacet_ = new  boost::posix_time::time_facet("%r %z");
    ostr.imbue(std::locale(ostr.getloc(),tFacet_));
    lcd_.Init();
  }

  void Start() { 
    startTime_ = boost::posix_time::second_clock::local_time();
    running_ = true;
    StartThread();
  }

  void Stop() { running_ = false; }

  void Mode(const string& mode) { 
    mode_=mode;
    newMode_ = true;
  }

  void Run(){
    while (!exit_) {
      //sleep for one second then update display
      Sleep(SEC,1);

      if(newMode_){
	    modeTime_ = boost::posix_time::second_clock::local_time();
	    newMode_=false;
      }
      string cTime = CurrentTime();
      string eTime = ElapsedTime();

      lcd_.Message(0,"   Mode: " + mode_);
      lcd_.Message(1,"Elapsed: " + eTime);
      lcd_.Message(2,"  Start: " + StartTime());
      lcd_.Message(3," System: " + cTime); 
      lcd_.Update();
    }
  }

  void Exit() { exit_ = true;}
  
  ~LCDController(){
    delete tFacet_;
    cout << "LCDController DTOR called" << endl;
  }
};


#endif
