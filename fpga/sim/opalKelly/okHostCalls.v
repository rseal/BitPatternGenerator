//------------------------------------------------------------------------
// okHostCalls_v2.v
//
// Description:
//    This file is included by a test fixture designed to mimic FrontPanel
//    operations.  The functions and task below provide a pseudo
//    translation between the FrontPanel operations and the hi_in, hi_out,
//    and hi_inout signals.
//------------------------------------------------------------------------
// Copyright (c) 2006 Opal Kelly Incorporated
// $Rev: 231 $ $Date: 2007-01-24 11:35:04 -0800 (Wed, 24 Jan 2007) $
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// *  Do not edit any of the defines, registers, integers, arrays, or
//    functions below this point.
// *  Tasks in Verilog cannot pass arrays.  The pipe tasks utilize arrays
//    of data. If you require multiple pipe arrays, you may create new
//    arrays in the top level file (that `includes this file), duplicate
//    the pipe tasks below as required, change the names of the duplicated
//    tasks to unique identifiers, and alter the pipe array in those tasks
//    to your newly generated arrays in the top level file.
// *  For example, in the top level file, along with:
//       reg   [7:0] pipeIn [0:(pipeInSize-1)];
//       reg   [7:0] pipeOut [0:(pipeOutSize-1)];
//       - Add:   reg   [7:0] pipeIn2 [0:1023];
//       - Then, copy the WriteToPipeIn task here, rename it WriteToPipeIn2,
//         and finally change pipeIn[i] in WriteToPipeIn2 to pipeIn2[i].
//    The task and operation can then be called with a:
//       WriteToPipeIn2(8'h80, 1024);//endpoint 0x80 pipe received pipeIn2
//------------------------------------------------------------------------
`define DNOP                  4'h0
`define DReset                4'h1
`define DUpdateWireIns        4'h3
`define DUpdateWireOuts       4'h5
`define DActivateTriggerIn    4'h6
`define DUpdateTriggerOuts    4'h7
`define DWriteToPipeIn        4'h9
`define DReadFromPipeOut      4'ha
`define DWriteToBlockPipeIn   4'hb
`define DReadFromBlockPipeOut 4'hc

parameter tCK = 10.417; // Half of the hi_clk frequency @ 1ns timing

reg   [15:0]   hi_dataout;
reg   [15:0]   WireIns [0:31];   // 16x32 array storing WireIn values
reg   [15:0]   WireOuts [0:31];  // 16x32 array storing WireOut values
reg   [15:0]   Triggered [0:31]; // 16x32 array storing IsTriggered values

initial begin
   hi_in = 8'h03;
   hi_dataout = 16'h0000;
end

always #tCK hi_in[0] = ~hi_in[0];

assign hi_inout =  hi_in[1] ? hi_dataout : 16'hzzzz;

//---------------------------------------------------------
// FrontPanelReset Task
//---------------------------------------------------------
task FrontPanelReset ();
   integer           i;
begin
   for (i=0; i<32; i=i+1) begin
      WireIns[i] = 16'h0000;
      WireOuts[i] = 16'h0000;
      Triggered[i] = 16'h0000;
   end
   
   @(posedge hi_in[0])  hi_in[7:4] = `DReset;
   @(posedge hi_in[0]) hi_in[7:4] = `DNOP;
   wait (hi_out[0] == 0);
end
endtask

//---------------------------------------------------------
// SetWireInValue
//---------------------------------------------------------
task SetWireInValue (
   input    [7:0]    ep,
   input    [15:0]   val,
   input    [15:0]   mask
);
   reg   [15:0]   tmp;
begin
   tmp = WireIns[ep] & ~mask;
   WireIns[ep] = tmp | (val & mask);
end
endtask

