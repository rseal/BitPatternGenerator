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
////////////////////////////////////////////////////////////////////////////////////
///\file Command.h
///
///Base class for commands.
///
///Author: Ryan Seal, Alex Hackett
//Modified: 6/15/09
///////////////////////////////////////////////////////////////////////////////////

#ifndef COMMAND_H
#define COMMAND_H 

#include <iostream>
#include <vector>
#include <map>

#include <boost/shared_ptr.hpp>

//////////////////////////////////////////////////////////////////////////////////
///\brief The Command base class
//////////////////////////////////////////////////////////////////////////////////
class Command{
  bool valid_;
protected:
  typedef std::vector<std::string> ArgList;
  typedef std::map<std::string,int> ArgMap;

  //contains list of arguments parsed from input
  ArgList argList_;
  //provides mapping from std::string input to machine-readable command
  ArgMap argMap_;

  //holds command name and help description
  std::string name_;
  std::string description_;

  //this determines whether or not user should be prompted
  //to enter arguments
  const bool Interact() { return argList_.empty();}
public:
  Command(const std::string& name, const std::string& description): 
    name_(name), description_(description), valid_(false){}
  virtual ~Command(){};
  virtual void Execute() = 0;

  const bool&    Valid() { return valid_; };
  void           Valid(const bool& state) { valid_ = state; }

  //load argument list from parser
  void  Args(const ArgList argList) {
    argList_ = argList;
  }
  const ArgList& Args()        { return argList_;     }
  const std::string&  Name()        { return name_;        }
  const std::string&  Description() { return description_; }
};


#endif
