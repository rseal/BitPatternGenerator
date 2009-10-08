#include <bpg-v2/Instruments/Rpg/RadarPulseGenerator.hpp>

namespace RPG
{
  //static callback for factory registration
  IInstrumentDefinition* Callback(){ return new RadarPulseGenerator(); }
  bool result = InstrumentFactory::Instance().RegisterInstrument("rpg",RPG::Callback);
}

void RadarPulseGenerator::WriteIIF(const string& fileName){
  RpgSignalFormatter sf;
  RpgIIF& iif          = rules_->IIFRef();
  PatternVector& ports = rules_->PortRef();
  sf(ports,iif);

  
  ofstream out(fileName.c_str(), ios::out);
  if(!out) throw std::runtime_error("Output File " + fileName + " could not be opened");
  
  SignalVector::const_iterator sAIter = iif.stateVectorA.begin();
  SignalVector::const_iterator sBIter = iif.stateVectorB.begin();
  SignalVector::const_iterator dAIter = iif.durVectorA.begin();
  SignalVector::const_iterator dBIter = iif.durVectorB.begin();
  
  for(uint i=0; i<iif.portLength; ++i){
    out << *(sAIter++) << endl;
    out << *(dAIter++) << endl;
  }
  out << iif.clkDivA << endl;
  out << iif.numStatesA << endl;
  //add clock divider a

  for(uint i=0; i<iif.portLength; ++i){
    out << *(sBIter++) << endl;
    out << *(dBIter++) << endl;
  }
  out << iif.clkDivB << endl;
  out << iif.numStatesB << endl;
  //add clock divider b

  cout << "writing output file" << endl;
}
  
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

  rules_ = dynamic_cast<RpgRules*>(InstrumentRuleFactory::Instance().Create(transmitter_));
  
  return *rules_;
}

void RadarPulseGenerator::Tokenize(const string& fileName){

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
}

