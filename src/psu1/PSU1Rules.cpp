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

#include <iostream>
#include <cstdint>
#include <cfloat>

#include <boost/tuple/tuple.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>

#include <bpg-v2/Common/Keyword.hpp>
#include <bpg-v2/Common/Unit.hpp>
#include <bpg-v2/Common/Location.hpp>
#include <bpg-v2/Rules/PSU/Type1/PSU1Rules.hpp>

using namespace std;
using namespace boost;
using namespace rpg;

namespace psu1 
{
   // Register rule set with rule factory 
   IRules* Callback(){ return new PSU1Rules(); }
   bool result = InstrumentRuleFactory::Instance().RegisterRule("psu1",Callback);

   /////////////////////////////////////////////////////////////////////////////
   //
   /////////////////////////////////////////////////////////////////////////////
   void PSU1Rules::Detect(const TokenVector& tv)
   {
      for(unsigned int i=0; i<tv.size(); ++i)
      {
         gKey.Process(tv[i]);
         t1Key.Process(tv[i]);
         t2Key.Process(tv[i]);
      }

      const double bauda = any_cast<double>(param::FindParameter(t1Key.GetTupleRef(), "bauda").value);

      for(unsigned int i=0; i<tv.size(); ++i)
      {
         trKey.Process(tv[i],bauda);
         txaKey.Process(tv[i],bauda);
         codeKey.Process(tv[i]);
         saKey.Process(tv[i]);
      }
   }

   /////////////////////////////////////////////////////////////////////////////
   //
   /////////////////////////////////////////////////////////////////////////////
   bool PSU1Rules::Verify()
   {
      //store all locations and compare to 
      //ensure unique assignments
      LocationVector globalLocations;

      //contains tuple<LocationVector, Pattern, double>
      //single entry
      const CodeTupleVector& codeTupleVec = codeKey.GetTupleRef();

      //contains tuple<LocationVector, double, double>
      //single entry
      const TrTupleVector& trTupleVec = trKey.GetTupleRef();

      //contains tuple<LocationVector, double>
      //single entry
      const TxaTupleVector& txaTupleVec = txaKey.GetTupleRef();

      //contains tuple<LocationVector, bool, double, double>
      //multiple entries
      const SaTupleVector& saTupleVec = saKey.GetTupleRef();

      //contains simple Parameter
      //multiple entries
      const ParameterVector& t1Tuple = t1Key.GetTupleRef();

      //contains tuple<LocationVector, dynamic_bitset<> >
      //optional with multiple entries
      GenericTupleVector genericTupleVec; 

      if(gKey.Set())
      {
         genericTupleVec = gKey.GetTupleRef();
      }

      //contains simple Parameter
      //single entry
      //const ParameterVector& t2Tuple   = t2Key.GetTupleRef();

      const double txa = txaTupleVec[0].get<1>();
      const double rfclk    = any_cast<double>(param::FindParameter(t1Tuple, "refclock").value);
      const double baudb    = any_cast<double>(param::FindParameter(t1Tuple, "baudb").value);
      const double ippa     = any_cast<double>(param::FindParameter(t1Tuple, "ippa").value);
      const double bauda    = any_cast<double>(param::FindParameter(t1Tuple, "bauda").value);
      const uint32_t txa_baud = round(txa/bauda);

      iif_.clkDivA = round(rfclk*bauda/2.0);
      iif_.clkDivB = round(rfclk*baudb/2.0);

      std::cout << "txa      = " << txa << std::endl;
      std::cout << "txa_baud = " << txa_baud << std::endl;
      std::cout << "rfclk    = " << rfclk << std::endl;
      std::cout << "baudb    = " << baudb << std::endl;
      std::cout << "bauda    = " << bauda << std::endl;
      std::cout << "ippa     = " << ippa << std::endl;
      std::cout << "diva     = " << iif_.clkDivA << std::endl;
      std::cout << "divb     = " << iif_.clkDivB << std::endl;

      //const double ipp_b   = rfclk/ipp;
      const double duty_cycle = txa/ippa;
      const uint32_t code_l  = codeTupleVec[0].get<2>();

      std::cout << "code length = " << code_l << std::endl;
      std::cout << "txa  length = " << txa_baud << std::endl;

      //verify that code width matches the transmitted pulse width
      if(txa_baud != code_l)
      {
         cerr << "TXA Pulse Width != CODE Pulse Width => " << txa_baud << " != " << code_l << endl;
         throw std::runtime_error("PSU1Rules: TXA length != CODE length");
      }

      //verify that code width matches the transmitted pulse width
      if( duty_cycle > MAX_DUTY_CYCLE ) 
      {
         throw std::runtime_error("PSU1Rules - DUTY CYCLE " + 
               lexical_cast<string>(duty_cycle) + " > " + 
               lexical_cast<string>(MAX_DUTY_CYCLE));
      }

      //push sa locations 
      for(uint16_t idx=0; idx<saTupleVec.size(); ++idx)
      {
         LocationVector lv = saTupleVec[idx].get<0>();
         globalLocations.insert(globalLocations.end(), lv.begin(), lv.end());
      }

      //push generic location
      for(uint16_t idx=0; idx<genericTupleVec.size(); ++idx)
      {
         LocationVector lv = genericTupleVec[idx].get<0>();
         globalLocations.insert(globalLocations.end(), lv.begin(), lv.end());
      }

      //push all other locations
      LocationVector t = txaTupleVec[0].get<0>();
      globalLocations.insert(globalLocations.end(), t.begin(), t.end() );
      t = trTupleVec[0].get<0>();
      globalLocations.insert(globalLocations.end(), t.begin(), t.end() );
      t = codeTupleVec[0].get<0>();
      globalLocations.insert(globalLocations.end(), t.begin(), t.end() );


      //lazy way to check for duplicate signal assignments
      for(uint16_t idx=0; idx<globalLocations.size(); ++idx)
      {
         for(uint16_t jdx=idx+1; jdx<globalLocations.size(); ++jdx)
         {
            if(globalLocations[idx].channel == globalLocations[jdx].channel)
            {
               if(globalLocations[idx].port == globalLocations[jdx].port)
               {
                  cout << globalLocations[idx].port << "." << globalLocations[idx].channel << " ";
                  throw std::runtime_error("SIGNALS are assigned to the same port.channel");
               }
            }
         }
      }

      return true;
   }

