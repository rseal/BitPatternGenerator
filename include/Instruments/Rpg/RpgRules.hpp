#ifndef RPG_RULES_H
#define RPG_RULES_H

#include <bpg-v2/Common/IRules.hpp>
#include <bpg-v2/Instruments/Rpg/RpgTypes.hpp>
#include <bpg-v2/Instruments/Rpg/RpgIIF.hpp>

using namespace rpg;

class RpgRules: public IRules{
  
protected:
  RpgIIF iif_;
  PatternVector ports_;

public:
  RpgRules(): ports_(32){}
  PatternVector& PortRef() { return ports_;}
  RpgIIF& IIFRef() { return iif_;}
};

#endif