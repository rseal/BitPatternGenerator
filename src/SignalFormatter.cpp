#include <bpg-v2/Instruments/Rpg/RpgSignalFormatter.hpp>

void RpgSignalFormatter::operator()(const PatternVector& ports,){

    const int width      = 16;
    const int ipp        = ports[0].size();

    StateVector    svA,svB;
    DurationVector dvA,dvB;
    PatternVector  stateVecA;
    PatternVector  stateVecB;
    Pattern        state(width);

    for(int i=0; i<ipp; ++i){
      //load state on port A
      for(int j=0; j<width; ++j){ state[j] = ports[j][i]; }
      stateVecA.push_back(state);
      //load state on port B
      for(int j=0; j<width; ++j){ state[j] = ports[j+width][i];}
      stateVecB.push_back(state);
    }

    BuildVector(stateVecA,svA,dvA);
    iif.stateVectorA = svA;
    iif.durVectorA = dvA;

    BuildVector(stateVecB,svB,dvB);
    iif.stateVectorB = dvB;
    iif.durVectorB = dvB;
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
