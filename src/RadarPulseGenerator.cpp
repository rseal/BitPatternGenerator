#include "../include/RadarPulseGenerator.hpp"

namespace RPG
{
  //static callback for factory registration
  IInstrumentDefinition* Callback(){ return new RadarPulseGenerator(); }
  bool result = InstrumentFactory::Instance().RegisterInstrument("rpg",RPG::Callback);
}

void RadarPulseGenerator::WriteIIF(){ cout << "writing output file" << endl;}
  
IRules & RadarPulseGenerator::GetRules(const string& fileName){
  
  string buffer;
  
  ifstream in(fileName.c_str());
  
  if(!in) throw runtime_error("RadarPulseGenerator::GetRules - Could not open" + fileName);
  
  while(!in.eof()){
    getline(in,buffer);
    StripToken(buffer);
    
    if(buffer.find("rules") != string::npos){
      int idx = buffer.find("=");
      transmitter_ = buffer.substr(idx+1,buffer.length());
    }
  }
  return *InstrumentRuleFactory::Instance().Create(transmitter_);
}

const TokenVector& RadarPulseGenerator::Tokenize(const string& fileName){
  
  string buffer;
  ifstream in(fileName.c_str());

  if(!in) throw runtime_error("FindInstrument:: Could not open" + fileName);
    
  while(!in.eof()){
    getline(in,buffer);
    StripToken(buffer);

    if(buffer.find("instrument")==string::npos && 
       buffer.find("rules")==string::npos &&
       buffer[0]!='\n' && !buffer.empty()){
      tokens_.push_back(buffer);
    }
  }
  return tokens_;
}
