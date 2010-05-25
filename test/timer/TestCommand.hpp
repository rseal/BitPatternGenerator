#ifndef TEST_COMMAND_HPP
#define TEST_COMMAND_HPP

#include <bpg-v2/Instruments/Rpg/Command/Command.hpp>
#include <iostream>

// TestCommand class to test Timer class
class TestCommand : public Command {
   public:

      TestCommand(): Command( "Test", "TestCommand"){}

      void Execute() {
         std::cout << "TestCommand::Execute() called" << std::endl;
      }
};

#endif
