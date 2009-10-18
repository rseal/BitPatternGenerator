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

#include <bpg-v2/Instruments/Rpg/RpgTypes.hpp>
#include <bpg-v2/Instruments/Rpg/RpgIIF.hpp>
#include <bpg-v2/Instruments/Rpg/RpgSignalFormatter.hpp>

using namespace rpg;

void RpgSignalFormatter::operator()(const PatternVector& ports, RpgIIF& iif){

    const int width      = 16;
    const int ipp        = ports[0].size();

    StateVector    svA,svB;
    DurationVector dvA,dvB;
    PatternVector  stateVecA;
    PatternVector  stateVecB;
    Pattern        state(width);

    for(int i=0; i<ipp; ++i){
      //load state on port A
      //      cout << "PORTA STATES" << endl;
      for(int j=0; j<width; ++j){ state[j] = ports[j][i]; }{
	stateVecA.push_back(state);
	//	cout << state << endl;
      }
      //      cout << "PORTB STATES" << endl;
      //load state on port B
      for(int j=0; j<width; ++j){ state[j] = ports[j+width][i];}{
	//	cout << state << endl;
	stateVecB.push_back(state);
      }
    }

    BuildVector(stateVecA,svA,dvA);
    iif.numStatesA   = dvA.size();
    svA.resize(iif.portLength);
    dvA.resize(iif.portLength);
    iif.stateVectorA = svA;
    iif.durVectorA   = dvA;

    BuildVector(stateVecB,svB,dvB);
    iif.numStatesB   = dvB.size();
    svB.resize(iif.portLength);
    dvB.resize(iif.portLength);
    iif.stateVectorB = svB;
    iif.durVectorB   = dvB;
  }

void RpgSignalFormatter::BuildVector(PatternVector& pv, StateVector& sv, DurationVector& dv){
    int duration=0;     
     //store first state
    sv.push_back(pv[0].to_ulong());
   
    StateVector::iterator sIter         = sv.begin();
    PatternVector::const_iterator pIter = pv.begin();
    PatternVector::const_iterator pEnd  = pv.end();
    
    while(pIter != pEnd){
      if(*sIter != pIter->to_ulong()){
	sv.push_back(pIter->to_ulong());
	sIter = sv.end()-1;
	dv.push_back(duration);
	duration=0;
      }
      ++duration;
      ++pIter;
    }
    dv.push_back(duration);
  }
