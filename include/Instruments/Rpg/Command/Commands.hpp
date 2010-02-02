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
