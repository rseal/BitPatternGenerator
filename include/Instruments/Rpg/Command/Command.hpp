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
