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
#ifndef PSU1_KEYWORDS_H
#define PSU1_KEYWORDS_H

#include "../Keyword.h"
#include "../UnitConvert.h"

#include <boost/spirit/include/classic_spirit.hpp>

using boost;

struct TRKeyword: public Keyword{
  void Detect(){
    string nameStr;
    vector<char> portVec;
    vector<uint> channelVec;
    vector<uint> unitValueVec;
    vector<string> unitStrVec;

    PhraseRule signal_r = port_r[push_back_a(portVec)] >> ch_p('.') >> uint2_p[push_back_a(channelVec)];
    PhraseRule unit_r   = uint_p[push_back_a(unitValueVec)] >> units_r[push_back_a(unitStrVec)];

    rule<> rule = (
		   name          = chseq_p("tr")[assign_a(nameStr)] >> ch_p('='),
		   location      = signal_r >> *(ch_p(',') >> signal_r) >> ch_p(','),
		   range         = ch_p('(') >> unit_r >> ch_p(',') >> unit_r >> ch_p(')')
		   );

    subrule<0> name;
    subrule<1> location;
    subrule<2> range;
  }
}

  void Verify(){ cout << "TR verify" << endl;}

struct PSU1Keywords{

  

#endif
