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

module TopModule
(
   input  wire [7:0]  hi_in,
   output wire [1:0]  hi_out,
   inout  wire [15:0] hi_inout,
   input  wire        clk_std,
   input  wire        clk_drifted,
   input  wire        int_clk,
   input  wire        pps_1_ext,
   input  wire        pps_10_ext,
   input  wire        ext_trig_ext,
   output wire        porta_clk,
   output wire        portb_clk,
   output wire [15:0] porta,
   output wire [15:0] portb,		   
   output wire [7:0]  led,
   output wire        dac_en
);

//target interface
wire usb_clk;
wire [30:0] 		  ok1;
wire [16:0] 		  ok2;

//status wire-ins
wire [15:0] 		  control_in;

//status wire-outs
wire [15:0] 		  status_out1;
wire [15:0] 		  status_out2;

//pipe-ins
wire [15:0] 		  din1;
wire we1;

wire [15:0] 		  din2;   
wire we2;

wire active_buffer1;
wire active_buffer2;

wire ready1;
wire ready2;

wire load_complete1;
wire load_complete2;

wire switch1;
wire switch2;

wire start1;
wire start2;

wire stop1;
wire stop2;

wire active1;
wire active2;

wire reset1;
wire reset2;

//Master Control signals
wire [1:0]		  use_drifted;
wire [1:0] 		  sync;
wire preload1;
wire preload2;
wire clp;
wire use_dac;
wire use_clp;
wire use_cal;

wire clk;
wire clk_div1;
wire clk_div2;

//PORT A BUFFER SIGNALS
wire [15:0] 		  porta_buf;
wire [15:0] 		  portb_buf;

wire [12:0] 		  addr_db1a;
wire [11:0] 		  addr_db1b;
wire [15:0] 		  din_db1;
wire [31:0] 		  dout_db1;
wire we_db1;

wire [3:0] 		  addr_vb1a;
wire [3:0] 		  addr_vb1b;
wire [31:0] 		  din_vb1;
wire [31:0] 		  dout_vb1;
wire we_vb1;

//PORT B BUFFER SIGNALS
wire [12:0] 		  addr_db2a;
wire [11:0] 		  addr_db2b;
wire [15:0] 		  din_db2;
wire [31:0] 		  dout_db2;
wire we_db2;

wire [3:0] 		  addr_vb2a;
wire [3:0] 		  addr_vb2b;
wire [31:0] 		  din_vb2;
wire [31:0] 		  dout_vb2;
wire we_vb2;

assign porta_clk = clk_div1;
assign portb_clk = clk_div2;

//channel 15 of portA is hardwired to produce either phase or coded long pulse
// depending on use_clp bit
assign porta = use_clp ? {clp , porta_buf[14:0]} : porta_buf;
assign portb = portb_buf;

//32-bit linear feedback shift register for coded long pulse - port a
lfsr lfsr_a
(
   .clk(clk_div1),
   .sd_out(clp),
   .ce(porta_buf[14])
);

//signal routing for DAC module - port b
//DAC dac_b (
   //.clk(clk_div2),
   //.din(portb_buf),
   //.rst_in(reset2),
   //.use_dac(use_dac),
   //.dout(portb),
   //.rst_out(dac_en)
//);

//PORT A BUFFERS
dpram db1(
   .addra(addr_db1a),
   .addrb(addr_db1b),
   .clka(usb_clk),
   .clkb(clk_div1),
   .dina(din_db1),
   .doutb(dout_db1),
   .wea(we_db1)
);

ddpram vb1(
   .a(addr_vb1a),
   .clk(usb_clk),
   .d(din_vb1),
   .we(we_vb1),
   .dpra(addr_vb1b),
   .qdpo_clk(clk_div1),
   .qdpo(dout_vb1),
   .qspo()
);

//PORT B BUFFERS
dpram db2(
   .addra(addr_db2a),
   .addrb(addr_db2b),
   .clka(usb_clk),
   .clkb(clk_div2),
   .dina(din_db2),
   .doutb(dout_db2),
   .wea(we_db2)
);

ddpram vb2(
   .a(addr_vb2a),
   .clk(usb_clk),
   .d(din_vb2),
   .we(we_vb2),
   .dpra(addr_vb2b),
   .qdpo_clk(clk_div2),
   .qdpo(dout_vb2),
   .qspo()
);


//instantiating BUFGMUX for this case fails to route properly - this method works
assign clk = use_drifted == 2'b11 ? int_clk : use_drifted == 2'b10 ? clk_drifted : clk_std;


