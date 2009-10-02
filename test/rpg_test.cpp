#include <boost/spirit/include/classic_spirit.hpp>
#define BOOST_TEST_MODULE RadarPulseGeneratorTest
#include <boost/test/included/unit_test.hpp>
#include "../include/RadarPulseGenerator.hpp"
#include "../include/InstrumentFinder.hpp"
#include "../include/IRules.hpp"

BOOST_AUTO_TEST_CASE(radarPulseGenerator_test){

  typedef vector<string> TokenVector;
  InstrumentFinder iFinder;

  //Locate the instrument according to the specified INSTRUMENT
  IInstrumentDefinition* instrument = iFinder.FindInstrument("test.hif");

  //Load the instrument's rule set
  IRules* rules = instrument->GetRules("test.hif");

  //Tokenize the input file
  TokenVector tokens = instrument->Tokenize("test.hif");

  rules->Detect(tokens);
  //rules->Verify();
  BOOST_CHECK(rules->Verify());
}
