#ifndef TR_KEYWORD_H
#define TR_KEYWORD_H

#include "../Keyword.hpp"
#include "../UnitConvert.hpp"
#include "../Location.hpp"
#include <boost/spirit/include/classic_spirit.hpp>

using namespace boost::spirit::classic;

class TRKeyword: public Keyword{

  float pre_;
  float post_;
  void Detect(const string& token){

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
      for(int i=0; i<portVec.size(); ++i){
	lv.push_back(Location(portVec[i][0],channelVec[i]));
      }
      
      //load parameters
      parameters_.push_back(Parameter("location",lv));
      pre_  = (unitValueVec[0]*UnitConvert::Convert(unitStrVec[0]))*1e6;
      post_ = (unitValueVec[1]*UnitConvert::Convert(unitStrVec[1]))*1e6;

      parameters_.push_back(Parameter("pre", pre_));
      parameters_.push_back(Parameter("post", post_));

      set_ = true;
      Verify();
    }

  }

  void Verify(){ 

    if(pre_ < 10) throw std::runtime_error("TR PRE value is below limits");
    if(post_ < 10) throw std::runtime_error("TR POST value is below limits");

    //if(!set_)
    cout << "TR verify " <<  endl;
  }
  
public:
  TRKeyword(): Keyword("tr"){
    typedef unsigned int uint;
  };

};

#endif
