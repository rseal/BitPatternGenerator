#ifndef OPTION_H
#define OPTION_H

#include <iostream>

//!\brief Provides an interface for defining switches on the command line. 
class Option{
protected:
  std::string name_;
  std::string helpDesc_;
    bool required_;
    bool set_;
public:
  Option(const std::string& name, const std::string& helpDesc, const bool& required):
	name_(name), helpDesc_(helpDesc), required_(required), set_(false) {}

    void Set(bool const& state) { set_ = state;     }
    const bool& Set()           { return set_;      }
  const std::string& Name()        { return name_;     }
  const std::string& Help()        { return helpDesc_; }
};
#endif
