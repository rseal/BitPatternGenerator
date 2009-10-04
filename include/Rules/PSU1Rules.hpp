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
#ifndef PSU1RULES_H
#define PSU1RULES_H

#include "../Keywords.hpp"
#include "../Unit.hpp"
#include "../Location.hpp"
#include "../IRules.hpp"
#include "../InstrumentRuleFactory.hpp"

#include <boost/dynamic_bitset.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/bind.hpp>
#include <vector>
#include <iostream>

using namespace std;
using namespace boost::spirit::classic;
using namespace boost;

class PSU1Rules: public IRules{
  typedef dynamic_bitset<> Pattern;
  typedef vector<Pattern> PatternVector;

  PatternVector ports_;

  //due to spirit rules non-copy problem, we can't simply
  //create a vector here.
  TRKeyword      trKey;
  TXAKeyword     txaKey;
  CODEKeyword    codeKey;
  GenericKeyword gKey;
  TYPE1Keyword   t1Key;
  TYPE2Keyword   t2Key;
  SAKeyword      saKey;

  template<typename T>
  const T FindParam(const ParameterVector& pv, const string& id){
    ParameterVector::const_iterator iter = 
      std::find_if(pv.begin(), pv.end(), 
		   bind(&Parameter::id, _1) == id);
    if(iter == pv.end()) throw std::runtime_error("Parameter " + id + " could not be found");
    return any_cast<T>(iter->value);
  }

  const int GetChOffset(const LocationVector& lv, const int& chNum){
    return lv[chNum].channel + ((lv[chNum].port == 'a') ? 0 : 16);
  }

public:

  PSU1Rules(): ports_(32){};

  void Detect(const TokenVector& tv){
    
    for(int i=0; i<tv.size(); ++i){
      trKey.Process(tv[i]);
      txaKey.Process(tv[i]);
      codeKey.Process(tv[i]);
      gKey.Process(tv[i]);
      t1Key.Process(tv[i]);
      t2Key.Process(tv[i]);
      saKey.Process(tv[i]);
    }
  };

