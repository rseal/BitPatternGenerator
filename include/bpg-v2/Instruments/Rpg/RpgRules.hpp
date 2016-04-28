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
#ifndef RPG_RULES_H
#define RPG_RULES_H

#include <bpg-v2/Common/IRules.hpp>
#include <bpg-v2/Instruments/Rpg/RpgTypes.hpp>
#include <bpg-v2/Instruments/Rpg/RpgIIF.hpp>



class RpgRules: public IRules
{
   static const unsigned int NUM_PORTS = 32;

   protected:
   RpgIIF iif_;
   rpg::PatternVector ports_;

   public:
   RpgRules(): ports_(NUM_PORTS){}
   rpg::PatternVector& PortRef() { return ports_;}
   RpgIIF& IIFRef() { return iif_;}
};

#endif
