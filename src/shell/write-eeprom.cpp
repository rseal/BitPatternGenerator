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
#include <cstdlib>

#include <bpg-v2/Instruments/Rpg/okFrontPanelDLL.h>

using namespace std;

int main(){

  const static float REF_CLOCK_MHZ = 48.0f;
  const static float P = 10;
  const static float Q = 6;
  const static float DIV1N = 4;

  //load the library
  if(!okFrontPanelDLL_LoadLib(NULL)){
    cerr << "bpg-shell:okFrontPanelDLL_LoadLib failed" << endl;;
    exit(1);
  }

  //connection to OpalKelly fpga module
  okCUsbFrontPanel* target = new okCUsbFrontPanel();

  okCPLL22150* pll = new okCPLL22150();
  pll->SetReference( REF_CLOCK_MHZ , false );
  pll->SetDiv1( okCPLL22150::DivSrc_VCO, DIV1N );
  pll->SetVCOParameters( P, Q );
  pll->SetOutputSource( 0, okCPLL22150::ClkSrc_Div1ByN );
  pll->SetOutputEnable( 0, true );

  target->SetEepromPLL22150Configuration( *pll );

  delete pll;
}

