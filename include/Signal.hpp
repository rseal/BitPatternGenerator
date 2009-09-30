#ifndef SIGNAL_H
#define SIGNAL_H

#include <string>
#include <vector>
#include <boost/dynamic_bitset.hpp>

#include "Unit.hpp"
#include "Location.hpp"

using std::vector;
using std::string;
using boost::dynamic_bitset;

struct Signal{

  typedef vector<Location> LocationVector;
  typedef vector<Unit> UnitVector;
  string name_;
  bool set_;
  bool negate_;
  LocationVector locationVec_;
  UnitVector  unitVec_;
  dynamic_bitset<> pattern_;
  
public:

  Signal(const string& name):
    name_(name),set_(true),negate_(false),pattern_(0){};

  const bool&   Set()  {return set_;}
  const string& Name() {return name_;}

  dynamic_bitset<>& PatternRef() { return pattern_;}

  LocationVector& LocationVectorRef() {return locationVec_;}
  UnitVector& UnitVectorRef() {return unitVec_;}

  const bool operator()(const string& id){
    return id == name_;
  }
    
};

#endif
