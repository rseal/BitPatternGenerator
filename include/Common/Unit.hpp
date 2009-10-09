// Copyright (c) 2009 Ryan Seal <rlseal -at- gmail.com>
//
// This file is part of Bit Pattern Generator (BPG) Software.
//
// BPG is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//  
// BPG is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with BPG.  If not, see <http://www.gnu.org/licenses/>.
#ifndef UNIT_H
#define UNIT_H

#include <iostream>
#include <vector>

struct Unit{
  Unit(): value(float()),units(std::string()){};

  Unit(const float& value_, 
       const std::string& units_):
    value(value_),units(units_){}
  float value;
  std::string units;
};

typedef std::vector<Unit> UnitVector;

#endif
