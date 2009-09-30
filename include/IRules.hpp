#ifndef IRULES_H
#define IRULES_H

#include <vector>
#include <iostream>

using std::vector;
using std::string;

//Rule interface
class IRules{
  
public:
  typedef vector<string> TokenVector;

  virtual void Detect(const TokenVector& tokenvector){};
  virtual const bool Verify(){};
};

#endif
