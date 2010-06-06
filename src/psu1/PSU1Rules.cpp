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
#include <boost/tuple/tuple.hpp>
#include <boost/bind.hpp>
#include <bpg-v2/Common/Keyword.hpp>
#include <bpg-v2/Common/Unit.hpp>
#include <bpg-v2/Common/Location.hpp>
#include <bpg-v2/Rules/PSU/Type1/PSU1Rules.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;
using namespace rpg;

namespace psu1 
{
   IRules* Callback(){ return new PSU1Rules(); }
   bool result = InstrumentRuleFactory::Instance().RegisterRule("psu1",Callback);


   void PSU1Rules::Detect(const TokenVector& tv){

      for(uint i=0; i<tv.size(); ++i){
         trKey.Process(tv[i]);
         txaKey.Process(tv[i]);
         codeKey.Process(tv[i]);
         gKey.Process(tv[i]);
         t1Key.Process(tv[i]);
         t2Key.Process(tv[i]);
         saKey.Process(tv[i]);
      }
   };

   const bool PSU1Rules::Verify(){

      uint i,j,k,ch;
      uint h0,hf;
      bool isNeg;

      //contains tuple<LocationVector, Pattern, float>
      //single entry
      const vector<CodeTuple>& cTuple = codeKey.GetTupleRef();

      //contains tuple<LocationVector, float, float>
      //single entry
      const vector<TrTuple>& trTuple  = trKey.GetTupleRef();

      //contains tuple<LocationVector, float>
      //single entry
      const vector<TxaTuple>& txaTuple = txaKey.GetTupleRef();

      //contains tuple<LocationVector, bool, float, float>
      //multiple entries
      const vector<SaTuple>& saTuple = saKey.GetTupleRef();

      //contains simple Parameter
      //multiple entries
      const ParameterVector& t1Tuple   = t1Key.GetTupleRef();

      vector<GenericTuple> gTuple; 

      
      //contains simple Parameter
      //single entry
      //const ParameterVector& t2Tuple   = t2Key.GetTupleRef();

      const float txa_l   = txaTuple[0].get<1>();
      const float bauda_l = any_cast<float>(param::FindParameter(t1Tuple, "bauda").value)*1e6;
      const float baudb_l = any_cast<float>(param::FindParameter(t1Tuple, "baudb").value)*1e6;
      const float rfclk   = any_cast<float>(param::FindParameter(t1Tuple, "refclock").value);
      const float ipp     = any_cast<float>(param::FindParameter(t1Tuple, "ipp").value)*1e6;


      volatile const float divClkA = rfclk*bauda_l/2e6;
      volatile const float divClkB = rfclk*baudb_l/2e6;

      iif_.clkDivA = divClkA;
      iif_.clkDivB = divClkB;

      //const float ipp_b   = rfclk/ipp;
      const float dc      = txa_l/ipp;      
      const float code_l  = cTuple[0].get<2>()*bauda_l;

      //verify that code width matches the transmitted pulse width
      if(txa_l != code_l) {
         cerr << "TXA Pulse Width != CODE Pulse Width => " << txa_l << " != " << code_l << endl;
         throw std::runtime_error("PSU1Rules: TXA length != CODE length");
      }

      //verify that code width matches the transmitted pulse width
      if( dc > MAX_DUTY_CYCLE ) 
         throw std::runtime_error("PSU1Rules - DUTY CYCLE > " + 
               lexical_cast<string>(MAX_DUTY_CYCLE) );

      float chLengthA = ipp/bauda_l;
      float chLengthB = ipp/baudb_l;

      //resize port A channels to proper length
      for(i=0; i<16; ++i) ports_[i].resize(chLengthA);

      //resize port B channels to proper length
      for(i=16; i<32; ++i) ports_[i].resize(chLengthB);

      //store all locations and compare to 
      //ensure unique assignments
      LocationVector tLoc;

      //push sa locations 
      for(i=0; i<saTuple.size(); ++i){
         LocationVector t = saTuple[i].get<0>();
         tLoc.insert(tLoc.end(), t.begin(), t.end());
      }

      try{

         gTuple = gKey.GetTupleRef();

         //push generic location
         for(i=0; i<gTuple.size(); ++i){
            LocationVector t = gTuple[i].get<0>();
            tLoc.insert(tLoc.end(), t.begin(), t.end());
         }
      } catch ( std::runtime_error& e) {
         cout << "no generic keywords found" << endl;
      }

      //push all other locations
      LocationVector t = txaTuple[0].get<0>();
      tLoc.insert(tLoc.end(), t.begin(), t.end() );
      t = trTuple[0].get<0>();
      tLoc.insert(tLoc.end(), t.begin(), t.end() );
      t = cTuple[0].get<0>();
      tLoc.insert(tLoc.end(), t.begin(), t.end() );


      //lazy way to check for duplicate signal assignments
      for(i=0; i<tLoc.size(); ++i)
         for(j=i+1; j<tLoc.size(); ++j)
            if(tLoc[i].channel == tLoc[j].channel)
               if(tLoc[i].port == tLoc[j].port){
                  cout << tLoc[i].port << "." << tLoc[i].channel << " ";
                  throw std::runtime_error("SIGNALS are assigned to the same port.channel");
               }

      //VERIFICATION PASSED at this point

      //Begin Building signals into Preformatted forms

      //(1) BUILD TR Signal
      const float pre         = trTuple[0].get<1>();
      const float post        = trTuple[0].get<2>();
      const float trWidth     = pre + txa_l + post;
      LocationVector lv = trTuple[0].get<0>();
      uint sz = lv.size();

      //(1) BUILD TR SIGNAL
      for(i=0; i<sz; ++i){
         for(j=0; j<trWidth; ++j)
            ports_[ChIndex(lv,i)].set(j,true);
      }

      //(2) BUILD TXA Signal
      lv = txaTuple[0].get<0>();
      sz = lv.size();
      for(i=0; i<sz; ++i){
         for(j=0; j<txa_l; ++j)
            ports_[ChIndex(lv,i)].set(j+pre,true);
      }

      //(3) BUILD CODE Signal
      lv = cTuple[0].get<0>();
      const Pattern p = cTuple[0].get<1>();
      sz = lv.size();
      for(i=0; i<sz; ++i){
         ch = ChIndex(lv,i);
         for(j=0; j<p.size(); ++j) ports_[ch][pre+j] = p[j];
      }

      //(4) BUILD SA SIGNALS
      // These are the sampling windows
      // There is a negate option to correctly trigger Julio's system.
      for(i=0; i<saTuple.size(); ++i){
         lv    = saTuple[i].get<0>();
         isNeg = saTuple[i].get<1>(); 
         h0    = static_cast<int>(saTuple[i].get<2>());
         hf    = static_cast<int>(saTuple[i].get<3>());
         for(j=0; j<lv.size(); ++j){
            ch = ChIndex(lv,j);
            //window's point of reference is TXA and not t=0 since we
            //are using a TR window to protect the receivers (i.e. add pre offset)
            cout << "h0=" << h0 << " hf=" << hf << endl;
            for(k=h0+pre; k<hf+pre; ++k) ports_[ch][k]=true;
            if(isNeg) ports_[ch].flip(); 
         } 
      }

      //(5) BUILD GENERIC SIGNALS
      //GenericTuple contains tuple<LocationVector, Pattern>
      //multiple entries
      //GenericKeywords are optional, so check and see if one or more were detected
      if(gKey.Set()){
         //         const vector<GenericTuple>& gTuple = gKey.GetTupleRef();

         //push generic locations 
         //if(gKey.Set()){
         //   for(i=0; i<gTuple.size(); ++i){
         //      LocationVector t = gTuple[i].get<0>();
         //      tLoc.insert(tLoc.end(), t.begin(), t.end());
         //   }
         //}

         for(i=0; i<gTuple.size(); ++i){
            lv = gTuple[i].get<0>();
            const Pattern p = gTuple[i].get<1>();
            for(j=0; j<lv.size(); ++j){
               const int ch = ChIndex(lv,j);
               ports_[ch] = p;
               ports_[ch].resize(('a'==lv[j].port)? chLengthA : chLengthB);
            } 
         }
      }
      return true;
   } 

}; // namespace psu1
