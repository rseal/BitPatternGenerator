#ifndef SWITCH_H
#define SWITCH_H

#include <iostream>
#include <bpg-v2/clp/Option.hpp>

//!\brief Provides an interface for defining switches on the command line. 
class Switch: public Option{
public:
  Switch(const std::string& name, const std::string& helpDesc, const bool& required):
	Option(name,helpDesc,required){};
};
#endif
