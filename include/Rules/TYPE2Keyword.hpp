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
#ifndef TYPE2_KEYWORD_H
#define TYPE2_KEYWORD_H

#include "../Keyword.hpp"
#include <boost/spirit/include/classic_spirit.hpp>

using namespace boost::spirit::classic;

class TYPE2Keyword: public Keyword<Parameter>{

  void Detect(const string& token){

    if(set_) return;

    typedef rule<phrase_scanner_t> PhraseRule;

    string                 modeStr;
    unsigned int           uValue;
    string                 uStr;

    
    PhraseRule mode_r     = (
			     chseq_p("normal") | chseq_p("multi")
			     )[assign_a(modeStr)];
    
    PhraseRule phrase     = (
			     chseq_p("mode")
			     >> ch_p('=')
			     >> mode_r
			     );

    if( parse( token.c_str(), phrase, space_p).full){
      cout << "found TYPE2 Keyword signal" << endl;
      
      parameters_.push_back(Parameter("mode", modeStr));
      
      set_ = true;
    }

  }

  void Verify(){ cout << "TYPE2 verify" << endl;}
  
public:
  TYPE2Keyword(): Keyword<Parameter>("type2"){};

};

#endif
