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
#include <boost/tuple/tuple.hpp>
#include <bpg-v2/Common/UnitConvert.hpp>
#include <bpg-v2/Rules/PSU/Type1/TRKeyword.hpp>

using namespace std;
using namespace boost::spirit::classic;

namespace psu1{

void TRKeyword::Detect(const string& token){

  if(set_) return;

  typedef rule<phrase_scanner_t> PhraseRule;
  string nameStr;
  vector<string> portVec;
  vector<uint> channelVec;
  vector<uint> unitValueVec;
  vector<string> unitStrVec;
  LocationVector lv;
  PhraseRule units_r    = (
			   chseq_p("km")   | 
			   chseq_p("usec") | 
			   chseq_p("mhz")  |
			   chseq_p("msec") | 
			   chseq_p("nsec")
			   );
  PhraseRule port_r     = ch_p('a') | ch_p('b');
  PhraseRule signal_r   = port_r[push_back_a(portVec)] >> ch_p('.') >> uint_p[push_back_a(channelVec)];
  PhraseRule unit_r     = uint_p[push_back_a(unitValueVec)] >> units_r[push_back_a(unitStrVec)];
  PhraseRule location_r = signal_r >> *(ch_p(',') >> signal_r);
  PhraseRule range_r    = ch_p('(') >> unit_r >> ch_p(',') >> unit_r >> ch_p(')');

  PhraseRule phrase = (
		       chseq_p("tr")[assign_a(nameStr)] 
		       >> ch_p('=') 
		       >> location_r 
		       >> ch_p(',')
		       >> range_r
		       );

  if( parse( token.c_str(), phrase, space_p).full){
    cout << "found TR signal" << endl;

    //load location vector
    for(uint i=0; i<portVec.size(); ++i){
      lv.push_back(Location(portVec[i][0],channelVec[i]));
	
    }
      
    //load parameters
    pre_  = (unitValueVec[0]*UnitConvert::Convert(unitStrVec[0]))*1e6;
    post_ = (unitValueVec[1]*UnitConvert::Convert(unitStrVec[1]))*1e6;

    parameters_.push_back(TrTuple(lv, pre_, post_));

    set_ = true;
    Verify();
  }

}

}; // namespace psu1
