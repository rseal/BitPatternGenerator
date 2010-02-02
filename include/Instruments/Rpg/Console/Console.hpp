////////////////////////////////////////////////////////////////////////////////
///\file Console.h
///
/// The Console structure provides an interface to add and manage a list of 
/// commands. The Read method accepts input from a terminal window and searches
/// the command list - looking for a match to the user's input. If the command
/// is found - the Function pointer bound to the command is executed.
///
///Author: Ryan Seal
///Modified: 05/12/2009
////////////////////////////////////////////////////////////////////////////////
#ifndef CONSOLE
#define CONSOLE

#include <iostream>
#include <vector>
#include <iomanip>
#include <boost/shared_ptr.hpp>
#include <bpg-v2/Instruments/Rpg/Console/ColorConsole.hpp>
#include <bpg-v2/Instruments/Rpg/Command/CommandArray.hpp>
#include <boost/algorithm/string.hpp>

///\brief The Console structure allows the developer to add and manage a list 
///of commands provided by the developer. User input is compared with the 
///command list and, if a match is found, the command's function pointer is
///executed. This allows a developer to easily add custom commands.
class Console: public ColorConsole{
  typedef ColorConsole CC;
  CommandArray commands_;
  std::string userPrompt; 
  std::string systemPrompt;
  ConsoleScheme consoleScheme_;
 
 public:
    
  Console(): consoleScheme_("bpg:user> ", CC::GREEN, "bpg: sys> ", CC::BLUE){
    this->Scheme(consoleScheme_);
  };

  ResetPrompt(){
    this->SystemPrompt("bpg: sys> ");
    this->UserPrompt("bpg:user> ");
  }

/// Interface to add a custom command. Inputs are the command name, a description of the 
/// command's purpose and a function pointer to execute the programmed behavior when 
/// called by the user from the shell.
  void AddCommands(const CommandArray& commands) { commands_ = commands;}

/// System responses are separated from user responses by a particular prompt.
  void Format(const std::string& str){ std::cout << userPrompt + str << std::endl;}

/// Reads user input from the shell and searches for a match with the loaded commands.
  void Read() { 
    bool found = false;
    std::string token;
    UserPrompt();
    getline(std::cin,token);
    boost::trim(token);

    if(!token.empty()) found = commands_.Run(token);
        
    if(!found && !token.empty()){
      SystemPrompt();
      this->Write(CC::RED, "Command ");
      this->Write(CC::YELLOW, token);
      this->Write(CC::RED, " not found\n");
    }

    ResetPrompt();
  }
    
};

#endif
