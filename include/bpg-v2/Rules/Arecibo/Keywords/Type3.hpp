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
#ifndef TYPE3_KEYWORD_H
#define TYPE3_KEYWORD_H

#include <boost/tuple/tuple.hpp>
#include <bpg-v2/Common/Keyword.hpp>
#include <bpg-v2/Common/Location.hpp>
#include <bpg-v2/Common/Parameter.hpp>

namespace arecibo{

typedef boost::tuple<LocationVector,float> Type3Tuple;

class Type3Keyword: public Keyword<Parameter>{
  
  void Detect(const std::string& token);
  
  void Verify(){ std::cout << "TYPE3 verify" << std::endl;}
  
public:
  Type3Keyword(): Keyword<Parameter>("type3"){};
  
};

}; // namespace arecibo

#endif
