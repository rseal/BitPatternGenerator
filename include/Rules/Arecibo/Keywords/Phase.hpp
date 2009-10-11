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
#ifndef PHASE_KEYWORD_H
#define PHASE_KEYWORD_H

#include <boost/tuple/tuple.hpp>
#include <boost/dynamic_bitset.hpp>
#include <bpg-v2/Common/Keyword.hpp>

typedef boost::tuple< boost::dynamic_bitset<>,unsigned int,bool> PhaseTuple;

class PhaseKeyword: public Keyword<PhaseTuple>{
  
  typedef boost::dynamic_bitset<> Pattern;

  void Detect(const std::string& token);
  
  void Verify(){ std::cout << "PHASE verify" << std::endl;}

  void FormatPattern(Pattern& pattern,std::vector<uint>& codeVec, 
		     std::vector<bool>& signVec){
    for(uint i=0; i<codeVec.size(); ++i){
      for(uint j=0; j<codeVec[i]; ++j)
	pattern.push_back(!signVec[i]);
    }
  }
  
public:
  PhaseKeyword(): Keyword<PhaseTuple>("Phase"){};
  
};

#endif
