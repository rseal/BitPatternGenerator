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
#include <bpg-v2/Rules/PSU/Type1/TXAKeyword.hpp>

using namespace std;
using namespace boost::spirit::classic;

namespace psu1{

   void TXAKeyword::Detect(const string& token)
   {

      // don't bother with duplicate entries in configuration file.
      if(set_) return;

      typedef rule<phrase_scanner_t> PhraseRule;
      LocationVector lv;
      vector<string> pVec;
      vector<unsigned int>   cVec;
      unsigned int   uValue;
      string         uStr;


      PhraseRule units_r = ( chseq_p("baud") );

      PhraseRule port_r = ch_p('a') | ch_p('b');

      PhraseRule signal_r = (
            port_r[push_back_a(pVec)] >> ch_p('.') >> 
            uint_p[push_back_a(cVec)]
            );

      PhraseRule unit_r = (
            ch_p('(') 
            >> uint_p[assign_a(uValue)] 
            >> units_r[assign_a(uStr)] 
            >> ch_p(')')
            );

      PhraseRule location_r = (
            signal_r >> *(ch_p(',') >> signal_r)
            );

      PhraseRule phrase = (
            chseq_p("txa") >> ch_p('=') 
            >> location_r 
            >> unit_r
            );

      if( parse( token.c_str(), phrase, space_p).full){
         cout << "found TXA signal" << endl;

         //load location vector
         for(uint i=0; i<pVec.size(); ++i){
            lv.push_back(Location(pVec[i][0],cVec[i]));
         }

         //load parameters
         width_ = uValue*UnitConvert::Convert(uStr);
         parameters_.push_back(TxaTuple(lv,width_));

         set_ = true;
         Verify();
      }

   }

}; // namespace psu1
