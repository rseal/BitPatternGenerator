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
module ClockDivider2( clk_in, div, clk_out, reset);

input  wire clk_in;
input  wire [15:0] div;
output reg clk_out;
input  wire reset;
reg [15:0]  counter;
//   reg 	       clk_buf;

/* -----\/----- EXCLUDED -----\/-----
`ifdef SPARTAN3
   //clock buffer
   BUFG cb (
      .I ( clk_buf ),
      .O ( clk_out )
   );
`else
   assign     clk_out = clk_buf;
`endif
-----/\----- EXCLUDED -----/\----- */

//   assign     clk_out = div == 1 ? clk_in : clk_buf;

always @ ( clk_in, reset, div )
begin
   if(!reset)
   begin
      counter <= div;
      clk_out <= clk_in;
   end
   else
   begin
      if(counter == 1)
      begin
         clk_out <= ~clk_out;
         counter <= div;
      end		  
      else
         counter <= counter - 1;
   end // else: !if(!reset)
end // always @ (posedge clk_in, negedge reset)
endmodule // ClkDivider
