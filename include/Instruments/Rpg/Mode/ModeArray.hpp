///////////////////////////////////////////////////////////////////////////////////////
///\file.h
///
///The ModeArray stores all the added modes.  The array structure allows automatic
///switching of the Modes by the shell program.
///
//////////////////////////////////////////////////////////////////////////////////////

#ifndef MODEARRAY_H
#define MODEARRAY_H

#include <vector>
#include <iostream>
#include <bpg-v2/Instruments/Rpg/Mode/Mode.hpp>
#include <iomanip>

///\brief The ModeArray structure holds the modes in a vector with indexes to the current
///and next Modes
struct ModeArray{
  typedef std::vector<Mode> Array;
  unsigned int current_;
  unsigned int next_;
  Array modeArray_;

public:

  ///\brief default constuctor with empty vector
  ModeArray(): current_(0), next_(1) {}

  ///\brief adds a Mode to the end of the vector
  void Add(const Mode& mode) {modeArray_.push_back(mode);}

  ///\brief returns the next mode in the vector
  Mode Next() {
    Mode ret;

    if(modeArray_.empty())
      std::cerr << "ModeArray::NextMode() - No modes allocated" << std::endl;
    else{
      current_ = next_;
      if(++next_ == modeArray_.size()) next_ = 0;
      ret = modeArray_[next_];
    }
	
    return ret;
  }

  ///\brief outputs current number of modes
  const int NumModes() { return modeArray_.size();}

  ///\brief returns a reference to the ModeArray
  Array& GetArray() { return modeArray_;}

  ///\brief searches for Mode by name, and removes if found
  const bool Remove(const std::string& name) {
    Array::iterator iter = modeArray_.begin();
    bool found = false;
    
    while(iter != modeArray_.end() && !found){
      if(iter->Name() == name){
	modeArray_.erase(iter);
	found = true;
      }
      ++iter;
    }
    return found;
  }

  const std::vector<std::string> Names(){
    std::vector<std::string> names;
    Array::iterator iter = modeArray_.begin();
    while(iter != modeArray_.end()){
      names.push_back(iter->Name());
      ++iter;
    }
    return names;
  }

  void Print(){
    Array::iterator iter = modeArray_.begin();
    std::setfill(' ');
    while(iter != modeArray_.end()){
      std::cout << "       "
	   << iter->Name() 
	   << std::endl;
      ++iter;
    }
  }

};

#endif