   /////////////////////////////////////////////////////////////////////////////
   //
   /////////////////////////////////////////////////////////////////////////////
   void PSU1Rules::Build()
   {
      //contains tuple<LocationVector, Pattern, double>
      //single entry
      const CodeTupleVector& codeTupleVec = codeKey.GetTupleRef();

      //contains tuple<LocationVector, double, double>
      //single entry
      const TrTupleVector& trTupleVec  = trKey.GetTupleRef();

      //contains tuple<LocationVector, double>
      //single entry
      const TxaTupleVector& txaTupleVec = txaKey.GetTupleRef();

      //contains tuple<LocationVector, bool, double, double>
      //multiple entries
      const SaTupleVector& saTupleVec = saKey.GetTupleRef();

      //contains simple Parameter
      //multiple entries
      const ParameterVector& t1Tuple   = t1Key.GetTupleRef();

      const double ippb     = any_cast<double>(param::FindParameter(t1Tuple, "ippb").value);
      const double baudb    = any_cast<double>(param::FindParameter(t1Tuple, "baudb").value);
      const double ippa     = any_cast<double>(param::FindParameter(t1Tuple, "ippa").value);
      const double bauda    = any_cast<double>(param::FindParameter(t1Tuple, "bauda").value);
      const double txa      = txaTupleVec[0].get<1>();

      //contains tuple<LocationVector, dynamic_bitset<> >
      //optional with multiple entries
      GenericTupleVector genericTupleVec; 

      if(gKey.Set())
      {
         genericTupleVec = gKey.GetTupleRef();
      }

      ///////////////////////////////////////////////////////////////////////////// 
      //(1) BUILD TR Signal
      ///////////////////////////////////////////////////////////////////////////// 
      BuildTrSignal(trTupleVec, txa, bauda);

      ///////////////////////////////////////////////////////////////////////////// 
      //(2) BUILD TXA Signal
      ///////////////////////////////////////////////////////////////////////////// 
      BuildTxaSignal(txaTupleVec, trTupleVec, txa, bauda); 

      ///////////////////////////////////////////////////////////////////////////// 
      //(3) BUILD CODE Signal
      ///////////////////////////////////////////////////////////////////////////// 
      BuildCodeSignal(codeTupleVec, trTupleVec, bauda);

      ///////////////////////////////////////////////////////////////////////////// 
      //(4) BUILD SA SIGNALS
      ///////////////////////////////////////////////////////////////////////////// 
      BuildSaSignal(saTupleVec, trTupleVec, bauda);

      ///////////////////////////////////////////////////////////////////////////// 
      //(5) BUILD GENERIC SIGNALS - optional, check for existence
      ///////////////////////////////////////////////////////////////////////////// 
      if(gKey.Set())
      {
         BuildGenericSignal(genericTupleVec);
      }

      uint16_t maxPortALen = 0;
      uint16_t maxPortBLen = 0;

      for(uint16_t idx=PORTA_START; idx<PORTA_END; ++idx)
      {
         if(ports_[idx].size() > maxPortALen)
         {
            maxPortALen = ports_[idx].size();
         }
      }

      const uint16_t ippa_baud = round(ippa/bauda);

      if(ippa_baud < maxPortALen)
      {
         throw std::runtime_error("PSU1Rules: PORTA IPP is less then longest signal");
      }

      maxPortALen = ippa_baud;

      for(uint16_t idx=PORTB_START; idx<PORTB_END; ++idx)
      {
         if(ports_[idx].size() > maxPortBLen)
         {
            maxPortBLen = ports_[idx].size();
         }
      }

      const uint16_t ippb_baud = round(ippb/baudb);

      if(ippb_baud < maxPortBLen)
      {
         throw std::runtime_error("PSU1Rules: PORTB IPP is less then longest signal");
      }

      maxPortBLen = ippb_baud;

      for(uint16_t idx=PORTA_START; idx<PORTA_END; ++idx)
      {
         ports_[idx].resize(maxPortALen);
      }

      for(uint16_t idx=PORTB_START; idx<PORTB_END; ++idx)
      {
         ports_[idx].resize(maxPortBLen);
         std::cout << "CHANNEL " << idx << " length = " << ports_[idx].size() << std::endl;
      }


      std::cout << "COMPLETE" << std::endl;
   } 

