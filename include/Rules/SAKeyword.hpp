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
#ifndef SA_KEYWORD_H
#define SA_KEYWORD_H

#include "../Keyword.hpp"
#include "../UnitConvert.hpp"
#include "../Location.hpp"
#include <boost/spirit/include/classic_spirit.hpp>

using namespace boost::spirit::classic;

typedef tuple<LocationVector, bool, float, float&> SaTuple;

class SAKeyword: public Keyword<SaTuple>{

  float h0_;
  float hf_;

  void Detect(const string& token);

  void Verify(){
    if(h0_ > hf_) throw std::runtime_error("SA window - hf > h0");
    cout << "SA verify" << endl;
  }
  
public:
  SAKeyword(): Keyword<SaTuple>("sa"){};

};

#endif
