#ifndef TYPE2_KEYWORD_H
#define TYPE2_KEYWORD_H

#include "../Keyword.hpp"
#include <boost/spirit/include/classic_spirit.hpp>

using namespace boost::spirit::classic;

class TYPE2Keyword: public Keyword{

  void Detect(const string& token){

    if(set_) return;

    typedef rule<phrase_scanner_t> PhraseRule;

    string                 modeStr;
    unsigned int           uValue;
    string                 uStr;

    
    PhraseRule mode_r     = (
			     chseq_p("normal") | chseq_p("multi")
			     )[assign_a(modeStr)];
    
    PhraseRule phrase     = (
			     chseq_p("mode")
			     >> ch_p('=')
			     >> mode_r
			     );

    if( parse( token.c_str(), phrase, space_p).full){
      cout << "found TYPE2 Keyword signal" << endl;
      
      parameters_.push_back(Parameter("mode", modeStr));
      
      set_ = true;
    }

  }

  void Verify(){ cout << "TYPE2 verify" << endl;}
  
public:
  TYPE2Keyword(): Keyword("type2"){};

};

#endif