   /////////////////////////////////////////////////////////////////////////////
   //
   /////////////////////////////////////////////////////////////////////////////
   void PSU1Rules::BuildTrSignal(const TrTupleVector& trTupleVec, const double txa, const double bauda)
   {
      std::cout << "BUILDING TR Signal " << std::endl;
      const uint16_t pre_baud = round(trTupleVec[0].get<1>()/bauda);
      const uint16_t post_baud = round(trTupleVec[0].get<2>()/bauda);
      const uint16_t txa_baud = round(txa/bauda);
      const uint16_t tr_baud = pre_baud + txa_baud + post_baud;

      LocationVector lv = trTupleVec[0].get<0>();

      for(uint16_t idx=0; idx<lv.size(); ++idx)
      {
         const uint16_t ch_idx = ChIndex(lv,idx);
         ports_[ch_idx].resize(tr_baud);

         for(uint16_t jdx=0; jdx<tr_baud; ++jdx)
         {
            ports_[ch_idx].set(jdx,true);
         }
      }

   }

   /////////////////////////////////////////////////////////////////////////////
   //
   /////////////////////////////////////////////////////////////////////////////
   void PSU1Rules::BuildTxaSignal(const TxaTupleVector& txaTupleVec, 
         const TrTupleVector& trTupleVec, const double txa, const double bauda)
   {
      std::cout << "BUILDING TXA Signal " << std::endl;

      LocationVector lv = txaTupleVec[0].get<0>();
      const uint16_t pre_baud = round(trTupleVec[0].get<1>()/bauda);
      const double txa_baud = round(txa/bauda);

      for(uint16_t idx=0; idx<lv.size(); ++idx)
      {
         const uint16_t ch_idx = ChIndex(lv,idx);
         ports_[ch_idx].resize(pre_baud + txa_baud);

         for(uint16_t jdx=0; jdx<txa_baud; ++jdx)
         {
            const uint16_t txa_offset = jdx + pre_baud;
            ports_[ch_idx].set(txa_offset,true);
         }
      }
   }

