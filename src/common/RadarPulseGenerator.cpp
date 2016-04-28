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
#include <fstream>

#include <bpg-v2/Common/IRules.hpp>
#include <bpg-v2/Instruments/Rpg/RpgSignalFormatter.hpp>
#include <bpg-v2/Instruments/Rpg/RpgTypes.hpp>
#include <bpg-v2/Instruments/Rpg/RadarPulseGenerator.hpp>
#include <bpg-v2/Instruments/Rpg/RpgIIF.hpp>
#include <bpg-v2/Instruments/Rpg/RpgRules.hpp>


using namespace std;
using namespace rpg;
//using namespace arecibo;

namespace RPG {

  //static callback for factory registration
  IInstrumentDefinition* Callback(){ return new RadarPulseGenerator(); }
  bool result = InstrumentFactory::Instance().RegisterInstrument("rpg",RPG::Callback);

}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void RadarPulseGenerator::WriteIIF(const string& fileName)
{
   RpgSignalFormatter radarSignalFormatter;

   // get RPG interface
   RpgIIF& iif = rules_->IIFRef();

   // get ports
   PatternVector& ports = rules_->PortRef();

   // generate signals
   radarSignalFormatter(ports,iif);

   ofstream out(fileName.c_str(), ios::out);

   if(!out)
   { 
      throw std::runtime_error("Output File " + fileName + " could not be opened");
   }

   SignalVector::const_iterator sAIter = iif.stateVectorA.begin();
   SignalVector::const_iterator sBIter = iif.stateVectorB.begin();
   SignalVector::const_iterator dAIter = iif.durVectorA.begin();
   SignalVector::const_iterator dBIter = iif.durVectorB.begin();

   //add clock divider a
   for(unsigned int idx=0; idx<iif.portLength; ++idx)
   {
      out << *(sAIter++) << endl;
      out << *(dAIter++) << endl;
   }
   out << iif.clkDivA << endl;
   out << iif.numStatesA << endl;

   //add clock divider b
   for(unsigned int idx=0; idx<iif.portLength; ++idx)
   {
      out << *(sBIter++) << endl;
      out << *(dBIter++) << endl;
   }
   out << iif.clkDivB << endl;
   out << iif.numStatesB;

   cout << "writing output file" << endl;
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
IRules & RadarPulseGenerator::GetRules(const string& fileName)
{

   string buffer;

   ifstream in(fileName.c_str());

   if(!in) throw runtime_error("RadarPulseGenerator::GetRules - Could not open" + fileName);

   while(!in.eof())
   {
      getline(in,buffer);
      StripToken(buffer);

      if(buffer.find("rules") != string::npos)
      {
         int idx = buffer.find("=");
         transmitter_ = buffer.substr(idx+1,buffer.length());
      }
   }

   rules_ = dynamic_cast<RpgRules*>(InstrumentRuleFactory::Instance().Create(transmitter_));

   return *rules_;
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void RadarPulseGenerator::Tokenize(const string& fileName)
{
   string buffer;
   ifstream in(fileName.c_str());

   if(!in) throw runtime_error("FindInstrument:: Could not open" + fileName);

   while(!in.eof())
   {
      getline(in,buffer);
      StripToken(buffer);

      if(
            buffer.find("instrument")==string::npos && 
            buffer.find("rules")==string::npos &&
            buffer[0]!='\n' && 
            !buffer.empty()
        )
      {
         tokens_.push_back(buffer);
      }
   }
}