//INPUT CONTROL MODULE
InputControl ic1(
   .active_buffer(active_buffer1), 
   .clk(usb_clk),
   .we(we1),
   .din(din1),     
   .dwe(we_db1),
   .vwe(we_vb1),   
   .dout(din_db1),
   .vout(din_vb1), 
   .daddr(addr_db1a),
   .vaddr(addr_vb1a),
   .ready(ready1),
   .load_complete(load_complete1),
   .reset(reset1)
);

//INPUT CONTROL MODULE
InputControl ic2(
   .active_buffer(active_buffer2), 
   .clk(usb_clk),
   .we(we2),
   .din(din2),     
   .dwe(we_db2),
   .vwe(we_vb2),   
   .dout(din_db2),
   .vout(din_vb2), 
   .daddr(addr_db2a),
   .vaddr(addr_vb2a),
   .ready(ready2),
   .load_complete(load_complete2),
   .reset(reset2)
);

//OUTPUT CONTROL MODULE A
OutputControl oc1(
   .active_buffer(active_buffer1),
   .clk(clk),                
   .pps_1s(pps_1_ext),                   
   .pps_10s(pps_10_ext),
   .ext_trig(ext_trig_ext),
   .start(start1),                    
   .stop(stop1),
   .switch(switch1),
   .ready(ready1),                    
   .sync(sync),                      
   .din(dout_db1),                   
   .daddr(addr_db1b),                
   .vaddr(addr_vb1b),                
   .vin(dout_vb1),                    
   .out_port(porta_buf),
   .clk_out(clk_div1),                
   .preload(preload1),
   .reset(reset1),
   .active(active1)
);

//OUTPUT CONTROL MODULE B
OutputControl oc2(
   .active_buffer(active_buffer2), 
   .clk(clk),                 
   .pps_1s(pps_1_ext),            
   .pps_10s(pps_10_ext),
   .ext_trig(ext_trig_ext),
   .start(start2),            
   .stop(stop2),
   .switch(switch2),
   .ready(ready2),            
   .sync(sync),               
   .din(dout_db2),            
   .daddr(addr_db2b),         
   .vaddr(addr_vb2b),        
   .vin(dout_vb2),           
   .out_port(portb_buf),
   .clk_out(clk_div2),       
   .preload(preload2),
   .reset(reset2),
   .active(active2)
);


StatusSignals ss1(
   .clk(usb_clk),
   .we(we1),
   .ready(ready1),
   .active(active1),
   .load_complete(load_complete1),
   .preload(preload1),
   .active_buffer(active_buffer1),
   .reset(reset1),
   .status(status_out1)
);

StatusSignals ss2(
   .clk(usb_clk),
   .we(we2),
   .ready(ready2),
   .active(active2),
   .load_complete(load_complete2),
   .preload(preload2),
   .active_buffer(active_buffer2),
   .reset(reset2),
   .status(status_out2)
);

ControlSignal cs (
   .clk(usb_clk),
   .control(control_in),
   .reset1(reset1),
   .reset2(reset2),
   .start1(start1),
   .start2(start2),
   .stop1(stop1),
   .stop2(stop2),
   .switch1(switch1),
   .switch2(switch2),
   .sync(sync),
   .use_drifted(use_drifted),
   .use_dac(use_dac),
   .use_clp(use_clp),
   .use_cal(use_cal)
);


//Interface to Cypress USB chip and from there to the PC
okHostInterface okHI(
   .hi_in(hi_in),
   .hi_out(hi_out),
   .hi_inout(hi_inout),
   .ti_clk(usb_clk),
   .ok1(ok1),
   .ok2(ok2)
);

okWireIn wi (
   .ok1(ok1),
   .ok2(ok2),
   .ep_addr(8'h00),
   .ep_dataout(control_in)
);


//opal kelly wire out   
okWireOut wo1       (
   .ok1(ok1),
   .ok2(ok2),
   .ep_addr(8'h20),
   .ep_datain(status_out1)
);


//opal kelly wire out   
okWireOut wo2      (
   .ok1(ok1),
   .ok2(ok2),
   .ep_addr(8'h21),
   .ep_datain(status_out2)
);

//opal kelly pipe in   
okPipeIn pi1       (
   .ok1(ok1),
   .ok2(ok2),
   .ep_addr(8'h80),
   .ep_write(we1),
   .ep_dataout(din1)
);

//opal kelly pipe in   
okPipeIn pi2       (
   .ok1(ok1),
   .ok2(ok2),
   .ep_addr(8'h81),
   .ep_write(we2),
   .ep_dataout(din2)
);

//led heart beat
HeartBeat hb       (
   .clk(usb_clk),
   .led(led)
);
endmodule
