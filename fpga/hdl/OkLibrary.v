//------------------------------------------------------------------------
// FrontPanel Library Module Declarations (Verilog)
//
// Copyright (c) 2005
// Opal Kelly Incorporated
//------------------------------------------------------------------------

module okHostInterface(hi_clk, hi_rdwr, hi_addr, hi_cs, hi_data, hi_irq, hi_busy, ti_clk, ti_control, ti_data);
input  wire        hi_clk;
input  wire        hi_rdwr;
input  wire        hi_cs;
input  wire [3:0]  hi_addr;
inout  wire [15:0] hi_data;
output wire        hi_irq;
output wire        hi_busy;
output wire        ti_clk;
output wire [12:0] ti_control;
inout  wire [15:0] ti_data;

wire [15:0] hi_datain;
wire [15:0] hi_dataout;
wire        hi_dir;

// Clock buffer for the Host Interface clock.
BUFG clkbuf(.I(hi_clk), .O(ti_clk));

// Instantiate bidirectional IOBUFs for the hi_data lines.
IOBUF iobuf0(.T(hi_dir),  .O(hi_datain[0]),  .I(hi_dataout[0]),  .IO(hi_data[0]));
IOBUF iobuf1(.T(hi_dir),  .O(hi_datain[1]),  .I(hi_dataout[1]),  .IO(hi_data[1]));
IOBUF iobuf2(.T(hi_dir),  .O(hi_datain[2]),  .I(hi_dataout[2]),  .IO(hi_data[2]));
IOBUF iobuf3(.T(hi_dir),  .O(hi_datain[3]),  .I(hi_dataout[3]),  .IO(hi_data[3]));
IOBUF iobuf4(.T(hi_dir),  .O(hi_datain[4]),  .I(hi_dataout[4]),  .IO(hi_data[4]));
IOBUF iobuf5(.T(hi_dir),  .O(hi_datain[5]),  .I(hi_dataout[5]),  .IO(hi_data[5]));
IOBUF iobuf6(.T(hi_dir),  .O(hi_datain[6]),  .I(hi_dataout[6]),  .IO(hi_data[6]));
IOBUF iobuf7(.T(hi_dir),  .O(hi_datain[7]),  .I(hi_dataout[7]),  .IO(hi_data[7]));
IOBUF iobuf8(.T(hi_dir),  .O(hi_datain[8]),  .I(hi_dataout[8]),  .IO(hi_data[8]));
IOBUF iobuf9(.T(hi_dir),  .O(hi_datain[9]),  .I(hi_dataout[9]),  .IO(hi_data[9]));
IOBUF iobuf10(.T(hi_dir), .O(hi_datain[10]), .I(hi_dataout[10]), .IO(hi_data[10]));
IOBUF iobuf11(.T(hi_dir), .O(hi_datain[11]), .I(hi_dataout[11]), .IO(hi_data[11]));
IOBUF iobuf12(.T(hi_dir), .O(hi_datain[12]), .I(hi_dataout[12]), .IO(hi_data[12]));
IOBUF iobuf13(.T(hi_dir), .O(hi_datain[13]), .I(hi_dataout[13]), .IO(hi_data[13]));
IOBUF iobuf14(.T(hi_dir), .O(hi_datain[14]), .I(hi_dataout[14]), .IO(hi_data[14]));
IOBUF iobuf15(.T(hi_dir), .O(hi_datain[15]), .I(hi_dataout[15]), .IO(hi_data[15]));

PULLUP p1(.O(ti_data[0]));
PULLUP p2(.O(ti_data[1]));
PULLUP p3(.O(ti_data[2]));
PULLUP p4(.O(ti_data[3]));
PULLUP p5(.O(ti_data[4]));
PULLUP p6(.O(ti_data[5]));
PULLUP p7(.O(ti_data[6]));
PULLUP p8(.O(ti_data[7]));
PULLUP p9(.O(ti_data[8]));
PULLUP p10(.O(ti_data[9]));
PULLUP p11(.O(ti_data[10]));
PULLUP p12(.O(ti_data[11]));
PULLUP p13(.O(ti_data[12]));
PULLUP p14(.O(ti_data[13]));
PULLUP p15(.O(ti_data[14]));
PULLUP p16(.O(ti_data[15]));

