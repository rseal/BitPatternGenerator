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
///////////////////////////////////////////////////////////////////////////
///shell.cpp
///
///The shell program is the text user interface to the radar controller.
///
///Authors: Ryan Seal, Alex Hackett
///Modified: 6/26/09
//////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>

#include <bpg-v2/Instruments/Rpg/Console/Console.hpp>
#include <bpg-v2/Instruments/Rpg/Command/Commands.hpp>
#include <bpg-v2/Instruments/Rpg/Exceptions.hpp>
#include <bpg-v2/Instruments/Rpg/Mode/ModeArray.hpp>
#include <bpg-v2/Instruments/Rpg/okFrontPanelDLL.h>
#include <sthread/Lock.hpp>
#include <bpg-v2/Instruments/Rpg/Command/CommandArray.hpp>
#include <bpg-v2/Display/CFA634.hpp>
#include <bpg-v2/Common/LCDController.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>

using namespace std;

const string imageDir = "/usr/local/bpg/firmware/";

int main(){

  typedef ColorConsole CC;
  boost::shared_ptr< CFA634 > lcd;
  boost::shared_ptr< LCDController > lcdController;

  try{

  //instantiate proper LCD module
  lcd = boost::shared_ptr< CFA634 >( new CFA634("/dev/ttyUSB0",4,20) );
  lcdController = boost::shared_ptr< LCDController >( new LCDController(*lcd.get()) );

  //initialize lcd
  lcd->BootScreen();

  //start lcd controller
  lcdController->Start();
  }
  catch( std::runtime_error e )
  { cout << "Unable to open LCD display " << endl; }

  //load the library
  if(!okFrontPanelDLL_LoadLib(NULL)){
    cerr << "bpg-shell:okFrontPanelDLL_LoadLib failed" << endl;;
    exit(1);
  }

  //connection to OpalKelly fpga module
  boost::shared_ptr<okCUsbFrontPanel> target(new okCUsbFrontPanel);

  int     numDevices = target->GetDeviceCount();
  int     quit       = 0;
  Console console;
  string  command;

  //global mutex for locking between threads
  Mutex gMutex;

  ControlStatus controlStatus(*target, quit, gMutex);    

  //vector to hold radar modes
  ModeArray modeArray;

  //Command container
  CommandArray commands;

  //preamble
  console.Write(CC::CYAN,"Bit Pattern Generator (BPG) version 1.1  2009\n");
  console.Write(CC::BROWN,"Ryan Seal, rlseal@gmail.com\n");
  console.Write(CC::BROWN,"Alex Hackett, alh5107@psu.edu\n");
 
  try{ 
    console.Write("Search for target device                     ",CC::SYSTEM,true);
    console.Write(CC::RED, " ---> ");
    console.Write(CC::YELLOW, "Found " + boost::lexical_cast<string>(numDevices) + " device(s)\n");
    if(!numDevices) { throw rpg::NoDevice();}

    console.Write("Opening target for communication             ", CC::SYSTEM,true);
    if(target->OpenBySerial() < 0) throw rpg::CommFailure();
    console.Write(CC::RED, " ---> ");
    console.Write(CC::YELLOW,"Success\n");

    console.Write("Loading PLL defaults from EEPROM on target   ", CC::SYSTEM,true);
    if(target->LoadDefaultPLLConfiguration() < 0) throw rpg::PLLFailure();
    console.Write(CC::RED, " ---> ");
    console.Write(CC::YELLOW,"Success\n");
    
    console.Write("Loading Bit Pattern Generator Image to target", CC::SYSTEM,true);
    if(target->ConfigureFPGA(imageDir+"/bpg.bit") < 0) throw rpg::ConfigFailure();
    console.Write(CC::RED, " ---> ");
    console.Write(CC::YELLOW,"Success\n");

    console.Write("Initializing Image                           ", CC::SYSTEM,true);
    console.Write(CC::RED, " ---> ");
    console.Write(CC::YELLOW,"Success\n");
    //reset and initialize the fpga code.
    controlStatus.Initialize();
    console.Write("Device is initialized and ready for operation\n", CC::SYSTEM);
    console.Write("Type <help> for a list of commands\n", CC::SYSTEM);

  } catch(rpg::Exception& error){
    error.PrintError();
    //unload the library
    okFrontPanelDLL_FreeLib();
    exit(1);
  }

  //create commands for the bpg
  typedef boost::shared_ptr<Command> CommandPtr;

  CommandPtr exitCmd
    (
     new Exit(
	      "exit",
	      " stop the system and exit the bit pattern generator",
	      quit
	      )
     );
    
  CommandPtr addCmd
    (
     new Add(
	     "add",
	     //special spacing for help display string - do not move
	     " add a new mode to the system while idle or running mode is\n"
	     "                    specified by file name and path is needed"
	     " if not in the\n                    local directory",
	     *target, 
	     modeArray, 
	     controlStatus,
	     gMutex,
	     console
	     )
     );
    
  CommandPtr removeCmd
    (
     new Remove(
		"remove",
		" remove a mode given by its filename",
		modeArray,
		console
		)
     );

  CommandPtr helpCmd 
    ( 
     new Help(
	      "help",
	      " prints this list",
	      commands,
	      console
	      )
     );
    
  CommandPtr fpgaImageCmd 
    (
     new FPGAImage(
		"image",
		" configure FPGA with new image - specify the image name "
		"(bit file) ",
		*target, 
		gMutex,
		console
		)
     );

  CommandPtr statusCmd 
    ( 
     new Status(
		"status",
		" returns FPGA status word for each channel (useful for debugging) ",
		*target, 
		controlStatus,
		console
		)
     );
    
  CommandPtr syncCmd
    (
     new Sync(
	      "sync",
	      " set the proper sync to start the system",
	      controlStatus,
		  console
	      )
     );
    
  CommandPtr listCmd
    (
     new List(
	      "list",
	      " Lists the added modes",
	      modeArray,
	      console
	      )
     );

  CommandPtr startCmd
    (
     new Start(
	       "start",
	       " starts the bit pattern generator if mode(s) are loaded",
	       *target,
	       modeArray,
	       controlStatus,
	       console
	       )
     );

  CommandPtr stopCmd
    (
     new Stop(
	      "stop",
	      " stops the bit pattern generator and zeros the output bits",
	      *target, 
	      controlStatus,
	      console
	      )
     );

  CommandPtr switchCmd
    (
     new Switch(
		"switch",
		" sends a signal to switch bpg modes",
		*target, 
		modeArray,
		controlStatus,
		*lcdController.get(),
		console)
     );

  CommandPtr clkCmd
    ( 
     new Clock(
	       "clock"                   ,
	       " sets the clock source",
	       *target                 , 
	       controlStatus           ,
	       console
	       )
     );

  CommandPtr dacCmd
    ( 
     new Dac(
	     "dac",
	     " Enables or disables the DAC on port b",
	     controlStatus,
	     console
	     )
     );
    
  CommandPtr resetCmd
    ( 
     new Reset(
	       "reset",
	       " reset the FPGA",
	       controlStatus,
	       console
	       )
     );
    
  CommandPtr clpCmd
    ( 
     new Clp(
	     "clp"                          ,
	     " Enables or disables the CLP" ,
	     controlStatus,
	     console
	     )
     );

  //add commands to container
  commands.Add( exitCmd   );
  commands.Add( addCmd    );
  commands.Add( removeCmd );
  commands.Add( helpCmd   );
  commands.Add( fpgaImageCmd );
  commands.Add( statusCmd );
  commands.Add( syncCmd   );
  commands.Add( listCmd   );
  commands.Add( startCmd  );
  commands.Add( stopCmd   );
  commands.Add( switchCmd );
  commands.Add( clkCmd    );
  commands.Add( resetCmd  );
  commands.Add( dacCmd    );
  commands.Add( clpCmd    );

  //add container to console
  console.AddCommands(commands);
  
  //main program loop - accept input until user exit program
  while(!quit){ console.Read();}
  
  cout << "goodbye" << endl;
  controlStatus.Wait();

  //unload the library
  okFrontPanelDLL_FreeLib();

  return 0;
}

