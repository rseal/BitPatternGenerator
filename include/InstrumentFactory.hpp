#ifndef INSTRUMENT_RULE_H
#define INSTRUMENT_RULE_H

#include <map>
#include <memory>
#include <iostream>
#include <stdexcept>
#include "IInstrumentDefinition.hpp"

using namespace std;

struct InstrumentFactory{

  typedef IInstrumentDefinition* (*CreateRuleCallback)(); 
  typedef map<string, CreateRuleCallback> InstrumentMap;
  InstrumentMap iMap_;
  static InstrumentFactory* pInstance_;
  static bool destroyed_;

  //disable CTOR and copy, and assignment capabilities
  InstrumentFactory(){};
  InstrumentFactory(const InstrumentFactory&);
  InstrumentFactory& operator=(const InstrumentFactory&);
  
  virtual ~InstrumentFactory(){
    pInstance_=0;
    destroyed_=true;
  }

public:

  //create single instance
  static InstrumentFactory& Instance(){
    if(!pInstance_){
      if(destroyed_) throw runtime_error("Dead reference detected");
      else{
	static InstrumentFactory obj;
	pInstance_ = &obj;
      }
    }
      return *pInstance_;
  }
  
  //Every class must register its callback here
  const bool RegisterInstrument(const string& id , CreateRuleCallback createFun){
    InstrumentMap::iterator iter = iMap_.find(id);
    return iMap_.insert( InstrumentMap::value_type(id,createFun)).second;
  }
  
  const bool UnregisterInstrument(const string& id){
    return iMap_.erase(id)==1;
  }

  //Return object of specified type or throw exception
  IInstrumentDefinition* Create(const string& id){
    InstrumentMap::const_iterator iter = iMap_.find(id);
    if(iter == iMap_.end()){
      throw std::runtime_error("InstrumentFactory - Unknown Rule ID " + id);
    }
    return (iter->second)();
  }

private:
};


#endif
