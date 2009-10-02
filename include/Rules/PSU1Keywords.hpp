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
