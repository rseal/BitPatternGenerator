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

#include <boost/spirit/include/classic_spirit.hpp>
#include <bpg-v2/Common/UnitConvert.hpp>
#include <bpg-v2/Rules/Arecibo/Keywords/Baudwidth.hpp>

using namespace std;
using namespace boost::spirit::classic;

namespace arecibo { 

void BaudwidthKeyword::Detect(const string& token){

  //we only detect this keyword once
  if(set_) return;

  typedef rule<phrase_scanner_t> PhraseRule;

  vector<unsigned int>   nVec;
  vector<string>         uVec;

  PhraseRule keyword_r = chseq_p("baudwidth");

  PhraseRule units_r    = ( 
			   chseq_p("km") | chseq_p("usec") | 
			   chseq_p("mhz") | chseq_p("msec") |
			   chseq_p("nsec") | chseq_p("samples")
			    );
    
  PhraseRule unit_r     = (
			   uint_p[push_back_a(nVec)] >> 
			   units_r[push_back_a(uVec)]
			   );

  PhraseRule range_r    = unit_r >> ch_p(',') >> unit_r; 

  PhraseRule phrase     = (
			   keyword_r
			   >> ch_p('=')
			   >> range_r
			   );

  if( parse( token.c_str(), phrase, space_p).full){
    cout << "found BAUDWIDTH Keyword signal" << endl;


    float v1 = nVec[0]*UnitConvert::Convert(uVec[0]);
    float v2 = nVec[1]*UnitConvert::Convert(uVec[1]);
    parameters_.push_back(BaudwidthTuple(v1,v2));
      
    set_ = true;
  }

}

}; //namespace arecibo 
