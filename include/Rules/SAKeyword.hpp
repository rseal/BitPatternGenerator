#ifndef SA_KEYWORD_H
#define SA_KEYWORD_H

#include "../Keyword.hpp"
#include "../UnitConvert.hpp"
#include "../Location.hpp"
#include <boost/spirit/include/classic_spirit.hpp>

using namespace boost::spirit::classic;

class SAKeyword: public Keyword{

  float h0_;
  float hf_;

  void Detect(const string& token){

    //if(set_) return;

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
      for(int i=0; i<pVec.size(); ++i){
	lv.push_back(Location(pVec[i][0],cVec[i]));
      }
            
      parameters_.push_back(Parameter("location",lv));
      parameters_.push_back(Parameter("number", num));
      parameters_.push_back(Parameter("negate", "negate" == negStr));
      
      //convert to usec and round up 
      h0_ = ceil(uvVec[0]*UnitConvert::Convert(usVec[0])*1e6);
      hf_ = ceil(uvVec[1]*UnitConvert::Convert(usVec[1])*1e6);

      parameters_.push_back(Parameter("h0", h0_));
      parameters_.push_back(Parameter("hf", hf_));

      set_ = true;
      Verify();
    }

  }

  void Verify(){
    cout << "h0 = " << h0_ << endl;
    cout << "hf = " << hf_ << endl;
    if(h0_ > hf_) throw std::runtime_error("SA window - hf > h0");
    cout << "SA verify" << endl;}
  
public:
  SAKeyword(): Keyword("sa"){};

};

#endif
