// Copyright (c) 2009 Ryan Seal <rlseal -at- gmail.com>
//
// This file is part of Bit Pattern Generator (BPG) Software.
//
// BPG is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//  
// BPG is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with BPG.  If not, see <http://www.gnu.org/licenses/>.
#ifndef INSTRUMENT_RULE_FACTORY_H
#define INSTRUMENT_RULE_FACTORY_H

#include <map>
#include <memory>
#include <iostream>
#include <stdexcept>
#include "IRules.hpp"

using namespace std;

struct InstrumentRuleFactory{

  typedef IRules* (*CreateRuleCallback)(); 
  typedef map<string, CreateRuleCallback> InstrumentRuleMap;
  InstrumentRuleMap iMap_;
  static InstrumentRuleFactory* pInstance_;
  static bool destroyed_;

  //disable CTOR and copy, and assignment capabilities
  InstrumentRuleFactory(){};
  InstrumentRuleFactory(const InstrumentRuleFactory&);
  InstrumentRuleFactory& operator=(const InstrumentRuleFactory&);
  
  virtual ~InstrumentRuleFactory(){
    pInstance_=0;
    destroyed_=true;
  }

public:

  //create single instance
  static InstrumentRuleFactory& Instance(){
    if(!pInstance_){
      if(destroyed_) throw runtime_error("Dead reference detected");
      else{
	static InstrumentRuleFactory obj;
	pInstance_ = &obj;
      }
    }
      return *pInstance_;
  }
  
  //Every class must register its callback here
  const bool RegisterRule(const string& id , CreateRuleCallback createFun){
    InstrumentRuleMap::iterator iter = iMap_.find(id);
    return iMap_.insert( InstrumentRuleMap::value_type(id,createFun)).second;
  }
  
  const bool UnregisterRule(const string& id){
    return iMap_.erase(id)==1;
  }

  //Return object of specified type or throw exception
  IRules* Create(const string& id){
    InstrumentRuleMap::const_iterator iter = iMap_.find(id);
    if(iter == iMap_.end()){
      throw std::runtime_error("InstrumentRuleFactory - Unknown Rule id " + id);
    }
    return (iter->second)();
  }

private:
};


#endif
