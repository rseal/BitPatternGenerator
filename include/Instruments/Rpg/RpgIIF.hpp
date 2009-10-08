#ifndef RPG_IIF_H
#define RPG_IIF_H

#include <bpg-v2/Instruments/Rpg/RpgTypes.hpp>

using namespace rpg;

struct RpgIIF{
public:

  ulong portLength;
  SignalVector stateVectorA;
  SignalVector stateVectorB;
  SignalVector durVectorA;
  SignalVector durVectorB;
  ulong clkDivA;
  ulong clkDivB;
  uint numStatesA;
  uint numStatesB;

  RpgIIF():portLength(2048){}
  
};



#endif
