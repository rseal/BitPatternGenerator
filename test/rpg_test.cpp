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
#define BOOST_TEST_MODULE RadarPulseGeneratorTest
#include <boost/test/included/unit_test.hpp>

#include <bpg-v2/Instruments/Rpg/RadarPulseGenerator.hpp>
#include <bpg-v2/Common/InstrumentFinder.hpp>
#include <bpg-v2/Common/IRules.hpp>

BOOST_AUTO_TEST_CASE(radarPulseGenerator_test){

  typedef vector<string> TokenVector;
  InstrumentFinder iFinder;

  //Locate the instrument according to the specified INSTRUMENT
  IInstrumentDefinition& instrument = iFinder.Find("test.hif");

  BOOST_CHECK(instrument.Init("test.hif", "output.hif"));

  //free instrument 
  delete &instrument;
  
}
