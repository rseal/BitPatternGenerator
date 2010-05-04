//------------------------------------------------------------------------
// dut_tf.v
//
// A simple text fixture shell for getting started with FrontPanel 3.x
// simulation.  This sample connects the top-level signals from a basic
// FrontPanel project to the task/function call system below.  When
// integrated with Opal Kelly simulation libraries, this mimics the
// functionality of FrontPanel.
//------------------------------------------------------------------------
// Copyright (c) 2005 Opal Kelly Incorporated
// $Rev: 202 $ $Date: 2006-11-15 19:30:19 -0800 (Wed, 15 Nov 2006) $
//------------------------------------------------------------------------

`timescale 1ns / 1ps

module Simple_Test;

reg	[7:0]		hi_in;
wire	[1:0]		hi_out;
wire	[15:0]	hi_inout;

reg				clk1;
wire	[7:0]		led;
reg	[3:0]		button;

userModule DUT (
	.hi_in(hi_in),
	.hi_out(hi_out),
	.hi_inout(hi_inout),
	.clk1(clk1),
	.led(led),
	.button(button)
	);

initial clk1 = 0;
always #9 clk1 = ~clk1;

initial button = 4'b1111;

//------------------------------------------------------------------------
// Begin okHostInterface simulation user configurable global data
//------------------------------------------------------------------------
parameter BlockDelayStates = 5;		// REQUIRED: # of clocks between blocks of pipe data
parameter ReadyCheckDelay = 5;		// REQUIRED: # of clocks before block transfer before
												//		host interface checks for ready (0-255)
parameter PostReadyDelay = 5;			// REQUIRED: # of clocks after ready is asserted and
												//		check that the block transfer begins (0-255)
parameter pipeInSize = 1024;			// REQUIRED: byte (must be even) length of default
												//		PipeIn; Integer 0-2^32
parameter pipeOutSize = 1024;			// REQUIRED: byte (must be even) length of default
												//		PipeOut; Integer 0-2^32

integer k;
reg	[7:0]	pipeIn [0:(pipeInSize-1)];
initial for (k=0; k<pipeInSize; k=k+1) pipeIn[k] = 8'h00;

reg	[7:0]	pipeOut [0:(pipeOutSize-1)];
initial for (k=0; k<pipeOutSize; k=k+1) pipeOut[k] = 8'h00;

reg	[15:0]	wireOutep20;		// User added register

//------------------------------------------------------------------------
//	Available User Task and Function Calls:
//		FrontPanelReset;					// Always start routine with FrontPanelReset;
//		SetWireInValue(ep, val, mask);
//		UpdateWireIns;
//		UpdateWireOuts;
//		GetWireOutValue(ep);				
//		ActivateTriggerIn(ep, bit);	// bit is an integer 0-15
//		UpdateTriggerOuts;
//		IsTriggered(ep, mask);			// Returns a 1 or 0
//		WriteToPipeIn(ep, length);		// passes pipeIn array data
//		ReadFromPipeOut(ep, length);	// passes data to pipeOut array
//    WriteToBlockPipeIn(ep, blockSize, length);   -- pass pipeIn array data; blockSize and length are integers
//    ReadFromBlockPipeOut(ep, blockSize, length); -- pass data to pipeOut array; blockSize and length are integers
//
//    *Pipes operate by passing arrays of data back and forth to the user's
//    design.  If you need multiple arrays, you can create a new procedure
//    above and connect it to a differnet array.  More information is
//    available in Opal Kelly documentation and online support tutorial.
//------------------------------------------------------------------------

// User configurable block of called FrontPanel operations.
initial begin
	FrontPanelReset;						// Start routine with FrontPanelReset;

	//---------------------------------------------------------------------
	// Sample task and function operations
	//---------------------------------------------------------------------
	
	// Sets a local register to value 0x1234 for WireIn endpoint 0x00
	//SetWireInValue(8'h00, 16'h1234, 16'hffff);

	// Sends all local WireIn register values to associated WireIn endpoints,
	//	and then triggers all Wire endpoints to update their values
	//UpdateWireIns;
	
	// Simulate pushing the first button
	//button = 4'b1110;

	// Delay 44 ns for no particular reason
	//#44;
	
	// Send an update siganl to all Wire endpoints and then retrieves latest
	// WireOut values into local registers.
	//UpdateWireOuts;
	
	// Get the value that was on WireOut endpoint 0x20 when last update called
	//wireOutep20 = GetWireOutValue(8'h20);

	// Simulate releasing first button
	//button = 4'b1111;

	// Send a trigger signal to bit 1 at endpoint 0x40
	//ActivateTriggerIn(0'h40, 1);
	
	// Retreives the trigger values of all TriggerOut endpoints to local
	// registers
	//UpdateTriggerOuts;
	
	// Receive a 1 if trigger[0] at endpoint 0x60 has occurred, or a 0 otherwise
	//k = IsTriggered(0'h60,0x0001);
	
	// Send 8 bytes (4 words) of data stored in pipeIn array to PipeIn endpoint 0x80
	//WriteToPipeIn(0'h80, 8);

	// Receive 8 bytes (4 words) of data from PipeOut endpoint 0xA0 to pipeOut array
	//ReadFromPipeOut(0'hA0, 8);

	// Send 1024 bytes of data in pipeIn array.  Data will come in two 512 byte
	// blocks with a delay between each (programmable).  User must give valid Ready signal
	// before each block transfer for it to commence.
	//WriteToBlockPipeIn(8'h81, 512, 1024);
	
	// Receive 1024 bytes of data into pipeOut array.  Data will come in two 512 byte
	// blocks with a delay between each (programmable).  User must give valid Ready signal
	// before block transfer
	//ReadFromBlockPipeOut(8'ha1, 512, 1024);

	$display(" ");
	$display("//// Simulation done at: %7dns ////", $time);
	$display(" ");
	
end

`include "okHostCalls.v"	// Do not remove!  The tasks, functions, and data stored
									// in okHostCalls.v must be included here.
	
endmodule
