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
#include <bpg-v2/Common/Location.hpp>
#include <boost/spirit/include/classic_spirit.hpp>
#include <bpg-v2/Rules/Arecibo/Keywords/Phase.hpp>

using namespace boost::spirit::classic;
using namespace boost;
using namespace std;

namespace arecibo{

void PhaseKeyword::Detect(const std::string& token){

  if(set_) return;
  
  typedef rule<phrase_scanner_t> PhraseRule;
  string nStr;
  vector<bool>   signVec;
  vector<uint>   codeVec;

  PhraseRule sequence_r = (
			   ch_p('{') 
			   >> +(sign_p[push_back_a(signVec)] 
				>> uint_p[push_back_a(codeVec)]) 
			   >> ch_p('}')
			   );

  PhraseRule phrase     = (
			   chseq_p("phase")[assign_a(nStr)] 
			   >> ch_p('=') 
			   >> (sequence_r | chseq_p("clp")[assign_a(nStr)])
			   );

  //run parser and match pattern
  if( parse( token.c_str(), phrase, space_p).full){
    cout << "found PHASE signal" << endl;
      
    Pattern bitVector;
    FormatPattern(bitVector,codeVec,signVec);

    //load parameters
    parameters_.push_back(PhaseTuple( bitVector,
				      static_cast<unsigned int>
				      (bitVector.size()),
				      nStr == "clp"
				      )
			  );

    set_ = true;
    Verify();
  }
}

}; // namespace arecibo 
