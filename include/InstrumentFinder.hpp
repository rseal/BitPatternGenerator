#ifndef INSTRUMENT_FINDER_H
#define INSTRUMENT_FINDER_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <boost/algorithm/string.hpp>
#include "InstrumentFactory.hpp"

//#include "IRules.hpp"
//#include "PSU1Rules.hpp"

using namespace std;
using namespace boost;

//Rule interface
class InstrumentFinder{

  typedef vector<string> TokenVector;
  typedef string File;
  TokenVector tokens_;
  
public:

  IInstrumentDefinition* FindInstrument(const File& fileName){
    string instrument;
    string buffer;

    ifstream in(fileName.c_str());

    if(!in) throw runtime_error("FindInstrument:: Could not open " + fileName);
    
    while(!in.eof()){
      getline(in,buffer);

      //remove all whitespace from the input string
      replace_all(buffer," ","");
      to_lower(buffer);
      int idx = buffer.find("#");
      buffer = buffer.substr(0,idx);

      if(buffer.find("instrument") != string::npos){
	int idx = buffer.find("=");
	instrument = buffer.substr(idx+1,buffer.length());
      }
    }
    return InstrumentFactory::Instance().Create(instrument);
  }

  //virtual void WriteIIF()=0;
};

#endif
