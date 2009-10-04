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
#ifndef GENERIC_KEYWORD_H
#define GENERIC_KEYWORD_H

#include "../Keyword.hpp"
#include "../Location.hpp"
#include <boost/spirit/include/classic_spirit.hpp>
#include <boost/dynamic_bitset.hpp>

using namespace boost::spirit::classic;

typedef tuple<LocationVector, dynamic_bitset<> > GenericTuple;

class GenericKeyword: public Keyword<GenericTuple>{
  
    typedef dynamic_bitset<> Pattern;

    void Detect(const string& token){

	//if(set_) return;

	typedef rule<phrase_scanner_t> PhraseRule;

	vector<bool>   signVec;
	vector<uint>   codeVec;
	vector<string> pVec;
	vector<uint>   cVec;
	LocationVector lv;

	PhraseRule units_r    =  (
	    chseq_p("km")  | chseq_p("usec") | 
	    chseq_p("mhz") | chseq_p("msec") | 
	    chseq_p("nsec")
	    );

	PhraseRule port_r     = ch_p('a') | ch_p('b');
	
	PhraseRule signal_r   = port_r[push_back_a(pVec)] 
	    >> ch_p('.') 
	    >> uint_p[push_back_a(cVec)];

	PhraseRule location_r = signal_r >> *(ch_p(',') >> signal_r);

	PhraseRule sequence_r = (
	    ch_p('{') 
	    >> +(sign_p[push_back_a(signVec)] 
		 >> uint_p[push_back_a(codeVec)]) 
	    >> ch_p('}')
	    );

	PhraseRule phrase = (
	    location_r >> ch_p('=') >> sequence_r
	    );

	//run parser and match pattern
	if( parse( token.c_str(), phrase, space_p).full){
	    cout << "found Generic signal" << endl;

	    //load location vector
	    for(int i=0; i<pVec.size(); ++i){
		lv.push_back(Location(pVec[i][0],cVec[i]));
	    }
      
	    Pattern bitVector;
	    FormatPattern(bitVector,codeVec,signVec);

	    //load parameters
	    parameters_.push_back(make_tuple(lv, bitVector));
	    // parameters_.push_back(Parameter("location",lv));
	    // parameters_.push_back(Parameter("pattern", bitVector));
	    set_ = true;
	}

    }

    void Verify(){ cout << "GENERIC verify" << endl;}

    void FormatPattern(Pattern& pattern,vector<uint>& codeVec, 
		       vector<bool>& signVec){
	for(uint i=0; i<codeVec.size(); ++i){
	    for(uint j=0; j<codeVec[i]; ++j)
		pattern.push_back(!signVec[i]);
	}
    }
  
public:
  GenericKeyword(): Keyword<GenericTuple>("generic"){};

};

#endif
