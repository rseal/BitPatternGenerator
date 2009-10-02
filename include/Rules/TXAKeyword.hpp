#ifndef TXA_KEYWORD_H
#define TXA_KEYWORD_H

#include "../Keyword.hpp"
#include "../UnitConvert.hpp"
#include "../Location.hpp"
#include <boost/spirit/include/classic_spirit.hpp>

using namespace boost::spirit::classic;

class TXAKeyword: public Keyword{

  float width_;

  void Detect(const string& token){

    if(set_) return;

    typedef rule<phrase_scanner_t> PhraseRule;

    vector<string> pVec;
    vector<unsigned int>   cVec;
    unsigned int   uValue;
    string         uStr;
    LocationVector lv;
    
    PhraseRule units_r    = ( 
			     chseq_p("km") | chseq_p("usec") | 
			     chseq_p("mhz") | chseq_p("msec") |
			     chseq_p("nsec")
			      );
    
    PhraseRule port_r     = ch_p('a') | ch_p('b');
    
    PhraseRule signal_r   = (
			     port_r[push_back_a(pVec)] >> ch_p('.') >> 
			     uint_p[push_back_a(cVec)]
			     );
    
    PhraseRule unit_r     = (
			     uint_p[assign_a(uValue)] >> 
			     units_r[assign_a(uStr)]
			     );
    
    PhraseRule location_r = (
			     signal_r >> *(ch_p(',') >> signal_r)
			     );
    
    PhraseRule phrase     = (
			     chseq_p("txa") >> ch_p('=') 
			     >> location_r 
			     >> ch_p(',') 
			     >> unit_r
			     );

    if( parse( token.c_str(), phrase, space_p).full){
      cout << "found TXA signal" << endl;
      
      //load location vector
      for(int i=0; i<pVec.size(); ++i){
	lv.push_back(Location(pVec[i][0],cVec[i]));
      }
      
      //load parameters
      parameters_.push_back(Parameter("location",lv));
      width_ = uValue*UnitConvert::Convert(uStr)*1e6;
      parameters_.push_back(Parameter("width", width_));

      set_ = true;
      Verify();
    }

  }

  void Verify(){
    if(width_ > 145) throw std::runtime_error("TXA width is above limits");

    cout << "TXA verify" << endl;
  }
  
public:
  TXAKeyword(): Keyword("txa"){};

};

#endif
