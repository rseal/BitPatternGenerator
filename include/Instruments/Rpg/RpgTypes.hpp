#ifndef PSU1_TYPES_H
#define PSU1_TYPES_H

#include <vector>
#include <boost/dynamic_bitset.hpp>

namespace rpg{
  typedef std::vector<unsigned long> StateVector;
  typedef std::vector<unsigned long> DurationVector;
  typedef boost::dynamic_bitset<> Pattern;
  typedef std::vector<Pattern> PatternVector;
  typedef std::vector<unsigned long> SignalVector;
};


#endif
