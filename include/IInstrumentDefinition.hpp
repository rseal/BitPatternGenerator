#ifndef IINSTRUMENT_DEFINITION_H
#define IINSTRUMENT_DEFINITION_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <boost/algorithm/string.hpp>

#include "IRules.hpp"
//#include "PSU1Rules.hpp"

using std::vector;
//using namespace boost;

//Rule interface
class IInstrumentDefinition{

public:
  typedef vector<string> TokenVector;

  virtual void WriteIIF()=0;
  virtual IRules* GetRules(const string& fileName)=0;
  virtual const TokenVector& Tokenize(const string& fileName)=0; 
private:

  //  TokenVector tokens_;
  // Instrument instrument_;

};

#endif
