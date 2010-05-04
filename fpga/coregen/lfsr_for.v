////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 1995-2007 Xilinx, Inc.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////
//   ____  ____
//  /   /\/   /
// /___/  \  /    Vendor: Xilinx
// \   \   \/     Version: J.30
//  \   \         Application: netgen
//  /   /         Filename: lfsr_for.v
// /___/   /\     Timestamp: Wed Jul 11 22:38:35 2007
// \   \  /  \ 
//  \___\/\___\
//             
// Command	: -intstyle ise -ecn formality /home/rseal/okRadar/test/Verilog/radarController/coregen/tmp/_cg/lfsr.ngd /home/rseal/okRadar/test/Verilog/radarController/coregen/tmp/_cg/lfsr_for.v 
// Device	: 3s400pq208-4
// Input file	: /home/rseal/okRadar/test/Verilog/radarController/coregen/tmp/_cg/lfsr.ngd
// Output file	: /home/rseal/okRadar/test/Verilog/radarController/coregen/tmp/_cg/lfsr_for.v
// # of Modules	: 1
// Design Name	: lfsr
// Xilinx        : /usr/local/xilinx91:/usr/local/xilinx91
//             
// Purpose:    
//     This verilog netlist is a verification model and uses library 
//     primitives which may not represent the true implementation of 
//     the device, however the netlist is functionally correct and 
//     should not be modified. This file cannot be synthesized and 
//     should only be used with supported equivalence checking tools.
//             
// Reference:  
//     Development System Reference Guide, Chapter 23
//     Synthesis and Simulation Design Guide, Chapter 6
//             
////////////////////////////////////////////////////////////////////////////////

