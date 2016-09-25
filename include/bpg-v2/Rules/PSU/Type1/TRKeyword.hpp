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
#include <limits>
#include <cmath>

namespace psu1{


   // define rules
   const double TR_PRE_MIN_USEC = 10.0e-6;
   const double TR_POST_MIN_USEC = 10.0e-6;

   typedef boost::tuple<LocationVector, double, double> TrTuple;
   typedef std::vector<TrTuple> TrTupleVector;

   class TRKeyword: public Keyword<TrTuple >
   {
      private:

         double pre_;
         double post_;

         void Detect(const std::string& token, double baudWidth);

         // Validate signals with predetermined rules
         inline void Verify()
         { 
            const double EPSILON = 1e-9;

            // pre min check
            if( pre_ < TR_PRE_MIN_USEC && fabs(pre_-TR_PRE_MIN_USEC) > EPSILON)
               throw std::runtime_error("TR PRE " + boost::lexical_cast<std::string>(pre_) + "<" +
                  boost::lexical_cast<std::string>(TR_PRE_MIN_USEC ));

            // post min check
            if( post_ < TR_POST_MIN_USEC && fabs(post_-TR_POST_MIN_USEC) > EPSILON)
               throw std::runtime_error("TR POST " + boost::lexical_cast<std::string>(post_) + "<" +
                  boost::lexical_cast<std::string>(TR_POST_MIN_USEC ));

            std::cout << "TR verify " <<  std::endl;
         }

      public:
         TRKeyword(): Keyword<TrTuple>("tr"){};
   };

}; // namespace psu1
#endif
