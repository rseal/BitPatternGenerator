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
#include <bpg-v2/Rules/PSU/Type1/GenericKeyword.hpp>

using namespace std;
using namespace boost::spirit::classic;

namespace psu1{

   void GenericKeyword::Detect(const string& token)
   {
      typedef rule<phrase_scanner_t> PhraseRule;

      vector<bool>   signVec;
      vector<uint>   codeVec;
      vector<string> pVec;
      vector<uint>   cVec;
      LocationVector lv;

      PhraseRule port_r = ch_p('a') | ch_p('b');

      PhraseRule signal_r = port_r[push_back_a(pVec)] 
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
      if( parse( token.c_str(), phrase, space_p).full)
      {
         cout << "found Generic signal" << endl;

         //load location vector
         for(uint i=0; i<pVec.size(); ++i)
         {
            lv.push_back(Location(pVec[i][0],cVec[i]));
         }

         Pattern bitVector;
         FormatPattern(bitVector,codeVec,signVec);

         //load parameters
         parameters_.push_back(GenericTuple(lv, bitVector));

         set_ = true;

         Verify();
      }

   }

}; // namespace psu1
