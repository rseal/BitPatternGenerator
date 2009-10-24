#ifndef LCD_HPP
#define LCD_HPP

#include <vector>
#include <iostream>
#include <termios.h>
#include <stdexcept>

//Using NVI with one public virtual function
class LCD {

  virtual void Location(const int& line, const int& column)=0;
  virtual void Write(const string& str)=0;

protected:
  const std::string location_;
  int fileDescriptor_;
  termios oldParams_;
  termios newParams_;
  int columns_;
  std::vector<std::string> message_;

public:
  
  LCD(const int& line, const int& columns):
    message_(line), columns_(columns){}

  virtual void Init()=0;
  virtual void BootScreen()=0;
  virtual void Home()=0;

  void Update(){
    uint sz = message_.size();
    for(uint i=0; i<sz; ++i){
      Location(i,0);
      Write(message_[i]);
    }
  }

  virtual ~LCD(){}
 
  void Message(const int& line, const string& str){
    if(line > message_.size()) 
      throw std::runtime_error(" Requested LCD line number too large");
    message_[line] = str;
  };
};


#endif
