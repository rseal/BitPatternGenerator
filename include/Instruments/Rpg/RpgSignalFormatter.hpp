#ifndef RPG_SIGNAL_FORMATTER_H
#define RPG_SIGNAL_FORMATTER_H

#include <bpg-v2/Instruments/Rpg/RpgTypes.hpp>

class RpgIIF;

struct RpgSignalFormatter{

  void BuildVector(rpg::PatternVector& pv, rpg::StateVector& sv, rpg::DurationVector& dv);

public:

  void operator()(const rpg::PatternVector& ports, RpgIIF& iif);
};

#endif
