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

module StatusSignals
(
   clk,
   we,
   ready,
   active,
   load_complete,
   preload,
   active_buffer,
   reset,
   status
);

input wire clk;
input wire we;   
input wire ready;
input wire active;
input wire load_complete;
input wire preload;
input wire active_buffer;
input wire reset;
output reg [15:0] status;

reg 	  preload_int;

always @ (posedge clk)
begin
   preload_int <= preload && !we ? 1 : 0;
   status <= 
      {
      10'd0, 
      reset,
      ready, 
      active, 
      load_complete, 
      preload_int, 
      active_buffer
      };
   end
   endmodule // StatusSignals



