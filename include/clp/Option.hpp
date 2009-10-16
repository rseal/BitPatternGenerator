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
#ifndef OPTION_H
#define OPTION_H

#include <iostream>

//!\brief Provides an interface for defining switches on the command line. 
class Option{
protected:
  std::string name_;
  std::string helpDesc_;
    bool required_;
    bool set_;
public:
  Option(const std::string& name, const std::string& helpDesc, const bool& required):
	name_(name), helpDesc_(helpDesc), required_(required), set_(false) {}

    void Set(bool const& state) { set_ = state;     }
    const bool& Set()           { return set_;      }
  const std::string& Name()        { return name_;     }
  const std::string& Help()        { return helpDesc_; }
};
#endif