//---------------------------------------------------------
// GetWireOutValue
//---------------------------------------------------------
function [15:0] GetWireOutValue (
   input    [7:0]    ep
);
begin
   GetWireOutValue = WireOuts[ep - 8'h20];
end
endfunction

//---------------------------------------------------------
// IsTriggered
//---------------------------------------------------------
function IsTriggered (
   input    [7:0]    ep,
   input    [15:0]   mask
);
begin
   if ((Triggered[ep - 8'h60] & mask) >= 0) begin
      if ((Triggered[ep - 8'h60] & mask) == 0) begin
         IsTriggered = 0;
      end else begin
         IsTriggered = 1;
      end
   end else begin
      $display("***FRONTPANEL ERROR: IsTriggered mask 0x%04h covers unused Triggers", mask);
      IsTriggered = 0;
   end
end
endfunction

//---------------------------------------------------------
// UpdateWireIns
//---------------------------------------------------------
task UpdateWireIns ();
   integer           i;
begin
   @(posedge hi_in[0]) hi_in[7:4] = `DUpdateWireIns;
   hi_in[1] = 1;
   @(posedge hi_in[0]) hi_in[7:4] = `DNOP;
   for (i=0; i<32; i=i+1) begin
      hi_dataout = WireIns[i];
      @(posedge hi_in[0]) ;
   end
   wait (hi_out[0] == 0);
end
endtask

//---------------------------------------------------------
// UpdateWireOuts
//---------------------------------------------------------
task UpdateWireOuts ();
   integer           i;
begin
   @(posedge hi_in[0]) hi_in[7:4] = `DUpdateWireOuts;
   @(posedge hi_in[0]) hi_in[7:4] = `DNOP;
   @(posedge hi_in[0]) hi_in[1] = 0;
   @(posedge hi_in[0]); @(posedge hi_in[0]);
   for (i=0; i<32; i=i+1)
      @(posedge hi_in[0]) WireOuts[i] = hi_inout;
   wait (hi_out[0] == 0);
end
endtask

//---------------------------------------------------------
// ActivateTriggerIn
//---------------------------------------------------------
task ActivateTriggerIn (
   input    [7:0]    ep,
   input    [31:0]  bit
);
begin
   @(posedge hi_in[0]) hi_in[1] = 1;
   hi_in[7:4] = `DActivateTriggerIn;
   hi_dataout = {8'h00, ep};
   @(posedge hi_in[0]) hi_dataout = (1'b1 << bit);
   hi_in[7:4] = `DNOP;
   @(posedge hi_in[0]) hi_dataout = 16'h0000;
   wait (hi_out[0] == 0);
end
endtask

//---------------------------------------------------------
// UpdateTriggerOuts
//---------------------------------------------------------
task UpdateTriggerOuts ();
   integer           i;
begin
   @(posedge hi_in[0]) hi_in[7:4] = `DUpdateTriggerOuts;
   @(posedge hi_in[0]) hi_in[7:4] = `DNOP;
   @(posedge hi_in[0]) hi_in[1] = 0;
   @(posedge hi_in[0]); @(posedge hi_in[0]); @(posedge hi_in[0]);
   for (i=0; i<32; i=i+1)
      @(posedge hi_in[0]) Triggered[i] = hi_inout;
   wait (hi_out[0] == 0);
end
endtask


//---------------------------------------------------------
// WriteToPipeIn
//---------------------------------------------------------
task WriteToPipeIn (
   input    [7:0]    ep,
   input    [31:0]   length
);
   integer           len, i, j, k, blockSize;
begin
   len = length/2; j = 0; k = 0; blockSize = 1024;
   if (length%2)
      $display("Error. Pipes commands may only send and receive an even # of bytes.");
   @(posedge hi_in[0]) hi_in[1] = 1;
   hi_in[7:4] = `DWriteToPipeIn;
   hi_dataout = {BlockDelayStates, ep};
   @(posedge hi_in[0]) hi_in[7:4] = `DNOP;
   hi_dataout = len;
   @(posedge hi_in[0]) hi_dataout = (len >> 16);
   for (i=0; i < length; i=i+2) begin
      @(posedge hi_in[0]);
      hi_dataout[7:0] = pipeIn[i];
      hi_dataout[15:8] = pipeIn[i+1];
      j=j+2;
      if (j == blockSize) begin
         for (k=0; k < BlockDelayStates; k=k+1) begin
            @(posedge hi_in[0]);
         end
         j=0;
      end
   end
   wait (hi_out[0] == 0);
end
endtask


//---------------------------------------------------------
// ReadFromPipeOut
//---------------------------------------------------------
task ReadFromPipeOut (
   input    [7:0]    ep,
   input    [31:0]   length
);
   integer           len, i, j, k, blockSize;
begin
   len = length/2; i = 0; j = 0; k = 0; blockSize = 1024;
   if (length%2)
      $display("Error. Pipes commands may only send and receive an even # of bytes.");
   @(posedge hi_in[0]) hi_in[1] = 1;
   hi_in[7:4] = `DReadFromPipeOut;
   hi_dataout = {BlockDelayStates, ep};
   @(posedge hi_in[0]) hi_in[7:4] = `DNOP;
   hi_dataout = len;
   @(posedge hi_in[0]) hi_dataout = (len >> 16);
   @(posedge hi_in[0]) hi_in[1] = 0;
   for (i=0; i < length; i=i+2) begin
      @(posedge hi_in[0]);
      pipeOut[i] = hi_inout[7:0];
      pipeOut[i+1] = hi_inout[15:8];
      j=j+2;
      if (j == blockSize) begin
         for (k=0; k < BlockDelayStates; k=k+1) begin
            @(posedge hi_in[0]);
         end
         j=0;
      end
   end
   wait (hi_out[0] == 0);
end
endtask

//---------------------------------------------------------
// WriteToBlockPipeIn
//---------------------------------------------------------
task WriteToBlockPipeIn (
   input    [7:0]    ep,
   input    [31:0]   blockLength,
   input    [31:0]   length
);
   integer           len, blockSize, blockNum, i, j, k;
begin
   len = length/2; blockSize = blockLength/2; j = 0; k = 0;
   blockNum = len/blockSize;
   if (length%2)
      $display("Error. Pipes commands may only send and receive an even # of bytes.");
   if (blockLength%2)
      $display("Error. Block Length may only be an even # of bytes.");
   if (length%blockLength)
      $display("Error. Pipe length MUST be a multiple of block length!");
   @(posedge hi_in[0]) hi_in[1] = 1;
   hi_in[7:4] = `DWriteToBlockPipeIn;
   hi_dataout = {BlockDelayStates, ep};
   @(posedge hi_in[0]) hi_in[7:4] = `DNOP;
   hi_dataout = len;
   @(posedge hi_in[0]) hi_dataout = (len >> 16);
   @(posedge hi_in[0]) hi_dataout = blockSize;
   @(posedge hi_in[0]) hi_dataout[7:0] = ReadyCheckDelay; hi_dataout[15:8] = PostReadyDelay;
   for (i=0; i < blockNum; i=i+1) begin
      while (hi_out[0] === 1) @(posedge hi_in[0]);
      while (hi_out[0] === 0) @(posedge hi_in[0]);
      @(posedge hi_in[0]); @(posedge hi_in[0]);
      for (j=0; j<blockSize; j=j+1) begin
         hi_dataout[7:0] = pipeIn[k]; hi_dataout[15:8] = pipeIn[k+1];
         @(posedge hi_in[0]); k=k+2;
      end
      for (j=0; j < BlockDelayStates; j=j+1) @(posedge hi_in[0]);
   end
   wait (hi_out[0] == 0);
end
endtask

//---------------------------------------------------------
// ReadFromBlockPipeOut
//---------------------------------------------------------
task ReadFromBlockPipeOut (
   input    [7:0]    ep,
   input    [31:0]   blockLength,
   input    [31:0]   length
);
   integer           len, blockSize, blockNum, i, j, k;
begin
   len = length/2; blockSize = blockLength/2; j = 0; k = 0;
   blockNum = len/blockSize;
   if (length%2)
      $display("Error. Pipes commands may only send and receive an even # of bytes.");
   if (blockLength%2)
      $display("Error. Block Length may only be an even # of bytes.");
   if (length%blockLength)
      $display("Error. Pipe length MUST be a multiple of block length!");
   @(posedge hi_in[0]) hi_in[1] = 1;
   hi_in[7:4] = `DReadFromBlockPipeOut;
   hi_dataout = {BlockDelayStates, ep};
   @(posedge hi_in[0]) hi_in[7:4] = `DNOP;
   hi_dataout = len;
   @(posedge hi_in[0]) hi_dataout = (len >> 16);
   @(posedge hi_in[0]) hi_dataout = blockSize;
   @(posedge hi_in[0]) hi_dataout[7:0] = ReadyCheckDelay; hi_dataout[15:8] = PostReadyDelay;
   @(posedge hi_in[0]) hi_in[1] = 0;
   for (i=0; i < blockNum; i=i+1) begin
      while (hi_out[0] === 1) @(posedge hi_in[0]);
      while (hi_out[0] === 0) @(posedge hi_in[0]);
      @(posedge hi_in[0]); @(posedge hi_in[0]);
      for (j=0; j<blockSize; j=j+1) begin
         pipeOut[k] = hi_inout[7:0]; pipeOut[k+1] = hi_inout[15:8];
         @(posedge hi_in[0]) k=k+2;
      end
      for (j=0; j < BlockDelayStates; j=j+1) @(posedge hi_in[0]);
   end
   wait (hi_out[0] == 0);
end
endtask
