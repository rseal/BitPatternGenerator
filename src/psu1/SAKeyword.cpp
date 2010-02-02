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
#include <bpg-v2/Rules/PSU/Type1/SAKeyword.hpp>

using namespace std;
using namespace boost::spirit::classic;

namespace psu1{

void SAKeyword::Detect(const string& token){

  typedef rule<phrase_scanner_t> PhraseRule;
  string negStr;
  unsigned int num;

  vector<string> pVec;
  vector<uint>   cVec;
  vector<uint>   uvVec;
  vector<string> usVec;
  LocationVector lv;

  PhraseRule units_r    =  chseq_p("km") | chseq_p("usec") | chseq_p("mhz") |
    chseq_p("msec") | chseq_p("nsec");
  PhraseRule port_r     = ch_p('a') | ch_p('b');
  PhraseRule signal_r   = port_r[push_back_a(pVec)] >> ch_p('.') >> uint_p[push_back_a(cVec)];
  PhraseRule unit_r     = uint_p[push_back_a(uvVec)] >> units_r[push_back_a(usVec)];
  PhraseRule location_r = signal_r >> *(ch_p(',') >> signal_r);
  PhraseRule range_r    = ch_p('(') >> unit_r >> ch_p(',') >> unit_r >> ch_p(')');


  PhraseRule phrase     = (
			   (chseq_p("sa") >> uint_p[assign_a(num)])
			   >> ch_p('=') 
			   >> location_r 
			   >> ch_p(',') 
			   >> range_r 			     
			   >> !( ch_p(',') >> (chseq_p("negate")[assign_a(negStr)]))
			   );
				

  if( parse( token.c_str(), phrase, space_p).full){
    cout << "found SA signal" << endl;

    //load location vector
    for(uint i=0; i<pVec.size(); ++i){
      lv.push_back(Location(pVec[i][0],cVec[i]));
    }
      
    bool isNeg = "negate" == negStr;

    //convert to usec and round up 
    h0_ = ceil(uvVec[0]*UnitConvert::Convert(usVec[0])*1e6);
    hf_ = ceil(uvVec[1]*UnitConvert::Convert(usVec[1])*1e6);
    cout << "range = (" << h0_ << "," << hf_ << ")" << endl;
      
    parameters_.push_back(SaTuple(lv,
				  isNeg,
				  h0_,
				  hf_
				  )
			  );
    set_ = true;
    Verify();
  }

}

}; // namespace psu1
