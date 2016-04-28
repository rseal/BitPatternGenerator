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
//////////////////////////////////////////////////////////////////////////////////////////
///\file Exceptions.h
///
/// Provides a list of commonly thrown exceptions.
///
///Author: Ryan Seal
///Modified: 5/27/09
//////////////////////////////////////////////////////////////////////////////////////////
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>

namespace rpg{

//////////////////////////////////////////////////////////////////////////////////
///\brief General exception is thrown
//////////////////////////////////////////////////////////////////////////////////
class Exception {
 public:
  virtual void PrintError() { std::cerr << "General Exception thrown" << std::endl;}
};

//////////////////////////////////////////////////////////////////////////////
///\brief No FPGA devices are found
//////////////////////////////////////////////////////////////////////////////
class NoDevice: public Exception{
 public:
  virtual void PrintError() { std::cerr << "No Devices Found" << std::endl;}
};

/////////////////////////////////////////////////////////////////////////////
///\brief Communication error between host and FPGA
////////////////////////////////////////////////////////////////////////////
 class CommFailure: public Exception{
 public:
  virtual void PrintError() { std::cerr << "Communication Failure" << std::endl;}
 };

///////////////////////////////////////////////////////////////////////////
///\brief Phase Lock Loop failure
//////////////////////////////////////////////////////////////////////////
 class PLLFailure: public Exception{
 public:
  virtual void PrintError() { std::cerr << "PLL Failure" << std::endl;}
 };

/////////////////////////////////////////////////////////////////////////
///\brief Error downloading the image to the FPGA
////////////////////////////////////////////////////////////////////////
 class ConfigFailure: public Exception{
 public:
  virtual void PrintError() { std::cerr << "FPGA Configuration Failure" << std::endl;}
 };
};



#endif
