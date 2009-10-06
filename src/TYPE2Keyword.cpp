#include "../include/Rules/TYPE2Keyword.hpp"

void TYPE2Keyword::Detect(const string& token){

    if(set_) return;

    typedef rule<phrase_scanner_t> PhraseRule;

    string                 modeStr;
    
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
