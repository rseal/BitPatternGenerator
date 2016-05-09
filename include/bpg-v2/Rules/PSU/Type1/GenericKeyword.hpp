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
#ifndef GENERIC_KEYWORD_H
#define GENERIC_KEYWORD_H

#include <boost/dynamic_bitset.hpp>
#include <boost/tuple/tuple.hpp>
#include <bpg-v2/Common/Keyword.hpp>
#include <bpg-v2/Common/UnitConvert.hpp>
#include <bpg-v2/Common/Location.hpp>

namespace psu1{

   typedef boost::tuple<LocationVector, boost::dynamic_bitset<> > GenericTuple;
   typedef std::vector<GenericTuple> GenericTupleVector;

   class GenericKeyword: public Keyword<GenericTuple>
   {
      private:

         typedef boost::dynamic_bitset<> Pattern;

         void Detect(const std::string& token);

         void Verify(){ std::cout << "GENERIC verify" << std::endl;}

         void FormatPattern(Pattern& pattern,std::vector<uint>& codeVec, 
               std::vector<bool>& signVec)
         {
            for(uint16_t idx=0; idx<codeVec.size(); ++idx)
            {
               for(uint16_t jdx=0; jdx<codeVec[idx]; ++jdx)
               {
                  pattern.push_back(!signVec[idx]);
               }
            }
         }

      public:
         GenericKeyword(): Keyword<GenericTuple>("generic"){};
   };

}; // namespace psu1
#endif