   /////////////////////////////////////////////////////////////////////////////
   //
   /////////////////////////////////////////////////////////////////////////////
   void PSU1Rules::BuildCodeSignal(const CodeTupleVector& codeTupleVec,
         const TrTupleVector& trTupleVec, const double bauda)
   {
      std::cout << "BUILDING CODE Signal " << std::endl;

      LocationVector lv = codeTupleVec[0].get<0>();
      const Pattern pattern = codeTupleVec[0].get<1>();
      const uint16_t pre_baud = round(trTupleVec[0].get<1>()/bauda);

      for(uint16_t idx=0; idx<lv.size(); ++idx)
      {
         const uint16_t ch_idx = ChIndex(lv,idx);
         ports_[ch_idx].resize(pre_baud+pattern.size());

         for(uint16_t jdx=0; jdx<pattern.size(); ++jdx) 
         {
            const uint16_t code_offset = pre_baud + jdx;
            ports_[ch_idx][code_offset] = pattern[jdx];
         }
      }
   }

   /////////////////////////////////////////////////////////////////////////////
   //
   /////////////////////////////////////////////////////////////////////////////
   void PSU1Rules::BuildSaSignal(const SaTupleVector& saTupleVec,
         const TrTupleVector& trTupleVec, const double bauda)
   {

      std::cout << "BUILDING SA (Receive Window) Signal " << std::endl;

      for(uint16_t idx =0; idx<saTupleVec.size(); ++idx)
      {
         // get all port.channel locations
         LocationVector lv = saTupleVec[idx].get<0>();
         bool isNeg = saTupleVec[idx].get<1>(); 

         // convert to baud
         const uint16_t h0_baud  = round(saTupleVec[idx].get<2>()/bauda);
         const uint16_t hf_baud  = round(saTupleVec[idx].get<3>()/bauda);
         const uint16_t pre_baud = round(trTupleVec[0].get<1>()/bauda);

         //window's point of reference is TXA and not t=0 since we
         //are using a TR window to protect the receivers (i.e. add pre offset)
         const uint16_t h0_offset = h0_baud + pre_baud;
         const uint16_t hf_offset = hf_baud + pre_baud;

         for(uint16_t jdx=0; jdx<lv.size(); ++jdx)
         {
            const uint16_t ch_jdx = ChIndex(lv,jdx);
            ports_[ch_jdx].resize(hf_offset);

            // enable signal for defined receive window 
            for(uint16_t kdx=h0_offset; kdx<hf_offset; ++kdx)
            { 
               ports_[ch_jdx][kdx]=true;
            }

            // invert signal if negate set
            if(isNeg) { ports_[ch_jdx].flip(); }
         } 
      }
   }

   /////////////////////////////////////////////////////////////////////////////
   //
   /////////////////////////////////////////////////////////////////////////////
   void PSU1Rules::BuildGenericSignal(const GenericTupleVector& genericTupleVec)
   {
      std::cout << "BUILDING Generic Signals " << std::endl;

      for(uint16_t idx=0; idx<genericTupleVec.size(); ++idx)
      {
         // get all port.channel locations
         LocationVector lv = genericTupleVec[idx].get<0>();

         // iterate through all locations and assign signal
         for(uint16_t jdx=0; jdx<lv.size(); ++jdx)
         {
            ports_[ChIndex(lv,jdx)] = genericTupleVec[idx].get<1>();
         } 
      }
   }

}; // namespace psu1
