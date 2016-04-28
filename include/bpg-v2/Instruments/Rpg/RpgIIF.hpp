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
#ifndef RPG_IIF_H
#define RPG_IIF_H

#include <cstdint>
#include <bpg-v2/Instruments/Rpg/RpgTypes.hpp>

struct RpgIIF
{
   public:

      static const int PORT_LENGTH = 2048;

      uint16_t portLength;
      rpg::SignalVector stateVectorA;
      rpg::SignalVector stateVectorB;
      rpg::SignalVector durVectorA;
      rpg::SignalVector durVectorB;
      uint16_t clkDivA;
      uint16_t clkDivB;
      uint16_t numStatesA;
      uint16_t numStatesB;

      RpgIIF():portLength(PORT_LENGTH){}
};



#endif
