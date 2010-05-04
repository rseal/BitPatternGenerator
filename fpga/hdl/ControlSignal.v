// Copyright (c) 2010 Ryan Seal <rlseal -at- gmail.com>
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
`default_nettype none

module ControlSignal(
   clk,
   control,
   reset1,
   reset2,
   start1,
   start2,
   stop1,
   stop2,
   switch1,
   switch2,
   sync,
   use_drifted,
   use_dac,
   use_clp,
   use_cal
);

input wire clk;   
input wire [15:0] control;
output reg reset1,reset2;
output reg start1,start2;
output reg switch1, switch2;
output reg stop1,stop2;
output reg use_dac, use_clp, use_cal;
output reg [1:0] sync;
output reg [1:0] use_drifted;

always @ (posedge clk)
begin
   reset1      <= control[0];
   reset2      <= control[1];
   start1      <= control[2];
   start2      <= control[3];
   stop1       <= control[4];
   stop2       <= control[5];
   sync        <= control[7:6];
   use_drifted <= control[9:8];
   switch1     <= control[10];
   switch2     <= control[11];
   use_dac     <= control[12];
   use_clp     <= control[13];
   use_cal     <= control[14];
end

endmodule // ControlSignal
