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
#ifndef TR_KEYWORD_H
#define TR_KEYWORD_H

#include <bpg-v2/Common/Keyword.hpp>
#include <bpg-v2/Common/UnitConvert.hpp>
#include <bpg-v2/Common/Location.hpp>

#include <boost/spirit/include/classic_spirit.hpp>

using namespace boost::spirit::classic;

typedef tuple<LocationVector, float, float> TrTuple;

class TRKeyword: public Keyword<TrTuple>{

  float pre_;
  float post_;

  void Detect(const string& token);

  void Verify(){ 

    if(pre_ < 10) throw std::runtime_error("TR PRE value is below limits");
    if(post_ < 10) throw std::runtime_error("TR POST value is below limits");
    cout << "TR verify " <<  endl;
  }
  
public:
  TRKeyword(): Keyword<TrTuple>("tr"){};

};

#endif