// Instantiate the core Host Interface.
okHostInterfaceCore hicore(.hi_clk(ti_clk), .hi_rdwr(hi_rdwr), .hi_cs(hi_cs),
.hi_irq(hi_irq), .hi_busy(hi_busy), .hi_addr(hi_addr),
.hi_dir(hi_dir), .hi_datain(hi_datain), .hi_dataout(hi_dataout),
.ti_control(ti_control), .ti_data(ti_data));

endmodule

module okHostInterfaceCore(hi_clk, hi_rdwr, hi_cs, hi_irq, hi_busy,
   hi_addr, hi_dir, hi_datain, hi_dataout,
   ti_control, ti_data);
input         hi_clk;
input         hi_rdwr;
input         hi_cs;
output        hi_irq;
output        hi_busy;
output        hi_dir;
input [3:0] 	 hi_addr;
input [15:0]  hi_datain;
output [15:0] hi_dataout;
output [12:0] ti_control;
inout [15:0]  ti_data;

// synthesis attribute box_type is black_box

endmodule

module okWireIn(ti_clk, ti_control, ti_data, ep_addr, ep_dataout);
input         ti_clk;
input [12:0]  ti_control;
input [15:0]  ti_data;
input [7:0] 	 ep_addr;
output [15:0] ep_dataout;

// synthesis attribute box_type is black_box

endmodule

module okWireOut(ti_clk, ti_control, ti_data, ep_addr, ep_datain);
input         ti_clk;
input [12:0]  ti_control;
output [15:0] ti_data;
input [7:0] 	 ep_addr;
input [15:0]  ep_datain;

// synthesis attribute box_type is black_box

endmodule

module okTriggerIn(ti_clk, ti_control, ti_data,
   ep_addr, ep_clk, ep_trigger);
input         ti_clk;
input [12:0]  ti_control;
input [15:0]  ti_data;
input [7:0] 	 ep_addr;
input         ep_clk;
output [15:0] ep_trigger;

// synthesis attribute box_type is black_box

endmodule

module okTriggerOut(ti_clk, ti_control, ti_data,
   ep_addr, ep_clk, ep_trigger);
input         ti_clk;
input [12:0]  ti_control;
output [15:0] ti_data;
input [7:0] 	 ep_addr;
input         ep_clk;
input [15:0]  ep_trigger;

// synthesis attribute box_type is black_box

endmodule


module okPipeIn(ti_clk, ti_control, ti_data, ep_addr, ep_write, ep_dataout);
input         ti_clk;
input [12:0]  ti_control;
input [15:0]  ti_data;
input [7:0] 	 ep_addr;
output        ep_write;
output [15:0] ep_dataout;

// synthesis attribute box_type is black_box

endmodule


module okPipeOut(ti_clk, ti_control, ti_data, ep_addr, ep_read, ep_datain);
input         ti_clk;
input [12:0]  ti_control;
output [15:0] ti_data;
input [7:0] 	 ep_addr;
output        ep_read;
input [15:0]  ep_datain;

// synthesis attribute box_type is black_box

endmodule


module okBufferedPipeIn(ti_clk, ti_control, ti_data,
   ep_addr, ep_clk, ep_reset, ep_read, ep_dataout,
   ep_full, ep_empty, ep_status);
input         ti_clk;
input [12:0]  ti_control;
input [15:0]  ti_data;
input [7:0] 	 ep_addr;
input         ep_clk;
input         ep_reset;
input         ep_read;
output [15:0] ep_dataout;
output        ep_full;
output        ep_empty;
output [3:0]  ep_status;

// synthesis attribute box_type is black_box

endmodule


module okBufferedPipeOut(ti_clk, ti_control, ti_data,
   ep_addr, ep_clk, ep_reset, ep_write, ep_datain,
   ep_full, ep_empty, ep_status);
input         ti_clk;
input [12:0]  ti_control;
output [15:0] ti_data;
input [7:0] 	 ep_addr;
input         ep_clk;
input         ep_reset;
input         ep_write;
input [15:0]  ep_datain;
output        ep_full;
output        ep_empty;
output [3:0]  ep_status;

// synthesis attribute box_type is black_box

endmodule
