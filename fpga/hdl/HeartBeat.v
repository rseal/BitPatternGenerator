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
module HeartBeat(
   input clk,
   output [7:0] led 
);

reg [15:0] count=0, count2=0, count3=0;
reg [7:0]  led_inv;
reg dir=0;

assign led = ~led_inv;

//heart beat leds   
always @ (posedge clk)
begin
   count <= count + 1;
   if(count == 16'hffff)
   begin
      count2 <= count2 + 1;
      count <=0;
   end

   if(count2 == 6'b011111)
   begin
      count2 <= 0;      
      led_inv <= (dir == 0) ? 8'b00000001 << count3 : 8'b10000000 >> count3;       
      count3 <= count3+1;       
   end

   if(led_inv == 8'b10000000) dir  <= 1;
   if(led_inv == 8'b00000001) dir  <= 0;
   if(count3 == 4'b1000) count3 <= 0;
end
endmodule
