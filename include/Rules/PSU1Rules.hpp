#ifndef PSU1RULES_H
#define PSU1RULES_H

#include "../Keywords.hpp"
#include "../Signal.hpp"
#include "../Unit.hpp"
#include "../Location.hpp"

#include "../IRules.hpp"
#include "../InstrumentRuleFactory.hpp"
#include <boost/spirit/include/classic_spirit.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/dynamic_bitset.hpp>
#include <boost/bind.hpp>
#include <vector>
#include <iostream>

using namespace std;
using namespace boost::spirit::classic;
using namespace boost;

class PSU1Rules: public IRules{
  // typedef vector<Unit> UnitVector;
  // typedef vector<Location> LocationVector;
  typedef dynamic_bitset<> Pattern;
  typedef vector<Pattern> PatternVector;
  //due to spirit rules non-copy problem, we can't simply
  //create a vector here.
    TRKeyword      trKey;
    TXAKeyword     txaKey;
    CODEKeyword    codeKey;
    GenericKeyword gKey;
    TYPE1Keyword   t1Key;
    TYPE2Keyword   t2Key;
    SAKeyword      saKey;

public:

  void Detect(const TokenVector& tokenVector){
    for(int i=0; i<tokenVector.size(); ++i){
      trKey.Process(tokenVector[i]);
      txaKey.Process(tokenVector[i]);
      codeKey.Process(tokenVector[i]);
      gKey.Process(tokenVector[i]);
      t1Key.Process(tokenVector[i]);
      t2Key.Process(tokenVector[i]);
      saKey.Process(tokenVector[i]);
    }
  };

  const bool Verify(){
    
    float txa_l   = txaKey.GetParameter<float>("width");
    float bauda_l = t1Key.GetParameter<float>("bauda")*1e6;
    float baudb_l = t1Key.GetParameter<float>("baudb")*1e6;
    float code_l  = codeKey.GetParameter<float>("width")*bauda_l;
    float rfclk   = t1Key.GetParameter<float>("refclock");
    float ipp     = t1Key.GetParameter<float>("ipp")*1e6;
    float ipp_b   = rfclk/ipp;
    float dc      = txa_l/ipp;      
    
    vector<LocationVector> gParamLocs;
    vector<LocationVector> saParamLocs;
    PatternVector gParamPattern;
    ParameterVector gParam    = gKey.GetParameterRef();
    ParameterVector saParam   = saKey.GetParameterRef();
    LocationVector trLocVec   = trKey.GetParameter<LocationVector>("location");
    LocationVector txaLocVec  = txaKey.GetParameter<LocationVector>("location");
    LocationVector codeLocVec = codeKey.GetParameter<LocationVector>("location");
    LocationVector alv = trLocVec;
    alv.insert(alv.end(),txaLocVec.begin(),txaLocVec.end());
    alv.insert(alv.end(),codeLocVec.begin(),codeLocVec.end());

    //verify that code width matches the transmitted pulse width
    if(txa_l != code_l) throw std::runtime_error("PSU1Rules - TXA width != CODE width");
    
    //verify that code width matches the transmitted pulse width
    if(dc > .02f) throw std::runtime_error("PSU1Rules - DUTY CYCLE too high");

    //both generic and SA keywords can store multiple signals
    //this means that there can be more than 1 location vector
    //i.e. we must parse manually
    for(int i=0; i<gParam.size(); i=i+2){
      gParamLocs.push_back(any_cast<LocationVector>(gParam[i].value));
      gParamPattern.push_back(any_cast<Pattern>(gParam[i+1].value));
    } 
    
    //SA can have more than one window
    for(int i=0; i<saParam.size(); i=i+5)
      saParamLocs.push_back(any_cast<LocationVector>(saParam[i].value));

    //append generic and SA signal locations to list
    for(int i=0; i<gParamLocs.size(); ++i)
      alv.insert(alv.end(),gParamLocs[i].begin(),gParamLocs[i].end());
    for(int i=0; i<saParamLocs.size(); ++i)
      alv.insert(alv.end(),saParamLocs[i].begin(),saParamLocs[i].end());

    //lazy way to check for duplicate signal assignments
    for(int i=0; i<alv.size(); ++i)
      for(int j=i+1; j<alv.size(); ++j)
	if(alv[i].channel == alv[j].channel)
	  if(alv[i].port == alv[j].port){
	    cout << alv[i].port << "." << alv[i].channel << " = " 
		 << alv[j].port << "." << alv[j].channel << endl;
	    throw std::runtime_error("SIGNALS are assigned to the same port.channel");
	  }

    ParameterVector codeP = codeKey.GetParameterRef();

    return true;
  }


};

namespace PSU1
{
  IRules* Callback(){
    return new PSU1Rules();
  }

  const string id = "psu1";
  bool result = InstrumentRuleFactory::Instance().RegisterRule(id,Callback);
};


#endif  

