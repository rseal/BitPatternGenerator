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
#ifndef TR_KEYWORD_H
#define TR_KEYWORD_H

#include <boost/tuple/tuple.hpp>
#include <bpg-v2/Common/Location.hpp>
#include <bpg-v2/Common/Keyword.hpp>
#include <boost/lexical_cast.hpp>

namespace psu1{

   // define rules
   const int TR_PRE_MIN = 10;
   const int TR_POST_MIN = 10;

   typedef boost::tuple<LocationVector, float, float> TrTuple;
   typedef std::vector<TrTuple> TrTupleVector;

   class TRKeyword: public Keyword<TrTuple >
   {
      private:

         float pre_;
         float post_;

         void Detect(const std::string& token);

         // Validate signals with predetermined rules
         inline void Verify()
         { 
            // pre min check
            if( pre_ < TR_PRE_MIN ) throw std::runtime_error("TR PRE < " + 
                  boost::lexical_cast<std::string>( TR_PRE_MIN ));

            // post min check
            if( post_ < TR_POST_MIN ) throw std::runtime_error("TR POST < " + 
                  boost::lexical_cast<std::string>( TR_POST_MIN ));

            std::cout << "TR verify " <<  std::endl;
         }

      public:
         TRKeyword(): Keyword<TrTuple>("tr"){};
   };

}; // namespace psu1
#endif
