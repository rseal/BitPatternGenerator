// Copyright (c) 2009 Ryan Seal <rlseal -at- gmail.com>
//
// This file is part of Bit Pattern Generator (BPG) Software.
//
// BPG is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//  
// BPG is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with BPG.  If not, see <http://www.gnu.org/licenses/>.

#include <boost/spirit/include/classic_spirit.hpp>
#define BOOST_TEST_MODULE SignalFormatterTest
#include <boost/test/included/unit_test.hpp>
#include <bpg-v2/Instruments/Rpg/RpgSignalFormatter.hpp>
#include <bpg-v2/Instruments/Rpg/RpgIIF.hpp>
#include <boost/dynamic_bitset.hpp>

using namespace std;
using namespace boost;

BOOST_AUTO_TEST_CASE(formatter_test){

  typedef dynamic_bitset<> Pattern;
  typedef vector<Pattern>  PatternVector;
  typedef vector<unsigned long> OutputVector;

  //use n(n+1)/2 sum to produce valid test pattern
  //n=45 and sum=1035
  const int ipp=1035;
  const int numPorts=32;
  PatternVector ports;
  OutputVector  output;
  int i,j;

  //setup 32 channels, each of length 1000
  for(i=0; i<numPorts; ++i)
    ports.push_back(Pattern(ipp));

  int sum=0;
  bool bit = true;
  for(i=0; i<45; ++i){
    bit = !bit;
    for(j=0; j<i+1; j++){
      ports[0][sum] = bit;
      sum += 1;
    }
  }

  cout << "sum = " << sum << endl;

  RpgSignalFormatter sf;
  RpgIIF iif;
  sf(ports, iif);

  BOOST_CHECK(true);
}
