#include <boost/spirit/include/classic_spirit.hpp>
#include <bpg-v2/Rules/PSU/Type1/TYPE2Keyword.hpp>

using namespace std;
using namespace boost::spirit::classic;

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
