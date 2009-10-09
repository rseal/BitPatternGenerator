
#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <boost/algorithm/string.hpp>

#include <bpg-v2/Common/InstrumentFactory.hpp>
#include <bpg-v2/Common/InstrumentFinder.hpp>


using namespace std;
using namespace boost;

IInstrumentDefinition& InstrumentFinder::Find(const File& fileName) {

  bool found = false;
  string buffer;
  ifstream in(fileName.c_str());
  
  if(!in) throw runtime_error("FindInstrument:: Could not open " + fileName);
  
  while(!in.eof() && !found){
    getline(in,buffer);

    //remove all whitespace from the input string
    replace_all(buffer," ","");
    to_lower(buffer);
    int idx = buffer.find("#");
    buffer = buffer.substr(0,idx);
      
    if(buffer.find("instrument") != string::npos){
      int idx = buffer.find("=");
      instrument_ = buffer.substr(idx+1,buffer.length());
      found = true;
    }
  }

  if(!found) throw runtime_error("FindInstrument:: Could not locate " + instrument_ + " Instrument");

  return *InstrumentFactory::Instance().Create(instrument_);
}
