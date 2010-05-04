/*******************************************************************************
*     This file is owned and controlled by Xilinx and must be used             *
*     solely for design, simulation, implementation and creation of            *
*     design files limited to Xilinx devices or technologies. Use              *
*     with non-Xilinx devices or technologies is expressly prohibited          *
*     and immediately terminates your license.                                 *
*                                                                              *
*     XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS"            *
*     SOLELY FOR USE IN DEVELOPING PROGRAMS AND SOLUTIONS FOR                  *
*     XILINX DEVICES.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION          *
*     AS ONE POSSIBLE IMPLEMENTATION OF THIS FEATURE, APPLICATION              *
*     OR STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS                *
*     IMPLEMENTATION IS FREE FROM ANY CLAIMS OF INFRINGEMENT,                  *
*     AND YOU ARE RESPONSIBLE FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE         *
*     FOR YOUR IMPLEMENTATION.  XILINX EXPRESSLY DISCLAIMS ANY                 *
*     WARRANTY WHATSOEVER WITH RESPECT TO THE ADEQUACY OF THE                  *
*     IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OR           *
*     REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE FROM CLAIMS OF          *
*     INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS          *
*     FOR A PARTICULAR PURPOSE.                                                *
*                                                                              *
*     Xilinx products are not intended for use in life support                 *
*     appliances, devices, or systems. Use in such applications are            *
*     expressly prohibited.                                                    *
*                                                                              *
*     (c) Copyright 1995-2006 Xilinx, Inc.                                     *
*     All rights reserved.                                                     *
*******************************************************************************/
// The synthesis directives "translate_off/translate_on" specified below are
// supported by Xilinx, Mentor Graphics and Synplicity synthesis
// tools. Ensure they are correct for your synthesis tool(s).

// You must compile the wrapper file lfsr.v when simulating
// the core, lfsr. When compiling the wrapper file, be sure to
// reference the XilinxCoreLib Verilog simulation library. For detailed
// instructions, please refer to the "CORE Generator Help".

`timescale 1ns/1ps

module lfsr(
	clk,
	sd_out,
	ce);


input clk;
output sd_out;
input ce;

// synthesis translate_off

      LFSR_V3_0 #(
		.C_AINIT_VAL("11111111111111111111111111111111"),
		.C_ENABLE_RLOCS(0),
		.C_GATE(0),
		.C_HAS_AINIT(0),
		.C_HAS_CE(1),
		.C_HAS_DATA_VALID(0),
		.C_HAS_LOAD(0),
		.C_HAS_LOAD_TAPS(0),
		.C_HAS_NEW_SEED(0),
		.C_HAS_PD_IN(0),
		.C_HAS_PD_OUT(0),
		.C_HAS_SD_IN(0),
		.C_HAS_SD_OUT(1),
		.C_HAS_SINIT(0),
		.C_HAS_TAPS_IN(0),
		.C_HAS_TERM_CNT(0),
		.C_IMPLEMENTATION(0),
		.C_MAX_LEN_LOGIC(0),
		.C_MAX_LEN_LOGIC_TYPE(0),
		.C_SINIT_VAL("11111111111111111111111111111111"),
		.C_SIZE(32),
		.C_TAP_POS("11000000000000000000010000000001"),
		.C_TYPE(0))
	inst (
		.CLK(clk),
		.SD_OUT(sd_out),
		.CE(ce),
		.PD_OUT(),
		.LOAD(),
		.PD_IN(),
		.SD_IN(),
		.DATA_VALID(),
		.LOAD_TAPS(),
		.TAPS_IN(),
		.SINIT(),
		.AINIT(),
		.NEW_SEED(),
		.TERM_CNT());


// synthesis translate_on

endmodule