  const bool Verify(){

    int i,j,k,ch;
    int h0,hf;
    bool isNeg;

    //contains tuple<LocationVector, Pattern, float>
    //single entry
    const vector<CodeTuple>& cTuple = codeKey.GetTupleRef();

    //contains tuple<LocationVector, float, float>
    //single entry
    const vector<TrTuple>& trTuple  = trKey.GetTupleRef();

    //contains tuple<LocationVector, float>
    //single entry
    const vector<TxaTuple>& txaTuple = txaKey.GetTupleRef();

    //contains tuple<LocationVector, bool, float, float>
    //multiple entries
    const vector<SaTuple>& saTuple = saKey.GetTupleRef();

    //contains tuple<LocationVector, Pattern>
    //multiple entries
    const vector<GenericTuple>& gTuple = gKey.GetTupleRef();

    //contains simple Parameter
    //multiple entries
    const ParameterVector& t1Tuple   = t1Key.GetTupleRef();

    //contains simple Parameter
    //single entry
    const ParameterVector& t2Tuple   = t2Key.GetTupleRef();

    const float txa_l   = txaTuple[0].get<1>();
    const float bauda_l = FindParam<float>(t1Tuple, "bauda")*1e6;
    const float baudb_l = FindParam<float>(t1Tuple, "baudb")*1e6;
    const float rfclk   = FindParam<float>(t1Tuple, "refclock")*1e6;
    const float ipp     = FindParam<float>(t1Tuple, "ipp")*1e6;
    const float ipp_b   = rfclk/ipp;
    const float dc      = txa_l/ipp;      
    const float code_l  = cTuple[0].get<2>()*bauda_l;
    
    //verify that code width matches the transmitted pulse width
    if(txa_l != code_l) {
      cerr << "TXA Pulse Width != CODE Pulse Width => " << txa_l << " != " << code_l << endl;
      throw std::runtime_error("PSU1Rules: TXA length != CODE length");
    }

    //verify that code width matches the transmitted pulse width
    if(dc > .02f) throw std::runtime_error("PSU1Rules - DUTY CYCLE too high");
    
    float chLengthA = ipp/bauda_l;
    float chLengthB = ipp/baudb_l;

    //resize port A channels to proper length
    for(i=0; i<16; ++i)
      ports_[i].resize(chLengthA);

    //resize port B channels to proper length
    for(i=16; i<32; ++i)
      ports_[i].resize(chLengthB);

    //store all locations and compare to 
    //ensure unique assignments
    LocationVector tLoc;
    
    //push generic locations 
    for(i=0; i<gTuple.size(); ++i){
      LocationVector t = gTuple[i].get<0>();
      tLoc.insert(tLoc.end(), t.begin(), t.end());
    }

    //push sa locations 
    for(i=0; i<saTuple.size(); ++i){
      LocationVector t = saTuple[i].get<1>();
      tLoc.insert(tLoc.end(), t.begin(), t.end());
    }

    //push all other locations
    LocationVector t = txaTuple[0].get<0>();
    tLoc.insert(tLoc.end(), t.begin(), t.end() );
    t = trTuple[0].get<0>();
    tLoc.insert(tLoc.end(), t.begin(), t.end() );
    t = cTuple[0].get<0>();
    tLoc.insert(tLoc.end(), t.begin(), t.end() );

    //lazy way to check for duplicate signal assignments
    for(i=0; i<tLoc.size(); ++i)
      for(j=i+1; j<tLoc.size(); ++j)
	if(tLoc[i].channel == tLoc[j].channel)
	  if(tLoc[i].port == tLoc[j].port){
	    cout << tLoc[i].port << "." << tLoc[i].channel << " ";
	    throw std::runtime_error("SIGNALS are assigned to the same port.channel");
	  }

    //VERIFICATION PASSED at this point
    
    //(1) BUILD TR Signal
    const float pre         = trTuple[0].get<1>();
    const float post        = trTuple[0].get<2>();
    const float trWidth     = pre + txa_l + post;
    LocationVector lv = trTuple[0].get<0>();
    int sz = lv.size();
    
    //(1) BUILD TR SIGNAL
    for(i=0; i<sz; ++i){
      for(j=0; j<trWidth; ++j)
	ports_[lv[i].channel+GetChOffset(lv,i)].set(j,true);
      cout << ports_[ lv[i].channel + GetChOffset(lv,i)] << endl << endl;
    }

    //(2) BUILD TXA Signal
    lv = txaTuple[0].get<0>();
    sz = lv.size();
    for(i=0; i<sz; ++i){
      for(j=pre; j<txa_l; ++j)
	ports_[lv[i].channel+GetChOffset(lv,i)].set(j,true);
      cout << ports_[ lv[i].channel + GetChOffset(lv,i)] << endl << endl;
    }

    //(3) BUILD CODE Signal
    lv = cTuple[0].get<0>();
    const Pattern p = cTuple[0].get<1>();
    sz = lv.size();
    for(i=0; i<sz; ++i){
      ch = lv[i].channel + GetChOffset(lv,i);
      for(j=0; j<p.size(); ++j) ports_[ch][pre+j] = p[j];
      cout << ports_[ch] << endl << endl;
    }

    //(4) BUILD SA SIGNALS
    // These are the sampling windows
    // There is a negate option to correctly trigger Julio's system.
    for(i=0; i<saTuple.size(); ++i){
      lv    = saTuple[i].get<1>();
      isNeg = saTuple[i].get<2>(); 
      h0    = static_cast<int>(saTuple[i].get<3>());
      hf    = static_cast<int>(saTuple[i].get<4>());
      for(j=0; j<lv.size(); ++j){
	ch = lv[j].channel + GetChOffset(lv,j);	
	for(k=h0; k<hf; ++k) ports_[ch][k]=true;
	if(isNeg) ports_[ch].flip(); 
      } 
    }

    //(5) BUILD GENERIC SIGNALS
    for(i=0; i<gTuple.size(); ++i){
      lv = gTuple[i].get<0>();
      const Pattern p = gTuple[i].get<1>();
      for(j=0; j<lv.size(); ++j){
	const int ch = lv[j].channel + GetChOffset(lv,j);
	ports_[ch] = p;
	ports_[ch].resize(('a'==lv[j].port)? chLengthA : chLengthB);
      } 
    }
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

