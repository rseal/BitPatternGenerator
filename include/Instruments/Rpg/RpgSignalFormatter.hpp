#ifndef RPG_SIGNAL_FORMATTER_H
#define RPG_SIGNAL_FORMATTER_H

#include <bpg-v2/Instruments/Rpg/RpgTypes.hpp>
#include <bpg-v2/Instruments/Rpg/RpgIIF.hpp>

#include <iostream>

using namespace std;

struct RpgSignalFormatter{

  void BuildVector(PatternVector& pv, StateVector& sv, DurationVector& dv);

public:

  void operator()(const PatternVector& ports, RpgIIF& iif);
};

#endif
