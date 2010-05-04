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
//`default_nettype none

////////////////////////////////////////////////////////////////////////////////
///
/// active_buffer: the buffer which is currently controlling the output port
/// clk: Input clk
/// we: write enable signal from the Opal Kelly pipeIn module
/// din: 16-bit data input from Opal Kelly pipeIn module
/// dwe: dual port ram write enable
/// vwe: distributed dual port ram enable
/// dout: data output to dual port ram
/// vout: variable output to distributed dual port ram
/// daddr: dual port ram data input address
/// vaddr:
/// ready:
/// load_complete:
/// reset:
////////////////////////////////////////////////////////////////////////////////

module InputControl(
   active_buffer,
   clk,
   we,
   din,
   dwe,
   vwe,
   dout,
   vout,
   daddr,
   vaddr,
   ready,
   load_complete,
   reset
);

input wire active_buffer;
input wire clk;
input wire we;
input wire [15:0] din;
output reg  dwe;
output reg  vwe;
output reg  [15:0] dout;
output reg  [31:0] vout;
output reg  [12:0] daddr;
output wire [3:0]  vaddr;
output reg ready;
output reg  load_complete;
input wire reset;

parameter IDLE = 2'b00, STATE = 2'b01, VAR = 2'b11;

reg [12:0]  address;
reg [1:0] state;
reg [2:0] vcount;
reg [15:0] clk_div;
//reg [15:0]  rotations;
wire [12:0] start_address, end_address;

//provide the proper indexing into buffers
//write to the inactive buffer while the active buffer is busy on the output ports
assign start_address = active_buffer ? 13'd0 : 13'd4096;
assign end_address   = active_buffer ? 13'd4095 : 13'd8191;
assign vaddr         = {3'b00,~active_buffer};

//write data to dual-port ram
//dual-port ram responds to posedge clks so negedge make sure of valid data on ports
always @ (negedge clk)
   if(!reset)
   begin
      clk_div   <= 16'd0;
      vout      <= 32'd0;       
      state     <= IDLE;
      address   <= 13'd0;
      daddr     <= 13'd0;
      dout      <= din;
      dwe       <= we;
      vwe       <= 4'd0;
      vcount    <= 3'd0;
      ready     <= 0;
      load_complete <=0;        
   end // if (reset)
   else
   begin
      case(state)
         IDLE:
         begin        
         address       <= start_address;
         daddr         <= start_address;
         dout          <= din;
         dwe           <= we;
         vwe           <= 0;
         vcount        <= 3'd0;
         vout          <= 32'd0;
         load_complete <= 0;         
         state         <= we ? STATE : IDLE;
      end
      STATE:
      begin
         if(address == end_address)
         begin
            daddr   <= start_address;         
            dout    <= 0;
            dwe     <= 0;

            if(we)
            begin
               clk_div <= din;          
               state   <= VAR;
            end
         end        
         else
         begin
            //only write when the pipeIn module asserts we
            if(we)
            begin
               address <= address+1;
               daddr   <= address+1;
               dout    <= din;
               dwe     <= we;
            end
         end
      end
      VAR:
      begin
         case (vcount)
            0: begin
               //only write when the pipIn module asserts we
               if(we) begin
                  //write data to vout
                  vwe    <=1;
                  vout   <= {clk_div, din};
                  vcount <=1;
               end
            end
            1: begin
               //wait state         
               load_complete <= 1;
               state         <= IDLE;
               ready         <= 1;
            end
            default: state   <= IDLE;
         endcase // case(vcount)
      end
   endcase // case(state)
end 
endmodule

