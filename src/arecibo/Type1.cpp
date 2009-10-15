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


#include <iostream>
#include <boost/spirit/include/classic_spirit.hpp>
#include <bpg-v2/Rules/Arecibo/Keywords/Type1.hpp>

using namespace std;
using namespace boost::spirit::classic;

namespace arecibo{

void Type1Keyword::Detect(const std::string& token){

  typedef rule<phrase_scanner_t> PhraseRule;
  
  string         nStr;
  vector<string> pVec;
  vector<uint>   cVec;
  LocationVector lv;
 
  PhraseRule keyword_names_r = (
				chseq_p("txipp") | chseq_p("riipp") | 
				chseq_p("rf")
				)[assign_a(nStr)];

  PhraseRule port_r     = ch_p('a') | ch_p('b');

  PhraseRule signal_r   = port_r[push_back_a(pVec)] >> ch_p('.') >> uint_p[push_back_a(cVec)];

  PhraseRule location_r = signal_r >> *(ch_p(',') >> signal_r);

  PhraseRule phrase     = (
			   keyword_names_r
			   >> ch_p('=')
			   >> location_r
			   );

  //set_ = false;

  if( parse( token.c_str(), phrase, space_p).full){
    cout << "found TYPE1 Keyword signal" << endl;

    //load location vector
    for(uint i=0; i<pVec.size(); ++i){ 
      lv.push_back(Location(pVec[i][0],cVec[i]));
    }
    parameters_.push_back(Parameter(nStr, lv));
      
    set_ = true;
  }
}
  
  void Type1Keyword::Verify(){ std::cout << "TYPE1 verify" << std::endl;}

}; //namespace arecibo
