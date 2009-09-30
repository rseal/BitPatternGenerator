#include <boost/spirit/include/classic_spirit.hpp>
#define BOOST_TEST_MODULE SpiritTest
#include <boost/test/included/unit_test.hpp>
#include <vector>
using std::vector;
using std::cout;
using std::endl;
using std::string;

using namespace boost::spirit::classic;

//Functor to define semantic action when port rule is detected
struct PortVerify{
private:
  string& str_;
public:
  PortVerify(string& str): str_(str){};
  void operator()(const char* first, const char* last) const{
  str_.assign(first,last);
  }
};

BOOST_AUTO_TEST_CASE(spririt_test){

  typedef rule<phrase_scanner_t> PhraseRule;
  vector<int> vec;
  uint_parser<unsigned,10,1,2> uint2_p;
  
  string testStr;
  PortVerify pv(testStr);
  bool isNegative;
  string name;
  uint ch;
  string unitStr;

  string input("SA0 = a.1,a.2,b.15,b.4,  ( 15 usec,10    km  )");
  string txa_input("TXA = b.1,b.3,b.5,b.7, 150 usec ");
  string code_input("CODE  = a.0,a.3,a.7, {+5 -2 +2 -1 +1 -1 +1}");

  //NOTE: you have to explicity specify the phrase scanner for rules to avoid confusion when passed to the parser
  //this bug creates errors due to white space not being properly skipped.
  PhraseRule signal_names_r = (chseq_p("TR")   | chseq_p("TXA") | 
			       chseq_p("CODE") | (chseq_p("SA") >> *uint_p));
  PhraseRule units_r        = chseq_p("km") | chseq_p("usec");
  PhraseRule unit_r         = uint_p >> units_r[assign_a(unitStr)];
  PhraseRule range_r        = ch_p('(') >> unit_r >> ch_p(',') >> unit_r >> ch_p(')');
  PhraseRule port_r         = (ch_p('a') | ch_p('b'))[pv];
  PhraseRule signal_r       = port_r >> ch_p('.') >> uint2_p[assign_a(ch)];
  PhraseRule multi_signal_r = signal_r >> *(ch_p(',') >> signal_r);
  PhraseRule sequence_r     = ch_p('{') >> +(sign_p[assign_a(isNegative)] 
							 >> uint_p) >> ch_p('}');
  PhraseRule TR_r  = signal_names_r[assign_a(name)] >> ch_p('=') 
							     >> multi_signal_r 
							     >> ch_p(',') 
							     >> range_r 
							     >> !chseq_p("negate");

  PhraseRule TXA_r          = chseq_p("TXA")  >> ch_p('=') 
					      >> multi_signal_r >> ch_p(',') >> unit_r;
  PhraseRule CODE_r         = chseq_p("CODE") >> ch_p('=') 
					      >> multi_signal_r >> ch_p(',') >> sequence_r;

  BOOST_CHECK(parse("a.14",signal_r,space_p).full);
  BOOST_CHECK(parse("a.14,a.3,a.4",multi_signal_r,space_p).full);
  BOOST_CHECK(parse("TXA", signal_names_r,space_p).full);
  BOOST_CHECK(parse(txa_input.c_str(), TXA_r,space_p).full);
  BOOST_CHECK(parse(code_input.c_str(), CODE_r,space_p).full);
  BOOST_CHECK(parse(input.c_str(),TR_r,space_p).full);
}
