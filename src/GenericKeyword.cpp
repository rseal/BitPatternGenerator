#include <bpg-v2/Rules/PSU/Type1/GenericKeyword.hpp>

void GenericKeyword::Detect(const string& token){

  typedef rule<phrase_scanner_t> PhraseRule;

  vector<bool>   signVec;
  vector<uint>   codeVec;
  vector<string> pVec;
  vector<uint>   cVec;
  LocationVector lv;

  PhraseRule units_r    =  (
			    chseq_p("km")  | chseq_p("usec") | 
			    chseq_p("mhz") | chseq_p("msec") | 
			    chseq_p("nsec")
			    );

  PhraseRule port_r     = ch_p('a') | ch_p('b');
	
  PhraseRule signal_r   = port_r[push_back_a(pVec)] 
    >> ch_p('.') 
    >> uint_p[push_back_a(cVec)];

  PhraseRule location_r = signal_r >> *(ch_p(',') >> signal_r);

  PhraseRule sequence_r = (
			   ch_p('{') 
			   >> +(sign_p[push_back_a(signVec)] 
				>> uint_p[push_back_a(codeVec)]) 
			   >> ch_p('}')
			   );

  PhraseRule phrase = (
		       location_r >> ch_p('=') >> sequence_r
		       );

  //run parser and match pattern
  if( parse( token.c_str(), phrase, space_p).full){
    cout << "found Generic signal" << endl;

    //load location vector
    for(uint i=0; i<pVec.size(); ++i){
      lv.push_back(Location(pVec[i][0],cVec[i]));
    }
      
    Pattern bitVector;
    FormatPattern(bitVector,codeVec,signVec);

    //load parameters
    parameters_.push_back(GenericTuple(lv, bitVector));

    set_ = true;
  }

}
