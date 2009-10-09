#ifndef RPG_SIGNAL_FORMATTER_H
#define RPG_SIGNAL_FORMATTER_H


struct RpgSignalFormatter{

  void BuildVector(rpg::PatternVector& pv, rpg::StateVector& sv, rpg::DurationVector& dv);

public:

  void operator()(const rpg::PatternVector& ports, RpgIIF& iif);
};

#endif
