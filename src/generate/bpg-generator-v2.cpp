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

#include <bpg-v2/Instruments.hpp>
#include <bpg-v2/Common/InstrumentFinder.hpp>
#include <clp/CommandLineParser.hpp>

#include <iostream>

using namespace std;

int main(int argc,char** argv){

  //set default output file
  string outputFile = "output.iif";

  CommandLineParser cmd(argc,argv);
  
  //add help switch
  string help = "Displays command line options";
  Switch help1Sw("h",help, false);
  Switch help2Sw("help", help, false);

  cmd.AddSwitch(help1Sw);
  cmd.AddSwitch(help2Sw);

  //add version switch
  string version = "Prints version information";
  Switch vSw("v",version,false);
  Switch versionSW("version",version,false);
  cmd.AddSwitch(vSw);
  cmd.AddSwitch(versionSW);

  //add debug switch
//   string debug = "Prints debug information";
//   cmd.AddSwitch("d", debug, false);
//   cmd.AddSwitch("debug", debug, false);
    
  //add output file option
  Arg outputArg("o", "<filename> Name of generated output file", 1, false);
  cmd.AddArg(outputArg);

  //parse command line
  cmd.Parse();

  //print version info if set
  if(cmd.SwitchSet("v") || cmd.SwitchSet("version")){
    cout << "bpg v2.0-01202010" << endl;
    exit(0);
  }

  //print help info if set
  if(cmd.SwitchSet("help") || cmd.SwitchSet("h")){
    cout << "Usage: bpg-generate <options> <sourcefiles>\n" << endl;
    cout << "possible options include:\n" << endl;
    cmd.PrintHelp();
    exit(0);
  }

  //set output file if set
  if(cmd.ArgSet("o"))
    outputFile = cmd.GetArgValue<string>("o");
    

  //assume last argument is file name to parse
  string inFile(argv[argc-1]);

  ifstream exist(inFile.c_str(),ios::in);
  if(!exist)
    {
      cout << endl << "!!! " << inFile << " not understood !!!\n" << endl;
      cmd.PrintHelp();
      exit(1);
    }

  InstrumentFinder iFinder;

  //Locate the instrument according to the specified INSTRUMENT
  IInstrumentDefinition& instrument = iFinder.Find(inFile);

  instrument.Init(inFile, outputFile);
  //free instrument 
  delete &instrument;

  return 0;  
}
