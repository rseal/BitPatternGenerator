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
#include <iostream>
#include <boost/tuple/tuple.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

#include <bpg-v2/Instruments/Rpg/RpgRules.hpp>
#include <bpg-v2/Common/Keyword.hpp>
#include <bpg-v2/Common/Unit.hpp>
#include <bpg-v2/Common/Location.hpp>
#include <bpg-v2/Rules/Arecibo/Rules.hpp>

using namespace std;
using namespace boost;
using namespace rpg;

namespace arecibo{
  
  IRules* Callback(){ return new Rules(); }
  bool result = InstrumentRuleFactory::Instance().RegisterRule("arecibo",Callback);


void Rules::Detect(const TokenVector& tv){
    
  for(uint i=0; i<tv.size(); ++i){
    phaseKey.Process(tv[i]);
    bwKey.Process(tv[i]);
    gKey.Process(tv[i]);
    saKey.Process(tv[i]);
    t1Key.Process(tv[i]);
    t2Key.Process(tv[i]);
    t3Key.Process(tv[i]);
  }

};

const bool Rules::Verify(){

  typedef vector<PhaseTuple>     PhaseTupleVec;
  typedef vector<BaudwidthTuple> BWTupleVec;
  typedef vector<SaTuple>        SaTupleVec;
  typedef vector<GenericTuple>   GenTupleVec;

  uint i,j,k,ch;
  uint h0,hf;
  bool isNeg;
  LocationVector tLoc;

  //delay all signals 2 baud to initialize RiIPP and TxIPP
  // 1 at t=0 and 0 at t=1 and all other signals at t=2
  const int initDelay = 2;

  //Klystrons need time to stabilize before transmitting
  const float beamWarmUp = 10e-6;

  //6% is the maximum duty cycle allowable 
  const float maxDutyCycle = .06;
  
  //contains tuple<Pattern, uint, bool> - single entry
  const PhaseTupleVec& pTuple    = phaseKey.GetTupleRef();

  //contains tuple<float, float> - /single entry
  const BWTupleVec& bwTuple      = bwKey.GetTupleRef();

  //contains tuple<LocationVector, bool, float, float> - multiple entries
  const SaTupleVec& saTuple      = saKey.GetTupleRef();

  //contains tuple<LocationVector, Pattern> - multiple entries
  const GenTupleVec& gTuple      = gKey.GetTupleRef();

  //contains simple Parameter - multiple entries
  const ParameterVector& t1Vec   = t1Key.GetTupleRef();

  //contains Parameter holding float - multiple entries
  const ParameterVector& t2Vec   = t2Key.GetTupleRef();

  //contains tuple<LocationVector, float> - multiple entries
  const ParameterVector& t3Vec   = t3Key.GetTupleRef();

  //Type2 keywords are refclock or ipp
  const float rfclk = any_cast<float>(param::FindParameter(t2Vec, "refclock").value);
  const float ipp   = any_cast<float>(param::FindParameter(t2Vec, "ipp").value);
  cout << "ipp = " << ipp << endl; 

  const float baudA = bwTuple[0].get<0>();
  const float baudB = bwTuple[0].get<1>();

  //workaround for nasty floating point precision behavior
  volatile const float divClkA   = rfclk*baudA/2.0;
  volatile const float divClkB   = rfclk*baudB/2.0;
  volatile const float chLengthA = ipp/baudA;
  volatile const float chLengthB = ipp/baudB;

  //resize port A channels to proper length
  for(i=0; i<16; ++i)
    ports_[i].resize(chLengthA);

  //resize port B channels to proper length
  for(i=16; i<32; ++i)
    ports_[i].resize(chLengthB);

  iif_.clkDivA = divClkA;
  iif_.clkDivB = divClkB;


  const Type3Tuple& beamTuple = any_cast<Type3Tuple>(param::FindParameter(t3Vec, "beam").value);
  const float beam = beamTuple.get<1>();
  const float beam_l = beam*1e6;
  
  const Type3Tuple& txTuple  = any_cast<Type3Tuple>(param::FindParameter(t3Vec, "txwin").value);
  const unsigned int txWin_l = 
    static_cast<unsigned int>(txTuple.get<1>() + beam_l + initDelay);

  const float dutyCycle = beam/ipp;
  const string dcStr = lexical_cast<string>(maxDutyCycle);
  if(dutyCycle > maxDutyCycle) 
    throw std::runtime_error("Maximum Duty Cycle of " + dcStr + " exceeded");
  
  const Pattern& phase = pTuple[0].get<0>();
  const unsigned int phaseLength = pTuple[0].get<1>();
 
  const bool isCLP = pTuple[0].get<2>();

  if(phaseLength + beamWarmUp > beam_l) 
    throw std::runtime_error("Phase code is longer than the BEAM width");

  //TXIPP Locations
  LocationVector txLocs = any_cast<LocationVector>(param::FindParameter(t1Vec, "txipp").value);
  tLoc.insert(tLoc.end(), txLocs.begin(), txLocs.end());
  
  //RIIPP Locations
  LocationVector riLocs = any_cast<LocationVector>(param::FindParameter(t1Vec, "riipp").value);
  tLoc.insert(tLoc.end(), riLocs.begin(), riLocs.end());

  //RF Locations
  LocationVector rfLocs = any_cast<LocationVector>(param::FindParameter(t1Vec, "rf").value);
  tLoc.insert(tLoc.end(), rfLocs.begin(), rfLocs.end());

  //Beam Locations
  LocationVector beamLocs = beamTuple.get<0>();
  tLoc.insert(tLoc.end(), beamLocs.begin(), beamLocs.end());

  //TXWIN Locations
  LocationVector txWinLocs = txTuple.get<0>();  
  tLoc.insert(tLoc.end(), txWinLocs.begin(), txWinLocs.end());

  //GENERIC Locations
  for(i=0; i<gTuple.size(); ++i){
    LocationVector t = gTuple[i].get<0>();
    tLoc.insert(tLoc.end(), t.begin(), t.end());
  }

  //SA Locations 
  for(i=0; i<saTuple.size(); ++i){
    LocationVector t = saTuple[i].get<0>();
    tLoc.insert(tLoc.end(), t.begin(), t.end());
  }
  
  //PHASE Location
  tLoc.push_back(Location('a',15));

  //lazy way to check for duplicate signal assignments
  for(i=0; i<tLoc.size(); ++i)
    for(j=i+1; j<tLoc.size(); ++j)
      if(tLoc[i].channel == tLoc[j].channel)
	if(tLoc[i].port == tLoc[j].port){
	  throw std::runtime_error("ENTRY: " + 
				   lexical_cast<string>(tLoc[i].port) + "." +
				   lexical_cast<string>(tLoc[i].channel) + 
				   " has multiple signals assigned");
	}

  //Verification passed, now BUILD Signals

  //(1) BUILD TXIPP Signal
  unsigned int sz = txLocs.size();
  unsigned int mx = 1;
  for(i=0; i<sz; ++i){
    for(j=0; j<mx; ++j)
      ports_[ChIndex(txLocs,i)].set(j,true);
  }

  //(2) BUILD RIIPP Signal
  sz = riLocs.size();
  mx = 1;
  for(i=0; i<sz; ++i){
    for(j=0; j<mx; ++j)
      ports_[ChIndex(riLocs,i)].set(j,true);
  }

  //(3) BUILD BEAM Signal
  sz = beamLocs.size();
  mx = static_cast<unsigned int>(beam_l) + initDelay;
  for(i=0; i<sz; ++i){
    for(j=initDelay; j<mx; ++j)
      ports_[ChIndex(beamLocs,i)].set(j,true);
  }

  //(4) BUILD TXWIN Signal
  sz = txWinLocs.size();
  for(i=0; i<sz; ++i){
    for(j=initDelay; j<txWin_l; ++j)
      ports_[ChIndex(txWinLocs,i)].set(j,true);
  }

  //(5) BUILD PHASE and RF Signals
  sz = rfLocs.size();
  unsigned int pStart = beam_l + initDelay - phaseLength - 1;
  unsigned int pEnd   = phaseLength;
  for(i=0; i<pEnd; ++i){
    ports_[15].set(i+pStart,phase[i]);
    for(j=0; j<sz; ++j) 
      ports_[ChIndex(rfLocs,j)].set(i+pStart,true);
  }

 
  for(i=0; i<saTuple.size(); ++i){
     LocationVector lv = saTuple[i].get<0>();
     for(int j=0; j<lv.size(); ++j)
        cout << "Port " << lv[j].port <<  " Channel " << lv[j].channel << endl;

     cout << "isNeg    " << saTuple[i].get<1>() << "\n"
        << "h0       " << saTuple[i].get<2>() << "\n"
        << "h1       " << saTuple[i].get<3>() << endl;
  }

  //(6) BUILD SA SIGNALS
  // These are the sampling windows
  for(i=0; i<saTuple.size(); ++i){
    tLoc    = saTuple[i].get<0>();
    isNeg = saTuple[i].get<1>(); 
    //transmitted signal begins at start of phase (pStart)
    h0    = static_cast<int>(saTuple[i].get<2>()) + pStart;
    hf    = static_cast<int>(saTuple[i].get<3>()) + pStart;
    cout << "h0=" << h0 << " hf=" << hf << endl;
    for(j=0; j<tLoc.size(); ++j){
      ch = ChIndex(tLoc,j);	
      for(k=h0; k<hf; ++k) ports_[ch][k]=true;
      if(isNeg) ports_[ch].flip(); 
    }
  }

  //(7) BUILD GENERIC SIGNALS
  for(i=0; i<gTuple.size(); ++i){
    tLoc = gTuple[i].get<0>();
    const Pattern p = gTuple[i].get<1>();
    for(j=0; j<tLoc.size(); ++j){
      const int ch = ChIndex(tLoc,j);
      ports_[ch] = p;
      ports_[ch].resize(('a'==tLoc[j].port)? chLengthA : chLengthB);
    } 
  }

  return true;
}

}; //namespace arecibo