`timescale 1 ns/1 ps

module lfsr (
  ce, sd_out, clk
);
  input ce;
  output sd_out;
  input clk;
  wire N0;
  wire N77;
  wire NlwRenamedSig_OI_sd_out;
  wire N249;
  wire N250;
  wire N251;
  wire N252;
  wire N253;
  wire N254;
  wire N255;
  wire N256;
  wire N257;
  wire N258;
  wire N259;
  wire N260;
  wire N261;
  wire N262;
  wire N263;
  wire N264;
  wire N265;
  wire N266;
  wire N267;
  wire N268;
  wire N269;
  wire N270;
  wire N271;
  wire N272;
  wire N273;
  wire N274;
  wire N275;
  wire N276;
  wire N277;
  wire N278;
  wire N279;
  wire NLW_VCC_O_UNCONNECTED;
  wire GND_0;
  assign
    sd_out = NlwRenamedSig_OI_sd_out;
  X_ONE VCC (
    .O(NLW_VCC_O_UNCONNECTED)
  );
  X_ZERO GND (
    .O(N0)
  );
  defparam BU23.INIT = 1'b1;
  X_FF BU23 (
    .SET(N0),
    .CE(ce),
    .CLK(clk),
    .I(N77),
    .O(N279),
    .RST(GND_0)
  );
  defparam BU31.INIT = 1'b1;
  X_FF BU31 (
    .SET(N0),
    .CE(ce),
    .CLK(clk),
    .I(N279),
    .O(N278),
    .RST(GND_0)
  );
  defparam BU39.INIT = 1'b1;
  X_FF BU39 (
    .SET(N0),
    .CE(ce),
    .CLK(clk),
    .I(N278),
    .O(N277),
    .RST(GND_0)
  );
  defparam BU47.INIT = 1'b1;
  X_FF BU47 (
    .SET(N0),
    .CE(ce),
    .CLK(clk),
    .I(N277),
    .O(N276),
    .RST(GND_0)
  );
  defparam BU55.INIT = 1'b1;
  X_FF BU55 (
    .SET(N0),
    .CE(ce),
    .CLK(clk),
    .I(N276),
    .O(N275),
    .RST(GND_0)
  );
  defparam BU63.INIT = 1'b1;
  X_FF BU63 (
    .SET(N0),
    .CE(ce),
    .CLK(clk),
    .I(N275),
    .O(N274),
    .RST(GND_0)
  );
  defparam BU71.INIT = 1'b1;
  X_FF BU71 (
    .SET(N0),
    .CE(ce),
    .CLK(clk),
    .I(N274),
    .O(N273),
    .RST(GND_0)
  );
  defparam BU79.INIT = 1'b1;
  X_FF BU79 (
    .SET(N0),
    .CE(ce),
    .CLK(clk),
    .I(N273),
    .O(N272),
    .RST(GND_0)
  );
  defparam BU87.INIT = 1'b1;
  X_FF BU87 (
    .SET(N0),
    .CE(ce),
    .CLK(clk),
    .I(N272),
    .O(N271),
    .RST(GND_0)
  );
  defparam BU95.INIT = 1'b1;
  X_FF BU95 (
    .SET(N0),
    .CE(ce),
    .CLK(clk),
    .I(N271),
    .O(N270),
    .RST(GND_0)
  );
  defparam BU103.INIT = 1'b1;
  X_FF BU103 (
    .SET(N0),
    .CE(ce),
    .CLK(clk),
    .I(N270),
    .O(N269),
    .RST(GND_0)
  );
  defparam BU111.INIT = 1'b1;
  X_FF BU111 (
    .SET(N0),
    .CE(ce),
    .CLK(clk),
    .I(N269),
    .O(N268),
    .RST(GND_0)
  );
  defparam BU119.INIT = 1'b1;
  X_FF BU119 (
    .SET(N0),
    .CE(ce),
    .CLK(clk),
    .I(N268),
    .O(N267),
    .RST(GND_0)
  );
  defparam BU127.INIT = 1'b1;
  X_FF BU127 (
    .SET(N0),
    .CE(ce),
    .CLK(clk),
    .I(N267),
    .O(N266),
    .RST(GND_0)
  );
  defparam BU135.INIT = 1'b1;
  X_FF BU135 (
    .SET(N0),
    .CE(ce),
    .CLK(clk),
    .I(N266),
    .O(N265),
    .RST(GND_0)
  );
  defparam BU143.INIT = 1'b1;
  X_FF BU143 (
    .SET(N0),
    .CE(ce),
    .CLK(clk),
    .I(N265),
    .O(N264),
    .RST(GND_0)
  );
  defparam BU151.INIT = 1'b1;
  X_FF BU151 (
    .SET(N0),
    .CE(ce),
    .CLK(clk),
    .I(N264),
    .O(N263),
    .RST(GND_0)
  );
  defparam BU159.INIT = 1'b1;
  X_FF BU159 (
    .SET(N0),
    .CE(ce),
    .CLK(clk),
    .I(N263),
    .O(N262),
    .RST(GND_0)
  );
  defparam BU167.INIT = 1'b1;
  X_FF BU167 (
    .SET(N0),
    .CE(ce),
    .CLK(clk),
    .I(N262),
    .O(N261),
    .RST(GND_0)
  );
  defparam BU175.INIT = 1'b1;
  X_FF BU175 (
    .SET(N0),
    .CE(ce),
    .CLK(clk),
    .I(N261),
    .O(N260),
    .RST(GND_0)
  );
  defparam BU183.INIT = 1'b1;
  X_FF BU183 (
    .SET(N0),
    .CE(ce),
    .CLK(clk),
    .I(N260),
    .O(N259),
    .RST(GND_0)
  );
  defparam BU191.INIT = 1'b1;
  X_FF BU191 (
    .SET(N0),
    .CE(ce),
    .CLK(clk),
    .I(N259),
    .O(N258),
    .RST(GND_0)
  );
  defparam BU199.INIT = 1'b1;
  X_FF BU199 (
    .SET(N0),
    .CE(ce),
    .CLK(clk),
    .I(N258),
    .O(N257),
    .RST(GND_0)
  );
  defparam BU207.INIT = 1'b1;
  X_FF BU207 (
    .SET(N0),
    .CE(ce),
    .CLK(clk),
    .I(N257),
    .O(N256),
    .RST(GND_0)
  );
  defparam BU215.INIT = 1'b1;
  X_FF BU215 (
    .SET(N0),
    .CE(ce),
    .CLK(clk),
    .I(N256),
    .O(N255),
    .RST(GND_0)
  );
  defparam BU223.INIT = 1'b1;
  X_FF BU223 (
    .SET(N0),
    .CE(ce),
    .CLK(clk),
    .I(N255),
    .O(N254),
    .RST(GND_0)
  );
  defparam BU231.INIT = 1'b1;
  X_FF BU231 (
    .SET(N0),
    .CE(ce),
    .CLK(clk),
    .I(N254),
    .O(N253),
    .RST(GND_0)
  );
  defparam BU239.INIT = 1'b1;
  X_FF BU239 (
    .SET(N0),
    .CE(ce),
    .CLK(clk),
    .I(N253),
    .O(N252),
    .RST(GND_0)
  );
  defparam BU247.INIT = 1'b1;
  X_FF BU247 (
    .SET(N0),
    .CE(ce),
    .CLK(clk),
    .I(N252),
    .O(N251),
    .RST(GND_0)
  );
  defparam BU255.INIT = 1'b1;
  X_FF BU255 (
    .SET(N0),
    .CE(ce),
    .CLK(clk),
    .I(N251),
    .O(N250),
    .RST(GND_0)
  );
  defparam BU263.INIT = 1'b1;
  X_FF BU263 (
    .SET(N0),
    .CE(ce),
    .CLK(clk),
    .I(N250),
    .O(N249),
    .RST(GND_0)
  );
  defparam BU271.INIT = 1'b1;
  X_FF BU271 (
    .SET(N0),
    .CE(ce),
    .CLK(clk),
    .I(N249),
    .O(NlwRenamedSig_OI_sd_out),
    .RST(GND_0)
  );
  defparam BU15.INIT = 16'h6996;
  X_LUT4 BU15 (
    .ADR0(NlwRenamedSig_OI_sd_out),
    .ADR1(N258),
    .ADR2(N278),
    .ADR3(N279),
    .O(N77)
  );
  X_ZERO NlwBlock_lfsr_GND (
    .O(GND_0)
  );
endmodule

