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
#ifndef BAUDWIDTH_KEYWORD_H
#define BAUDWIDTH_KEYWORD_H

#include <boost/tuple/tuple.hpp>
#include <bpg-v2/Common/Keyword.hpp>
#include <bpg-v2/Common/Location.hpp>

typedef boost::tuple<float,float> BaudwidthTuple;

class BaudwidthKeyword: public Keyword<BaudwidthTuple>{
  
  void Detect(const std::string& token);
  
  void Verify(){ std::cout << "BAUDWIDTH verify" << std::endl;}
  
public:
  BaudwidthKeyword(): Keyword<BaudwidthTuple>("baudwidth"){};
  
};

#endif
