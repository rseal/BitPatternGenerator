#include <boost/spirit/include/classic_spirit.hpp>
#include <bpg-v2/Common/UnitConvert.hpp>
#include <bpg-v2/Rules/PSU/Type1/TYPE1Keyword.hpp>

using namespace std;
using namespace boost::spirit::classic;

void TYPE1Keyword::Detect(const string& token){

  typedef rule<phrase_scanner_t> PhraseRule;

  string         nStr;
  unsigned int   uValue;
  string         uStr;

  PhraseRule keyword_names_r = (
				chseq_p("refclock") | chseq_p("ipp") | 
				chseq_p("bauda")    | chseq_p("baudb")
				)[assign_a(nStr)];

  PhraseRule units_r    = ( 
			   chseq_p("km") | chseq_p("usec") | 
			   chseq_p("mhz") | chseq_p("msec") |
			   chseq_p("nsec")
			    );
    
  PhraseRule unit_r     = (
			   uint_p[assign_a(uValue)] >> 
			   units_r[assign_a(uStr)]
			   );
    

  PhraseRule phrase     = (
			   keyword_names_r
			   >> ch_p('=')
			   >> unit_r
			   );

  if( parse( token.c_str(), phrase, space_p).full){
    cout << "found TYPE1 Keyword signal" << endl;
    float value = uValue*UnitConvert::Convert(uStr);
    parameters_.push_back(Parameter(nStr, value));
      
    set_ = true;
  }

}
