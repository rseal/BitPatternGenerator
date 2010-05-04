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
module OutputControl
(
   active_buffer,    
   clk,         
   pps_1s,      
   pps_10s,
   ext_trig,
   start,       
   stop,
   ready,       
   sync,        
   din,        
   daddr,     
   vaddr,     
   vin,       
   out_port,
   clk_out,
   preload,
   reset,
   active,
   switch
);

//port declarations   
output reg  active_buffer;
input  wire clk;         
input  wire pps_1s; 
input  wire pps_10s;
input  wire ext_trig;
input  wire start;         
input  wire stop;
input  wire ready;         
input  wire [1:0]  sync;    
input  wire [31:0] din;    
output reg  [11:0] daddr;   
output reg  [3:0]  vaddr;   
input  wire [31:0] vin;    
output reg  [15:0] out_port;

output wire clk_out;
output reg  preload;
input  wire reset;
output reg active;
input  wire switch;

parameter IDLE   = 2'b00, ACTIVE = 2'b01, WAIT = 2'b10;

//internal declarations
reg [15:0] mode_count;
reg [15:0] div;             
reg [15:0] state_count;
reg [1:0]  state;
wire [11:0] start_address_active, start_address_next;
reg 	       synced_start;

//clk divider module
ClockDivider clkdiv
(
   .clk_in(clk),
   .div(div),
   .clk_out(clk_out),
   .reset(reset)
);

//data and variable starting addresses for curr
assign      start_address_next    = active_buffer ? 12'd0    : 12'd2048;
assign      start_address_active  = active_buffer ? 12'd2048 : 12'd0;

always @(negedge clk)
begin
   if(!reset) 
      synced_start <= 0;
   else
   begin
      case(sync)
         0: synced_start <= start;
         1: synced_start <= pps_1s & start;
         2: synced_start <= pps_10s & start;
         3: synced_start <= ext_trig & start;	       
         default: synced_start <= start;
      endcase
   end // else: !if(!reset)
end // always @ (negedge clk, negedge reset)

always @ (negedge clk_out)
   if(!reset)
   begin
      state <= IDLE;	
      div   <= 16'd1;
      active_buffer <= 1;
      active <= 0;	  
      vaddr <= 4'd0;
      daddr <= 12'd0;
      out_port <= 16'd0;
      preload <= 0;
      //switch_modes <= 0;	  
   end // if (!reset)
   else
   begin
      case(state)
         IDLE:
         begin
            if(ready & synced_start) begin
               state <= WAIT;
               div <= vin[31:16];
            end // if (ready & synced_start)		 
            else
            begin
               state         <= IDLE;
               active_buffer <= 1;
               vaddr         <= 4'd0;
               daddr         <= 12'd0;
               preload       <= 0;
               div           <= 1;
               active        <= 0;		      
            end // else: !if(ready & synced_start)
         end // case: IDLE

         ACTIVE:
         begin
            preload <= 0;	       
            if(state_count ==1) begin		    
               if(mode_count == 1) begin
                  if(switch == 1 || stop == 1) begin
                     //stop or enter wait state
                     state <= stop ? IDLE : WAIT;
                     //load new clock divider 1 cycle early
                     div <= vin[31:16];
                  end			 
                  else begin
                     //repeat mode
                     {state_count, out_port} <= din;
                     mode_count <= vin[15:0];
                  end
                  daddr <= daddr + 1;			 
               end 
               else begin
                  //decrement mode_count and load next state,count
                  mode_count <= mode_count -1;
                  daddr <= mode_count == 2 ? switch == 1 ?  
                     start_address_next : start_address_active : daddr +1;
                  {state_count, out_port}  <= din;
               end 
            end 
            else
               state_count <= state_count -1 ;	     
         end // case: ACTIVE
         WAIT:
         begin
            //added wait state to load div one cycle early
            //this corrects for a problem with the divide-by-n counter
            //updating on the master clock while this module updates on the div_clk
            state                   <= ACTIVE;		
            active_buffer           <= ~active_buffer;
            vaddr                   <= {3'd0,~active_buffer};			
            {state_count, out_port} <= din;
            {mode_count}            <= vin[15:0];
            daddr                   <= daddr + 1;
            // tell user to load the next mode and also clear switch bit
            preload                 <= 1;
            active                  <= 1;
            //switch_modes <= 0;		 
         end
      endcase 
   end // else: !if(!reset)
   endmodule // OutputControl
