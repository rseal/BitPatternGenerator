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
#ifndef TYPE1_KEYWORD_H
#define TYPE1_KEYWORD_H

#include "../Keyword.hpp"
#include "../UnitConvert.hpp"
#include <boost/spirit/include/classic_spirit.hpp>

using namespace boost::spirit::classic;

class TYPE1Keyword: public Keyword<Parameter>{

  void Detect(const string& token){

    typedef rule<phrase_scanner_t> PhraseRule;

    string                 nStr;
    unsigned int           uValue;
    string                 uStr;

    PhraseRule keyword_names_r = (
				  chseq_p("refclock") | chseq_p("ipp") | 
				  chseq_p("bauda")    | chseq_p("baudb")
				  )[assign_a(nStr)];
    
    PhraseRule units_r    = ( 
			     chseq_p("km") | chseq_p("usec") | 
			     chseq_p("mhz") | chseq_p("msec") |
			     chseq_p("nsec")
			      );
    
    PhraseRule unit_r     = (
			     uint_p[assign_a(uValue)] >> 
			     units_r[assign_a(uStr)]
			     );
    

    PhraseRule phrase     = (
			     keyword_names_r
			     >> ch_p('=')
			     >> unit_r
			     );

    if( parse( token.c_str(), phrase, space_p).full){
      cout << "found TYPE1 Keyword signal" << endl;
      float value = uValue*UnitConvert::Convert(uStr);
      parameters_.push_back(Parameter(nStr, value));
      
      set_ = true;
    }

  }

  void Verify(){ cout << "TYPE1 verify" << endl;}
  
public:
  TYPE1Keyword(): Keyword<Parameter>("type1"){};

};

#endif
