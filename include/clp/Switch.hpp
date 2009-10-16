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
#ifndef SWITCH_H
#define SWITCH_H

#include <iostream>
#include <bpg-v2/clp/Option.hpp>

//!\brief Provides an interface for defining switches on the command line. 
class Switch: public Option{
public:
  Switch(const std::string& name, const std::string& helpDesc, const bool& required):
	Option(name,helpDesc,required){};
};
#endif
