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
module DAC 
(
   clk,
   din,
   rst_in,
   use_dac,
   dout,
   rst_out
);

input wire clk;
input wire [15:0] din;
input wire rst_in;
input wire use_dac;
output wire [15:0] dout;
output wire rst_out;

reg select;
reg toggle;

//DAC reset is active high
assign rst_out = ~rst_in;
assign dout = use_dac ? { 3'd0, clk, clk, select, din[9:0]} : din;

always @ (negedge clk)
begin
   if(!rst_in)
      toggle <= 0;
   else
   begin
      select <= toggle ? 1 : 0;
      toggle <= ~toggle;
   end
end // always @ (negedge clk)
endmodule // DAC
