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
////////////////////////////////////////////////////////////////////////////////
///\file Commands.h
///
///This file holds commands used by the bpg program. All commands
///derive from the Command class, giving them a common interface. Customized
///information is created for each class and initialized by the class's
///constructor.
///
///Authors: Ryan Seal, Alex Hackett
///Modified: 6/26/09
////////////////////////////////////////////////////////////////////////////////

#ifndef COMMANDS
#define COMMANDS

#include <bpg-v2/Instruments/Rpg/Command/Commands/Add.hpp>
#include <bpg-v2/Instruments/Rpg/Command/Commands/Clock.hpp>
#include <bpg-v2/Instruments/Rpg/Command/Commands/Clp.hpp>
#include <bpg-v2/Instruments/Rpg/Command/Commands/Dac.hpp>
#include <bpg-v2/Instruments/Rpg/Command/Commands/Exit.hpp>
#include <bpg-v2/Instruments/Rpg/Command/Commands/FPGAImage.hpp>
#include <bpg-v2/Instruments/Rpg/Command/Commands/Help.hpp>
#include <bpg-v2/Instruments/Rpg/Command/Commands/List.hpp>
#include <bpg-v2/Instruments/Rpg/Command/Commands/Remove.hpp>
#include <bpg-v2/Instruments/Rpg/Command/Commands/Reset.hpp>
#include <bpg-v2/Instruments/Rpg/Command/Commands/Start.hpp>
#include <bpg-v2/Instruments/Rpg/Command/Commands/Status.hpp>
#include <bpg-v2/Instruments/Rpg/Command/Commands/Stop.hpp>
#include <bpg-v2/Instruments/Rpg/Command/Commands/Switch.hpp>
#include <bpg-v2/Instruments/Rpg/Command/Commands/Sync.hpp>

#endif
