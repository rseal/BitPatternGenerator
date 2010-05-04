////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 1995-2007 Xilinx, Inc.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////
//   ____  ____
//  /   /\/   /
// /___/  \  /    Vendor: Xilinx
// \   \   \/     Version: J.30
//  \   \         Application: netgen
//  /   /         Filename: ddpram_for.v
// /___/   /\     Timestamp: Thu Jun 28 17:15:43 2007
// \   \  /  \ 
//  \___\/\___\
//             
// Command	: -intstyle ise -ecn formality /home/rseal/okRadar/test/Verilog/radarController/coregen/tmp/_cg/ddpram.ngd /home/rseal/okRadar/test/Verilog/radarController/coregen/tmp/_cg/ddpram_for.v 
// Device	: 3s400pq208-4
// Input file	: /home/rseal/okRadar/test/Verilog/radarController/coregen/tmp/_cg/ddpram.ngd
// Output file	: /home/rseal/okRadar/test/Verilog/radarController/coregen/tmp/_cg/ddpram_for.v
// # of Modules	: 1
// Design Name	: ddpram
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

module ddpram (
  clk, qdpo_clk, we, a, d, qspo, dpra, qdpo
);
  input clk;
  input qdpo_clk;
  input we;
  input [3 : 0] a;
  input [31 : 0] d;
  output [31 : 0] qspo;
  input [3 : 0] dpra;
  output [31 : 0] qdpo;
  wire N0;
  wire N1;
  wire \BU2/N2 ;
  wire VCC_0;
  wire GND_1;
  wire [3 : 0] a_2;
  wire [31 : 0] d_3;
  wire [3 : 0] dpra_4;
  wire [31 : 0] qspo_5;
  wire [31 : 0] qdpo_6;
  wire [31 : 0] \BU2/U0/gen_dp_ram.dpram_inst/dpo_int ;
  wire [31 : 0] \BU2/U0/gen_dp_ram.dpram_inst/spo_int ;
  wire [0 : 0] \BU2/dpo ;
  assign
    a_2[3] = a[3],
    a_2[2] = a[2],
    a_2[1] = a[1],
    a_2[0] = a[0],
    d_3[31] = d[31],
    d_3[30] = d[30],
    d_3[29] = d[29],
    d_3[28] = d[28],
    d_3[27] = d[27],
    d_3[26] = d[26],
    d_3[25] = d[25],
    d_3[24] = d[24],
    d_3[23] = d[23],
    d_3[22] = d[22],
    d_3[21] = d[21],
    d_3[20] = d[20],
    d_3[19] = d[19],
    d_3[18] = d[18],
    d_3[17] = d[17],
    d_3[16] = d[16],
    d_3[15] = d[15],
    d_3[14] = d[14],
    d_3[13] = d[13],
    d_3[12] = d[12],
    d_3[11] = d[11],
    d_3[10] = d[10],
    d_3[9] = d[9],
    d_3[8] = d[8],
    d_3[7] = d[7],
    d_3[6] = d[6],
    d_3[5] = d[5],
    d_3[4] = d[4],
    d_3[3] = d[3],
    d_3[2] = d[2],
    d_3[1] = d[1],
    d_3[0] = d[0],
    qspo[31] = qspo_5[31],
    qspo[30] = qspo_5[30],
    qspo[29] = qspo_5[29],
    qspo[28] = qspo_5[28],
    qspo[27] = qspo_5[27],
    qspo[26] = qspo_5[26],
    qspo[25] = qspo_5[25],
    qspo[24] = qspo_5[24],
    qspo[23] = qspo_5[23],
    qspo[22] = qspo_5[22],
    qspo[21] = qspo_5[21],
    qspo[20] = qspo_5[20],
    qspo[19] = qspo_5[19],
    qspo[18] = qspo_5[18],
    qspo[17] = qspo_5[17],
    qspo[16] = qspo_5[16],
    qspo[15] = qspo_5[15],
    qspo[14] = qspo_5[14],
    qspo[13] = qspo_5[13],
    qspo[12] = qspo_5[12],
    qspo[11] = qspo_5[11],
    qspo[10] = qspo_5[10],
    qspo[9] = qspo_5[9],
    qspo[8] = qspo_5[8],
    qspo[7] = qspo_5[7],
    qspo[6] = qspo_5[6],
    qspo[5] = qspo_5[5],
    qspo[4] = qspo_5[4],
    qspo[3] = qspo_5[3],
    qspo[2] = qspo_5[2],
    qspo[1] = qspo_5[1],
    qspo[0] = qspo_5[0],
    dpra_4[3] = dpra[3],
    dpra_4[2] = dpra[2],
    dpra_4[1] = dpra[1],
    dpra_4[0] = dpra[0],
    qdpo[31] = qdpo_6[31],
    qdpo[30] = qdpo_6[30],
    qdpo[29] = qdpo_6[29],
    qdpo[28] = qdpo_6[28],
    qdpo[27] = qdpo_6[27],
    qdpo[26] = qdpo_6[26],
    qdpo[25] = qdpo_6[25],
    qdpo[24] = qdpo_6[24],
    qdpo[23] = qdpo_6[23],
    qdpo[22] = qdpo_6[22],
    qdpo[21] = qdpo_6[21],
    qdpo[20] = qdpo_6[20],
    qdpo[19] = qdpo_6[19],
    qdpo[18] = qdpo_6[18],
    qdpo[17] = qdpo_6[17],
    qdpo[16] = qdpo_6[16],
    qdpo[15] = qdpo_6[15],
    qdpo[14] = qdpo_6[14],
    qdpo[13] = qdpo_6[13],
    qdpo[12] = qdpo_6[12],
    qdpo[11] = qdpo_6[11],
    qdpo[10] = qdpo_6[10],
    qdpo[9] = qdpo_6[9],
    qdpo[8] = qdpo_6[8],
    qdpo[7] = qdpo_6[7],
    qdpo[6] = qdpo_6[6],
    qdpo[5] = qdpo_6[5],
    qdpo[4] = qdpo_6[4],
    qdpo[3] = qdpo_6[3],
    qdpo[2] = qdpo_6[2],
    qdpo[1] = qdpo_6[1],
    qdpo[0] = qdpo_6[0];
  X_ONE VCC (
    .O(N1)
  );
  X_ZERO GND (
    .O(N0)
  );
  X_ONE \BU2/XST_VCC  (
    .O(\BU2/N2 )
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_0 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_0  (
    .CLK(qdpo_clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [0]),
    .O(qdpo_6[0]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_1 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_1  (
    .CLK(qdpo_clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [1]),
    .O(qdpo_6[1]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_2 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_2  (
    .CLK(qdpo_clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [2]),
    .O(qdpo_6[2]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_3 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_3  (
    .CLK(qdpo_clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [3]),
    .O(qdpo_6[3]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_4 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_4  (
    .CLK(qdpo_clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [4]),
    .O(qdpo_6[4]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_5 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_5  (
    .CLK(qdpo_clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [5]),
    .O(qdpo_6[5]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_6 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_6  (
    .CLK(qdpo_clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [6]),
    .O(qdpo_6[6]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_7 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_7  (
    .CLK(qdpo_clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [7]),
    .O(qdpo_6[7]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_8 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_8  (
    .CLK(qdpo_clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [8]),
    .O(qdpo_6[8]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_9 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_9  (
    .CLK(qdpo_clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [9]),
    .O(qdpo_6[9]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_10 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_10  (
    .CLK(qdpo_clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [10]),
    .O(qdpo_6[10]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_11 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_11  (
    .CLK(qdpo_clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [11]),
    .O(qdpo_6[11]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_12 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_12  (
    .CLK(qdpo_clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [12]),
    .O(qdpo_6[12]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_13 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_13  (
    .CLK(qdpo_clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [13]),
    .O(qdpo_6[13]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_14 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_14  (
    .CLK(qdpo_clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [14]),
    .O(qdpo_6[14]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_15 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_15  (
    .CLK(qdpo_clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [15]),
    .O(qdpo_6[15]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_16 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_16  (
    .CLK(qdpo_clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [16]),
    .O(qdpo_6[16]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_17 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_17  (
    .CLK(qdpo_clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [17]),
    .O(qdpo_6[17]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_18 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_18  (
    .CLK(qdpo_clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [18]),
    .O(qdpo_6[18]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_19 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_19  (
    .CLK(qdpo_clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [19]),
    .O(qdpo_6[19]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_20 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_20  (
    .CLK(qdpo_clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [20]),
    .O(qdpo_6[20]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_21 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_21  (
    .CLK(qdpo_clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [21]),
    .O(qdpo_6[21]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_22 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_22  (
    .CLK(qdpo_clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [22]),
    .O(qdpo_6[22]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_23 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_23  (
    .CLK(qdpo_clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [23]),
    .O(qdpo_6[23]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_24 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_24  (
    .CLK(qdpo_clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [24]),
    .O(qdpo_6[24]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_25 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_25  (
    .CLK(qdpo_clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [25]),
    .O(qdpo_6[25]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_26 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_26  (
    .CLK(qdpo_clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [26]),
    .O(qdpo_6[26]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_27 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_27  (
    .CLK(qdpo_clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [27]),
    .O(qdpo_6[27]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_28 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_28  (
    .CLK(qdpo_clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [28]),
    .O(qdpo_6[28]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_29 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_29  (
    .CLK(qdpo_clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [29]),
    .O(qdpo_6[29]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_30 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_30  (
    .CLK(qdpo_clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [30]),
    .O(qdpo_6[30]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_31 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qdpo_int_31  (
    .CLK(qdpo_clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [31]),
    .O(qdpo_6[31]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_0 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_0  (
    .CLK(clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [0]),
    .O(qspo_5[0]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_1 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_1  (
    .CLK(clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [1]),
    .O(qspo_5[1]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_2 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_2  (
    .CLK(clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [2]),
    .O(qspo_5[2]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_3 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_3  (
    .CLK(clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [3]),
    .O(qspo_5[3]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_4 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_4  (
    .CLK(clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [4]),
    .O(qspo_5[4]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_5 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_5  (
    .CLK(clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [5]),
    .O(qspo_5[5]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_6 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_6  (
    .CLK(clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [6]),
    .O(qspo_5[6]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_7 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_7  (
    .CLK(clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [7]),
    .O(qspo_5[7]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_8 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_8  (
    .CLK(clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [8]),
    .O(qspo_5[8]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_9 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_9  (
    .CLK(clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [9]),
    .O(qspo_5[9]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_10 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_10  (
    .CLK(clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [10]),
    .O(qspo_5[10]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_11 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_11  (
    .CLK(clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [11]),
    .O(qspo_5[11]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_12 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_12  (
    .CLK(clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [12]),
    .O(qspo_5[12]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_13 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_13  (
    .CLK(clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [13]),
    .O(qspo_5[13]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_14 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_14  (
    .CLK(clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [14]),
    .O(qspo_5[14]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_15 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_15  (
    .CLK(clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [15]),
    .O(qspo_5[15]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_16 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_16  (
    .CLK(clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [16]),
    .O(qspo_5[16]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_17 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_17  (
    .CLK(clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [17]),
    .O(qspo_5[17]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_18 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_18  (
    .CLK(clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [18]),
    .O(qspo_5[18]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_19 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_19  (
    .CLK(clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [19]),
    .O(qspo_5[19]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_20 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_20  (
    .CLK(clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [20]),
    .O(qspo_5[20]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_21 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_21  (
    .CLK(clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [21]),
    .O(qspo_5[21]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_22 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_22  (
    .CLK(clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [22]),
    .O(qspo_5[22]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_23 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_23  (
    .CLK(clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [23]),
    .O(qspo_5[23]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_24 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_24  (
    .CLK(clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [24]),
    .O(qspo_5[24]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_25 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_25  (
    .CLK(clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [25]),
    .O(qspo_5[25]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_26 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_26  (
    .CLK(clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [26]),
    .O(qspo_5[26]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_27 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_27  (
    .CLK(clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [27]),
    .O(qspo_5[27]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_28 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_28  (
    .CLK(clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [28]),
    .O(qspo_5[28]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_29 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_29  (
    .CLK(clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [29]),
    .O(qspo_5[29]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_30 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_30  (
    .CLK(clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [30]),
    .O(qspo_5[30]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_31 .INIT = 1'b0;
  X_FF \BU2/U0/gen_dp_ram.dpram_inst/qspo_int_31  (
    .CLK(clk),
    .I(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [31]),
    .O(qspo_5[31]),
    .CE(VCC_0),
    .SET(GND_1),
    .RST(GND_1)
  );
  X_ZERO \BU2/XST_GND  (
    .O(\BU2/dpo [0])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem31/X_RAMD16 .INIT = 16'h0000;
  X_RAMD16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem31/X_RAMD16  (
    .RADR0(dpra_4[0]),
    .RADR1(dpra_4[1]),
    .RADR2(dpra_4[2]),
    .RADR3(dpra_4[3]),
    .WADR0(a_2[0]),
    .WADR1(a_2[1]),
    .WADR2(a_2[2]),
    .WADR3(a_2[3]),
    .I(d_3[31]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [31])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem31/X_RAMS16 .INIT = 16'h0000;
  X_RAMS16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem31/X_RAMS16  (
    .ADR0(a_2[0]),
    .ADR1(a_2[1]),
    .ADR2(a_2[2]),
    .ADR3(a_2[3]),
    .I(d_3[31]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [31])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem30/X_RAMD16 .INIT = 16'h0000;
  X_RAMD16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem30/X_RAMD16  (
    .RADR0(dpra_4[0]),
    .RADR1(dpra_4[1]),
    .RADR2(dpra_4[2]),
    .RADR3(dpra_4[3]),
    .WADR0(a_2[0]),
    .WADR1(a_2[1]),
    .WADR2(a_2[2]),
    .WADR3(a_2[3]),
    .I(d_3[30]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [30])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem30/X_RAMS16 .INIT = 16'h0000;
  X_RAMS16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem30/X_RAMS16  (
    .ADR0(a_2[0]),
    .ADR1(a_2[1]),
    .ADR2(a_2[2]),
    .ADR3(a_2[3]),
    .I(d_3[30]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [30])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem29/X_RAMD16 .INIT = 16'h0000;
  X_RAMD16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem29/X_RAMD16  (
    .RADR0(dpra_4[0]),
    .RADR1(dpra_4[1]),
    .RADR2(dpra_4[2]),
    .RADR3(dpra_4[3]),
    .WADR0(a_2[0]),
    .WADR1(a_2[1]),
    .WADR2(a_2[2]),
    .WADR3(a_2[3]),
    .I(d_3[29]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [29])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem29/X_RAMS16 .INIT = 16'h0000;
  X_RAMS16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem29/X_RAMS16  (
    .ADR0(a_2[0]),
    .ADR1(a_2[1]),
    .ADR2(a_2[2]),
    .ADR3(a_2[3]),
    .I(d_3[29]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [29])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem28/X_RAMD16 .INIT = 16'h0000;
  X_RAMD16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem28/X_RAMD16  (
    .RADR0(dpra_4[0]),
    .RADR1(dpra_4[1]),
    .RADR2(dpra_4[2]),
    .RADR3(dpra_4[3]),
    .WADR0(a_2[0]),
    .WADR1(a_2[1]),
    .WADR2(a_2[2]),
    .WADR3(a_2[3]),
    .I(d_3[28]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [28])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem28/X_RAMS16 .INIT = 16'h0000;
  X_RAMS16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem28/X_RAMS16  (
    .ADR0(a_2[0]),
    .ADR1(a_2[1]),
    .ADR2(a_2[2]),
    .ADR3(a_2[3]),
    .I(d_3[28]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [28])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem27/X_RAMD16 .INIT = 16'h0000;
  X_RAMD16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem27/X_RAMD16  (
    .RADR0(dpra_4[0]),
    .RADR1(dpra_4[1]),
    .RADR2(dpra_4[2]),
    .RADR3(dpra_4[3]),
    .WADR0(a_2[0]),
    .WADR1(a_2[1]),
    .WADR2(a_2[2]),
    .WADR3(a_2[3]),
    .I(d_3[27]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [27])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem27/X_RAMS16 .INIT = 16'h0000;
  X_RAMS16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem27/X_RAMS16  (
    .ADR0(a_2[0]),
    .ADR1(a_2[1]),
    .ADR2(a_2[2]),
    .ADR3(a_2[3]),
    .I(d_3[27]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [27])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem26/X_RAMD16 .INIT = 16'h0000;
  X_RAMD16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem26/X_RAMD16  (
    .RADR0(dpra_4[0]),
    .RADR1(dpra_4[1]),
    .RADR2(dpra_4[2]),
    .RADR3(dpra_4[3]),
    .WADR0(a_2[0]),
    .WADR1(a_2[1]),
    .WADR2(a_2[2]),
    .WADR3(a_2[3]),
    .I(d_3[26]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [26])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem26/X_RAMS16 .INIT = 16'h0000;
  X_RAMS16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem26/X_RAMS16  (
    .ADR0(a_2[0]),
    .ADR1(a_2[1]),
    .ADR2(a_2[2]),
    .ADR3(a_2[3]),
    .I(d_3[26]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [26])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem25/X_RAMD16 .INIT = 16'h0000;
  X_RAMD16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem25/X_RAMD16  (
    .RADR0(dpra_4[0]),
    .RADR1(dpra_4[1]),
    .RADR2(dpra_4[2]),
    .RADR3(dpra_4[3]),
    .WADR0(a_2[0]),
    .WADR1(a_2[1]),
    .WADR2(a_2[2]),
    .WADR3(a_2[3]),
    .I(d_3[25]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [25])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem25/X_RAMS16 .INIT = 16'h0000;
  X_RAMS16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem25/X_RAMS16  (
    .ADR0(a_2[0]),
    .ADR1(a_2[1]),
    .ADR2(a_2[2]),
    .ADR3(a_2[3]),
    .I(d_3[25]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [25])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem24/X_RAMD16 .INIT = 16'h0000;
  X_RAMD16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem24/X_RAMD16  (
    .RADR0(dpra_4[0]),
    .RADR1(dpra_4[1]),
    .RADR2(dpra_4[2]),
    .RADR3(dpra_4[3]),
    .WADR0(a_2[0]),
    .WADR1(a_2[1]),
    .WADR2(a_2[2]),
    .WADR3(a_2[3]),
    .I(d_3[24]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [24])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem24/X_RAMS16 .INIT = 16'h0000;
  X_RAMS16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem24/X_RAMS16  (
    .ADR0(a_2[0]),
    .ADR1(a_2[1]),
    .ADR2(a_2[2]),
    .ADR3(a_2[3]),
    .I(d_3[24]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [24])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem23/X_RAMD16 .INIT = 16'h0000;
  X_RAMD16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem23/X_RAMD16  (
    .RADR0(dpra_4[0]),
    .RADR1(dpra_4[1]),
    .RADR2(dpra_4[2]),
    .RADR3(dpra_4[3]),
    .WADR0(a_2[0]),
    .WADR1(a_2[1]),
    .WADR2(a_2[2]),
    .WADR3(a_2[3]),
    .I(d_3[23]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [23])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem23/X_RAMS16 .INIT = 16'h0000;
  X_RAMS16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem23/X_RAMS16  (
    .ADR0(a_2[0]),
    .ADR1(a_2[1]),
    .ADR2(a_2[2]),
    .ADR3(a_2[3]),
    .I(d_3[23]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [23])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem22/X_RAMD16 .INIT = 16'h0000;
  X_RAMD16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem22/X_RAMD16  (
    .RADR0(dpra_4[0]),
    .RADR1(dpra_4[1]),
    .RADR2(dpra_4[2]),
    .RADR3(dpra_4[3]),
    .WADR0(a_2[0]),
    .WADR1(a_2[1]),
    .WADR2(a_2[2]),
    .WADR3(a_2[3]),
    .I(d_3[22]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [22])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem22/X_RAMS16 .INIT = 16'h0000;
  X_RAMS16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem22/X_RAMS16  (
    .ADR0(a_2[0]),
    .ADR1(a_2[1]),
    .ADR2(a_2[2]),
    .ADR3(a_2[3]),
    .I(d_3[22]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [22])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem21/X_RAMD16 .INIT = 16'h0000;
  X_RAMD16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem21/X_RAMD16  (
    .RADR0(dpra_4[0]),
    .RADR1(dpra_4[1]),
    .RADR2(dpra_4[2]),
    .RADR3(dpra_4[3]),
    .WADR0(a_2[0]),
    .WADR1(a_2[1]),
    .WADR2(a_2[2]),
    .WADR3(a_2[3]),
    .I(d_3[21]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [21])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem21/X_RAMS16 .INIT = 16'h0000;
  X_RAMS16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem21/X_RAMS16  (
    .ADR0(a_2[0]),
    .ADR1(a_2[1]),
    .ADR2(a_2[2]),
    .ADR3(a_2[3]),
    .I(d_3[21]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [21])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem20/X_RAMD16 .INIT = 16'h0000;
  X_RAMD16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem20/X_RAMD16  (
    .RADR0(dpra_4[0]),
    .RADR1(dpra_4[1]),
    .RADR2(dpra_4[2]),
    .RADR3(dpra_4[3]),
    .WADR0(a_2[0]),
    .WADR1(a_2[1]),
    .WADR2(a_2[2]),
    .WADR3(a_2[3]),
    .I(d_3[20]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [20])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem20/X_RAMS16 .INIT = 16'h0000;
  X_RAMS16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem20/X_RAMS16  (
    .ADR0(a_2[0]),
    .ADR1(a_2[1]),
    .ADR2(a_2[2]),
    .ADR3(a_2[3]),
    .I(d_3[20]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [20])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem19/X_RAMD16 .INIT = 16'h0000;
  X_RAMD16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem19/X_RAMD16  (
    .RADR0(dpra_4[0]),
    .RADR1(dpra_4[1]),
    .RADR2(dpra_4[2]),
    .RADR3(dpra_4[3]),
    .WADR0(a_2[0]),
    .WADR1(a_2[1]),
    .WADR2(a_2[2]),
    .WADR3(a_2[3]),
    .I(d_3[19]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [19])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem19/X_RAMS16 .INIT = 16'h0000;
  X_RAMS16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem19/X_RAMS16  (
    .ADR0(a_2[0]),
    .ADR1(a_2[1]),
    .ADR2(a_2[2]),
    .ADR3(a_2[3]),
    .I(d_3[19]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [19])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem18/X_RAMD16 .INIT = 16'h0000;
  X_RAMD16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem18/X_RAMD16  (
    .RADR0(dpra_4[0]),
    .RADR1(dpra_4[1]),
    .RADR2(dpra_4[2]),
    .RADR3(dpra_4[3]),
    .WADR0(a_2[0]),
    .WADR1(a_2[1]),
    .WADR2(a_2[2]),
    .WADR3(a_2[3]),
    .I(d_3[18]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [18])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem18/X_RAMS16 .INIT = 16'h0000;
  X_RAMS16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem18/X_RAMS16  (
    .ADR0(a_2[0]),
    .ADR1(a_2[1]),
    .ADR2(a_2[2]),
    .ADR3(a_2[3]),
    .I(d_3[18]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [18])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem17/X_RAMD16 .INIT = 16'h0000;
  X_RAMD16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem17/X_RAMD16  (
    .RADR0(dpra_4[0]),
    .RADR1(dpra_4[1]),
    .RADR2(dpra_4[2]),
    .RADR3(dpra_4[3]),
    .WADR0(a_2[0]),
    .WADR1(a_2[1]),
    .WADR2(a_2[2]),
    .WADR3(a_2[3]),
    .I(d_3[17]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [17])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem17/X_RAMS16 .INIT = 16'h0000;
  X_RAMS16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem17/X_RAMS16  (
    .ADR0(a_2[0]),
    .ADR1(a_2[1]),
    .ADR2(a_2[2]),
    .ADR3(a_2[3]),
    .I(d_3[17]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [17])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem16/X_RAMD16 .INIT = 16'h0000;
  X_RAMD16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem16/X_RAMD16  (
    .RADR0(dpra_4[0]),
    .RADR1(dpra_4[1]),
    .RADR2(dpra_4[2]),
    .RADR3(dpra_4[3]),
    .WADR0(a_2[0]),
    .WADR1(a_2[1]),
    .WADR2(a_2[2]),
    .WADR3(a_2[3]),
    .I(d_3[16]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [16])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem16/X_RAMS16 .INIT = 16'h0000;
  X_RAMS16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem16/X_RAMS16  (
    .ADR0(a_2[0]),
    .ADR1(a_2[1]),
    .ADR2(a_2[2]),
    .ADR3(a_2[3]),
    .I(d_3[16]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [16])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem15/X_RAMD16 .INIT = 16'h0000;
  X_RAMD16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem15/X_RAMD16  (
    .RADR0(dpra_4[0]),
    .RADR1(dpra_4[1]),
    .RADR2(dpra_4[2]),
    .RADR3(dpra_4[3]),
    .WADR0(a_2[0]),
    .WADR1(a_2[1]),
    .WADR2(a_2[2]),
    .WADR3(a_2[3]),
    .I(d_3[15]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [15])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem15/X_RAMS16 .INIT = 16'h0000;
  X_RAMS16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem15/X_RAMS16  (
    .ADR0(a_2[0]),
    .ADR1(a_2[1]),
    .ADR2(a_2[2]),
    .ADR3(a_2[3]),
    .I(d_3[15]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [15])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem14/X_RAMD16 .INIT = 16'h0000;
  X_RAMD16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem14/X_RAMD16  (
    .RADR0(dpra_4[0]),
    .RADR1(dpra_4[1]),
    .RADR2(dpra_4[2]),
    .RADR3(dpra_4[3]),
    .WADR0(a_2[0]),
    .WADR1(a_2[1]),
    .WADR2(a_2[2]),
    .WADR3(a_2[3]),
    .I(d_3[14]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [14])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem14/X_RAMS16 .INIT = 16'h0000;
  X_RAMS16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem14/X_RAMS16  (
    .ADR0(a_2[0]),
    .ADR1(a_2[1]),
    .ADR2(a_2[2]),
    .ADR3(a_2[3]),
    .I(d_3[14]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [14])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem13/X_RAMD16 .INIT = 16'h0000;
  X_RAMD16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem13/X_RAMD16  (
    .RADR0(dpra_4[0]),
    .RADR1(dpra_4[1]),
    .RADR2(dpra_4[2]),
    .RADR3(dpra_4[3]),
    .WADR0(a_2[0]),
    .WADR1(a_2[1]),
    .WADR2(a_2[2]),
    .WADR3(a_2[3]),
    .I(d_3[13]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [13])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem13/X_RAMS16 .INIT = 16'h0000;
  X_RAMS16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem13/X_RAMS16  (
    .ADR0(a_2[0]),
    .ADR1(a_2[1]),
    .ADR2(a_2[2]),
    .ADR3(a_2[3]),
    .I(d_3[13]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [13])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem12/X_RAMD16 .INIT = 16'h0000;
  X_RAMD16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem12/X_RAMD16  (
    .RADR0(dpra_4[0]),
    .RADR1(dpra_4[1]),
    .RADR2(dpra_4[2]),
    .RADR3(dpra_4[3]),
    .WADR0(a_2[0]),
    .WADR1(a_2[1]),
    .WADR2(a_2[2]),
    .WADR3(a_2[3]),
    .I(d_3[12]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [12])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem12/X_RAMS16 .INIT = 16'h0000;
  X_RAMS16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem12/X_RAMS16  (
    .ADR0(a_2[0]),
    .ADR1(a_2[1]),
    .ADR2(a_2[2]),
    .ADR3(a_2[3]),
    .I(d_3[12]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [12])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem11/X_RAMD16 .INIT = 16'h0000;
  X_RAMD16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem11/X_RAMD16  (
    .RADR0(dpra_4[0]),
    .RADR1(dpra_4[1]),
    .RADR2(dpra_4[2]),
    .RADR3(dpra_4[3]),
    .WADR0(a_2[0]),
    .WADR1(a_2[1]),
    .WADR2(a_2[2]),
    .WADR3(a_2[3]),
    .I(d_3[11]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [11])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem11/X_RAMS16 .INIT = 16'h0000;
  X_RAMS16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem11/X_RAMS16  (
    .ADR0(a_2[0]),
    .ADR1(a_2[1]),
    .ADR2(a_2[2]),
    .ADR3(a_2[3]),
    .I(d_3[11]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [11])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem10/X_RAMD16 .INIT = 16'h0000;
  X_RAMD16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem10/X_RAMD16  (
    .RADR0(dpra_4[0]),
    .RADR1(dpra_4[1]),
    .RADR2(dpra_4[2]),
    .RADR3(dpra_4[3]),
    .WADR0(a_2[0]),
    .WADR1(a_2[1]),
    .WADR2(a_2[2]),
    .WADR3(a_2[3]),
    .I(d_3[10]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [10])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem10/X_RAMS16 .INIT = 16'h0000;
  X_RAMS16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem10/X_RAMS16  (
    .ADR0(a_2[0]),
    .ADR1(a_2[1]),
    .ADR2(a_2[2]),
    .ADR3(a_2[3]),
    .I(d_3[10]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [10])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem9/X_RAMD16 .INIT = 16'h0000;
  X_RAMD16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem9/X_RAMD16  (
    .RADR0(dpra_4[0]),
    .RADR1(dpra_4[1]),
    .RADR2(dpra_4[2]),
    .RADR3(dpra_4[3]),
    .WADR0(a_2[0]),
    .WADR1(a_2[1]),
    .WADR2(a_2[2]),
    .WADR3(a_2[3]),
    .I(d_3[9]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [9])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem9/X_RAMS16 .INIT = 16'h0000;
  X_RAMS16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem9/X_RAMS16  (
    .ADR0(a_2[0]),
    .ADR1(a_2[1]),
    .ADR2(a_2[2]),
    .ADR3(a_2[3]),
    .I(d_3[9]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [9])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem8/X_RAMD16 .INIT = 16'h0000;
  X_RAMD16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem8/X_RAMD16  (
    .RADR0(dpra_4[0]),
    .RADR1(dpra_4[1]),
    .RADR2(dpra_4[2]),
    .RADR3(dpra_4[3]),
    .WADR0(a_2[0]),
    .WADR1(a_2[1]),
    .WADR2(a_2[2]),
    .WADR3(a_2[3]),
    .I(d_3[8]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [8])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem8/X_RAMS16 .INIT = 16'h0000;
  X_RAMS16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem8/X_RAMS16  (
    .ADR0(a_2[0]),
    .ADR1(a_2[1]),
    .ADR2(a_2[2]),
    .ADR3(a_2[3]),
    .I(d_3[8]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [8])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem7/X_RAMD16 .INIT = 16'h0000;
  X_RAMD16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem7/X_RAMD16  (
    .RADR0(dpra_4[0]),
    .RADR1(dpra_4[1]),
    .RADR2(dpra_4[2]),
    .RADR3(dpra_4[3]),
    .WADR0(a_2[0]),
    .WADR1(a_2[1]),
    .WADR2(a_2[2]),
    .WADR3(a_2[3]),
    .I(d_3[7]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [7])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem7/X_RAMS16 .INIT = 16'h0000;
  X_RAMS16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem7/X_RAMS16  (
    .ADR0(a_2[0]),
    .ADR1(a_2[1]),
    .ADR2(a_2[2]),
    .ADR3(a_2[3]),
    .I(d_3[7]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [7])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem6/X_RAMD16 .INIT = 16'h0000;
  X_RAMD16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem6/X_RAMD16  (
    .RADR0(dpra_4[0]),
    .RADR1(dpra_4[1]),
    .RADR2(dpra_4[2]),
    .RADR3(dpra_4[3]),
    .WADR0(a_2[0]),
    .WADR1(a_2[1]),
    .WADR2(a_2[2]),
    .WADR3(a_2[3]),
    .I(d_3[6]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [6])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem6/X_RAMS16 .INIT = 16'h0000;
  X_RAMS16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem6/X_RAMS16  (
    .ADR0(a_2[0]),
    .ADR1(a_2[1]),
    .ADR2(a_2[2]),
    .ADR3(a_2[3]),
    .I(d_3[6]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [6])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem5/X_RAMD16 .INIT = 16'h0000;
  X_RAMD16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem5/X_RAMD16  (
    .RADR0(dpra_4[0]),
    .RADR1(dpra_4[1]),
    .RADR2(dpra_4[2]),
    .RADR3(dpra_4[3]),
    .WADR0(a_2[0]),
    .WADR1(a_2[1]),
    .WADR2(a_2[2]),
    .WADR3(a_2[3]),
    .I(d_3[5]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [5])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem5/X_RAMS16 .INIT = 16'h0000;
  X_RAMS16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem5/X_RAMS16  (
    .ADR0(a_2[0]),
    .ADR1(a_2[1]),
    .ADR2(a_2[2]),
    .ADR3(a_2[3]),
    .I(d_3[5]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [5])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem4/X_RAMD16 .INIT = 16'h0000;
  X_RAMD16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem4/X_RAMD16  (
    .RADR0(dpra_4[0]),
    .RADR1(dpra_4[1]),
    .RADR2(dpra_4[2]),
    .RADR3(dpra_4[3]),
    .WADR0(a_2[0]),
    .WADR1(a_2[1]),
    .WADR2(a_2[2]),
    .WADR3(a_2[3]),
    .I(d_3[4]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [4])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem4/X_RAMS16 .INIT = 16'h0000;
  X_RAMS16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem4/X_RAMS16  (
    .ADR0(a_2[0]),
    .ADR1(a_2[1]),
    .ADR2(a_2[2]),
    .ADR3(a_2[3]),
    .I(d_3[4]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [4])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem3/X_RAMD16 .INIT = 16'h0000;
  X_RAMD16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem3/X_RAMD16  (
    .RADR0(dpra_4[0]),
    .RADR1(dpra_4[1]),
    .RADR2(dpra_4[2]),
    .RADR3(dpra_4[3]),
    .WADR0(a_2[0]),
    .WADR1(a_2[1]),
    .WADR2(a_2[2]),
    .WADR3(a_2[3]),
    .I(d_3[3]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [3])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem3/X_RAMS16 .INIT = 16'h0000;
  X_RAMS16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem3/X_RAMS16  (
    .ADR0(a_2[0]),
    .ADR1(a_2[1]),
    .ADR2(a_2[2]),
    .ADR3(a_2[3]),
    .I(d_3[3]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [3])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem2/X_RAMD16 .INIT = 16'h0000;
  X_RAMD16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem2/X_RAMD16  (
    .RADR0(dpra_4[0]),
    .RADR1(dpra_4[1]),
    .RADR2(dpra_4[2]),
    .RADR3(dpra_4[3]),
    .WADR0(a_2[0]),
    .WADR1(a_2[1]),
    .WADR2(a_2[2]),
    .WADR3(a_2[3]),
    .I(d_3[2]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [2])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem2/X_RAMS16 .INIT = 16'h0000;
  X_RAMS16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem2/X_RAMS16  (
    .ADR0(a_2[0]),
    .ADR1(a_2[1]),
    .ADR2(a_2[2]),
    .ADR3(a_2[3]),
    .I(d_3[2]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [2])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem1/X_RAMD16 .INIT = 16'h0000;
  X_RAMD16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem1/X_RAMD16  (
    .RADR0(dpra_4[0]),
    .RADR1(dpra_4[1]),
    .RADR2(dpra_4[2]),
    .RADR3(dpra_4[3]),
    .WADR0(a_2[0]),
    .WADR1(a_2[1]),
    .WADR2(a_2[2]),
    .WADR3(a_2[3]),
    .I(d_3[1]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [1])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem1/X_RAMS16 .INIT = 16'h0000;
  X_RAMS16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem1/X_RAMS16  (
    .ADR0(a_2[0]),
    .ADR1(a_2[1]),
    .ADR2(a_2[2]),
    .ADR3(a_2[3]),
    .I(d_3[1]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [1])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem/X_RAMD16 .INIT = 16'h0000;
  X_RAMD16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem/X_RAMD16  (
    .RADR0(dpra_4[0]),
    .RADR1(dpra_4[1]),
    .RADR2(dpra_4[2]),
    .RADR3(dpra_4[3]),
    .WADR0(a_2[0]),
    .WADR1(a_2[1]),
    .WADR2(a_2[2]),
    .WADR3(a_2[3]),
    .I(d_3[0]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/dpo_int [0])
  );
  defparam \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem/X_RAMS16 .INIT = 16'h0000;
  X_RAMS16 \BU2/U0/gen_dp_ram.dpram_inst/inst_Mram_mem/X_RAMS16  (
    .ADR0(a_2[0]),
    .ADR1(a_2[1]),
    .ADR2(a_2[2]),
    .ADR3(a_2[3]),
    .I(d_3[0]),
    .CLK(clk),
    .WE(we),
    .O(\BU2/U0/gen_dp_ram.dpram_inst/spo_int [0])
  );
  X_ONE NlwBlock_ddpram_VCC (
    .O(VCC_0)
  );
  X_ZERO NlwBlock_ddpram_GND (
    .O(GND_1)
  );
endmodule

