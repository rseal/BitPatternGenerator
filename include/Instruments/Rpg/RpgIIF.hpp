#ifndef RPG_IIF_H
#define RPG_IIF_H

#include <bpg-v2/Instruments/Rpg/RpgTypes.hpp>

struct RpgIIF{
public:

  ulong portLength;
  rpg::SignalVector stateVectorA;
  rpg::SignalVector stateVectorB;
  rpg::SignalVector durVectorA;
  rpg::SignalVector durVectorB;
  ulong clkDivA;
  ulong clkDivB;
  uint numStatesA;
  uint numStatesB;

  RpgIIF():portLength(2048){}
  
};



#endif
