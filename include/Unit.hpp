#ifndef UNIT_H
#define UNIT_H

#include <iostream>
using std::string;

struct Unit{
  Unit(const float& value_, 
       const string& units_):
    value(value_),units(units_){}
  float value;
  string units;
};

#endif
