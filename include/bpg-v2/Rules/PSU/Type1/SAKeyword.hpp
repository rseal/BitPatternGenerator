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
#ifndef SA_KEYWORD_H
#define SA_KEYWORD_H

#include <boost/tuple/tuple.hpp>
#include <bpg-v2/Common/Location.hpp>
#include <bpg-v2/Common/Keyword.hpp>
#include <boost/lexical_cast.hpp>

namespace psu1{

   typedef boost::tuple<LocationVector, bool, double, double> SaTuple;
   typedef std::vector<SaTuple> SaTupleVector;

   class SAKeyword: public Keyword<SaTuple>
   {
      private:

         double h0_;
         double hf_;

         void Detect(const std::string& token);

         void Verify()
         {
            if(h0_ > hf_) throw std::runtime_error("SA window - " + 
                  boost::lexical_cast<std::string> ( h0_ ) + " > " +  boost::lexical_cast<std::string>( hf_ ) );
            std::cout << "SA verify" << std::endl;
         }

      public:

         SAKeyword(): Keyword<SaTuple>("sa"){};
   };

}; // namespace psu1
#endif
