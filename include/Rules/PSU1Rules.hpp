#ifndef PSU1RULES_H
#define PSU1RULES_H

#include "../Keyword.hpp"
#include "../Signal.hpp"
#include "../Unit.hpp"
#include "../Location.hpp"

#include "../IRules.hpp"
#include "../InstrumentRuleFactory.hpp"
#include <boost/spirit/include/classic_spirit.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/dynamic_bitset.hpp>
#include <vector>
#include <iostream>

using namespace std;
using namespace boost::spirit::classic;
using namespace boost;

class PSU1Rules: public IRules{
  typedef rule<phrase_scanner_t> PhraseRule;
  typedef vector<Keyword> KeywordVector;
  typedef vector<Signal> SignalVector;
  typedef vector<Unit> UnitVector;
  typedef vector<Location> LocationVector;
  typedef dynamic_bitset<> Pattern;

  KeywordVector keywords_;
  SignalVector signals_;

  void FormatPattern(Pattern& pattern,vector<uint>& codeVec, 
		     vector<bool>& signVec){
    for(uint i=0; i<codeVec.size(); ++i){
      for(uint j=0; j<codeVec[i]; ++j)
	pattern.push_back(!signVec[i]);
    }
  }
   
public:
 
  void Detect(const TokenVector& tokenVector){ 

    vector<string> portVec;
    vector<uint> channelVec;
    string nameStr;
    string modeStr;
    vector<string> unitStrVec;
    vector<uint>   unitValueVec;	
    vector<bool>   signVec;
    vector<uint>   codeVec;
    uint number;
    uint_parser<unsigned,10,1,2> uint2_p;
	
    /////////////////////////primitive rules defined here///////////////////////
    PhraseRule keyword_names_r = (
				  chseq_p("refclock") | chseq_p("ipp") | 
				  chseq_p("baud")
				  )[assign_a(nameStr)];
    
    PhraseRule units_r        = (
				 chseq_p("km") | 
				 chseq_p("usec") | 
				 chseq_p("mhz") |
				 chseq_p("msec")
				 );

    PhraseRule unit_r         = (
				 uint_p[push_back_a(unitValueVec)] >> units_r[push_back_a(unitStrVec)]
				 );
	
    PhraseRule range_r        = (
				 ch_p('(') >> unit_r >> ch_p(',') 
				 >> unit_r >> ch_p(')')
				 );

    PhraseRule port_r         = (
				 ch_p('a') | ch_p('b')
				 );
	
    PhraseRule signal_r       = (
				 port_r[push_back_a(portVec)] >> ch_p('.') >> uint2_p[push_back_a(channelVec)]
				 );

    PhraseRule mode_r         = (
				 chseq_p("normal") | chseq_p("multi")
				 )[assign_a(modeStr)];

    PhraseRule multi_signal_r = (
				 signal_r >> *(ch_p(',') >> signal_r)
				 );

    PhraseRule sequence_r     = (
				 ch_p('{') 
				 >> +(sign_p[push_back_a(signVec)] 
				      >> uint_p[push_back_a(codeVec)]) 
				 >> ch_p('}')
				 );
    /////////////////////////primitive rules defined here///////////////////////

    /////////////////////////comprehensive rules defined here///////////////////
    PhraseRule keyword_r = (
			    keyword_names_r[assign_a(nameStr)] 
			    >> ch_p('=')
			    >> unit_r
			    );

    PhraseRule keyword1_r = (
			     chseq_p("mode")[assign_a(nameStr)]
			     >> ch_p('=')
			     >> mode_r
			     );

    PhraseRule generic_r = (
			    multi_signal_r >> ch_p('=') >> sequence_r
			    );

    PhraseRule TR_r           = (
				 chseq_p("tr")[assign_a(nameStr)]
				 >> ch_p('=') 
				 >> multi_signal_r
				 >> ch_p(',') 
				 >> range_r 
				 );

    PhraseRule TXA_r          = (
				 chseq_p("txa")[assign_a(nameStr)]
				 >> ch_p('=') 
				 >> multi_signal_r 
				 >> ch_p(',') 
				 >> unit_r
				 );

    PhraseRule SA_r = (
		       (chseq_p("sa")[assign_a(nameStr)] >> uint2_p[assign_a(number)])
		       >> ch_p('=') 
		       >> multi_signal_r 
		       >> ch_p(',') 
		       >> range_r
		       >> !chseq_p("negate")
		       );
	    
    PhraseRule CODE_r         = (
				 chseq_p("code")[assign_a(nameStr)] 
				 >> ch_p('=') 
				 >> multi_signal_r 
				 >> ch_p(',') 
				 >> sequence_r
				 );
    /////////////////////////comprehensive rules defined here///////////////////

    TokenVector::const_iterator iter = tokenVector.begin();
    
    bool found = false;
    string token;

    while(iter != tokenVector.end()){
      found = false;
		
      token = to_lower_copy(*iter);

      //clear containers
      portVec.clear();
      channelVec.clear();
      unitValueVec.clear();
      unitStrVec.clear();
      nameStr.clear();
      codeVec.clear();
      signVec.clear();
	    
      if( parse(token.c_str(),TR_r,space_p).full){

	to_upper(nameStr);
	cout << "Found " << nameStr << " signal "  << endl;
		
	Signal sig(nameStr);
	UnitVector& uv     = sig.UnitVectorRef();
	LocationVector& lv = sig.LocationVectorRef();

	//store range units
	for(uint i=0; i<unitValueVec.size(); ++i)
	  uv.push_back(Unit(unitValueVec[i],unitStrVec[i]));

	//store locations
	for(uint i=0; i<portVec.size(); ++i)
	  lv.push_back(Location(portVec[i][0],channelVec[i]));

	//copy to vector
	signals_.push_back(sig);

	found = true;
      }
      
      if( parse(token.c_str(),TXA_r,space_p).full && !found){
	cout << "Found TXA signal " << endl;

	Signal sig("TXA");
	UnitVector& uv     = sig.UnitVectorRef();
	LocationVector& lv = sig.LocationVectorRef();

	//store range units
	for(uint i=0; i<unitValueVec.size(); ++i)
	  uv.push_back(Unit(unitValueVec[i],unitStrVec[i]));

	//store locations
	for(uint i=0; i<portVec.size(); ++i)
	  lv.push_back(Location(portVec[i][0],channelVec[i]));

	//copy to vector
	signals_.push_back(sig);
		
	found = true;
      }

      if( parse(token.c_str(),CODE_r,space_p).full && !found){
	cout << "Found CODE signal " << endl;

	Signal sig("CODE");
	Pattern& p = sig.PatternRef();

	FormatPattern(p,codeVec,signVec);

	found = true;
      }

      if( parse(token.c_str(),SA_r,space_p).full && !found){
	string str = nameStr + lexical_cast<string>(number);
	to_upper(str);

	cout << "Found " << str << " signal" << endl;
		
	
	Signal sig(str);
	LocationVector& lv = sig.LocationVectorRef();
	UnitVector& uv = sig.UnitVectorRef();

	//store locations
	for(uint i=0; i<portVec.size(); ++i)
	  lv.push_back(Location(portVec[i][0],channelVec[i]));

	//store units
	for(uint i=0; i<unitValueVec.size(); ++i)
	  uv.push_back(Unit(unitValueVec[i],unitStrVec[i]));
		
	//copy to vector
	signals_.push_back(sig);
		
	found = true;
      }

      if( parse(token.c_str(),generic_r,space_p).full && !found){
	static uint idx=0;
	cout << "Found generic signal " << endl;
	string str = "GEN" + lexical_cast<string>(idx);
	Signal sig(str);
	Pattern& p = sig.PatternRef();
	LocationVector lv = sig.LocationVectorRef();

	//store locations
	for(uint i=0; i<portVec.size(); ++i)
	  lv.push_back(Location(portVec[i][0],channelVec[i]));

	FormatPattern(p,codeVec,signVec);

	found = true;
      }

      if( parse(token.c_str(),keyword_r,space_p).full && !found){
	to_upper(nameStr);
	Keyword key(nameStr);
	UnitVector& uv = key.UnitVectorRef();

	//store locations
	for(uint i=0; i<unitValueVec.size(); ++i)
	  uv.push_back(Unit(unitValueVec[i],unitStrVec[i]));
		
	//copy to vector
	keywords_.push_back(key);

	found = true;
      }

      if( parse(token.c_str(),keyword1_r,space_p).full && !found){
		
	to_upper(nameStr);
	Keyword key(nameStr);
	key.Label(modeStr);
	keywords_.push_back(key);
	found = true;
      }

      if(!found)
	cout << "Unrecognized Pattern: " << *iter << endl; 

      ++iter;
    }
  };

  const bool Verify(){
    //parameters_.Print();
    cout << "running PSU1 Verification Function" << endl;
    return true;
  }


};

namespace PSU1
{
  IRules* Callback(){
    return new PSU1Rules();
  }

  const string id = "psu1";
  bool result = InstrumentRuleFactory::Instance().RegisterRule(id,Callback);
};

#endif  
