#ifndef UNIT_H
#define UNIT_H

#include <iostream>
#include <vector>

using std::vector;
using std::string;

struct Unit{
  Unit(): value(float()),units(string()){};

  Unit(const float& value_, 
       const string& units_):
    value(value_),units(units_){}
  float value;
  string units;
};

typedef vector<Unit> UnitVector;

#endif
