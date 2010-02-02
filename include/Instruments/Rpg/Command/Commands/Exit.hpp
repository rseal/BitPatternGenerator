#ifndef EXIT_H
#define EXIT_H

#include <iostream>

///\brief sets the exit variable passed by the main routine to exit the program.
class Exit: public Command{
  int& exit_;
public:
  Exit(const std::string& name, const std::string& description, int& exit): 
    Command(name,description),exit_(exit){};
  virtual ~Exit(){};
  virtual void Execute(){ exit_ = 1;}  
};

#endif
