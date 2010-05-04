`timescale  1ns /  100ps

`include "config.v"

module OutputControl_tb;

   //test bench stimulus
   parameter TEST_VECTOR_LENGTH=8196;
   parameter BUFFER_LENGTH=2048;
   parameter BLOCK_SIZE=4099;
   
   reg 	     switch;
   reg 	     start;
   reg 	     reset;
   reg 	     stop;
   reg 	     pps_1s;
   reg 	     pps_10s;
   reg 	     ext_trig;
   reg 	     usb_clk;
   reg [1:0] sync ;
   reg [15:0] testVector [0:TEST_VECTOR_LENGTH-1];
   reg [16:0] testVectorIter;
   reg [12:0] dataVectorIter;
   reg [1:0]  modeNum;
   
   //input module connections
   reg [15:0] tb_din_ic ;
   reg 	      tb_we_ic ;
   wire       ic_dwe_dpdata;
   wire       ic_vwe_dpvar;
   wire [15:0] ic_dout_dpdata ;
   wire [31:0] ic_vout_dpvar ;
   wire [12:0] ic_daddr_dpdata ;
   wire [3:0]  ic_vaddr_dpvar ;
   wire        ic_ready_oc;
   wire        load_complete;
   wire        ready;
   
   //output module connections
   wire [31:0] dpdata_din_oc ;
   wire [31:0] dpvar_vin_oc ;
   wire [11:0] oc_daddr_dpdata ;
   wire [3:0]  oc_vaddr_dpvar ;
   wire        oc_actbuf_ic;
   wire        preload;
   wire        clk_out;
   wire        active;
   wire [15:0] out_port ;
   
   //initialize testbench data
   initial
     begin
	sync = `SYNC;
	modeNum=1;	
	start=0;
	testVectorIter=0;
	dataVectorIter=0;
	stop=0;
	tb_we_ic=0;	
	pps_1s=0;
	pps_10s=0;
	ext_trig=0;
	reset=1;
	switch=0;
	
     end

   //number of simulation cycles
   initial
     begin
	#50000000 $finish;	
     end
   
   //generate clock
   initial
     begin
	usb_clk=0;
	forever #`USB_CLK_PERIOD usb_clk = ~usb_clk;
     end

   //generate reset to initialize modules
   initial
     begin	
	#`RESET_DELAY reset=0;
	#`RESET_PERIOD reset=1;
	#10.42 tb_we_ic=1;	
     end

   /*
    The OpalKelly PipeIn module presents data on the rising clock edge + delay. 
    The Input Module will read on the negative edge and present data to the 
    xilinx block RAM module, which clocks data in on the following positive edge.
    */
   
   //load test data to input module
   always @ (posedge usb_clk)
     begin
	if(tb_we_ic)
	  begin
	     tb_din_ic <= #5 testVector[testVectorIter];
	     testVectorIter <= testVectorIter + 1;	     
	  end
	if(testVectorIter == modeNum*BLOCK_SIZE)
	  begin
	     modeNum <= modeNum + 1;
	     tb_we_ic <= 0;
	  end
     end // always @ (negedge usb_clk)

   //output control asserts preload and the user
   //responds with another buffer of data
   //there are 4 buffers of test data available
   always @ (posedge preload)
     begin
	if(modeNum < 3)
	  tb_we_ic <= 1;
     end
   
   //load test vector
   initial
     begin	
	$readmemb("../input/data/test.bin", testVector);
     end

   //write simulation variables to file
   initial
     begin
	$dumpfile("../output.gtk");
	$dumpvars;
     end

   //produce sync variations
   always @ (posedge ready)
     begin
	#25 start=1;
	#`PPS_1S_DELAY   pps_1s   <= 1;
	#`PPS_10S_DELAY  pps_10s  <= 1;
	#`EXT_TRIG_DELAY ext_trig <= 1;	
     end

   //display user defined (config.v) sync mode
   initial
     begin
	case(`SYNC)
	  0: $display("SYNC: free running mode");
	  1: $display("SYNC: 1pps mode");
	  2: $display("SYNC: 10pps mode");
	  3: $display("SYNC: ext_trig mode");
	endcase // case(`SYNC)
     end // initial begin
   
   InputControl ic (
		    .active_buffer(oc_actbuf_in),
		    .clk(usb_clk),
		    .we(tb_we_ic),
		    .din(tb_din_ic),
		    .dwe(ic_dwe_dpdata),
		    .vwe(ic_vwe_dpvar),
		    .dout(ic_dout_dpdata),
		    .vout(ic_vout_dpvar),
		    .daddr(ic_daddr_dpdata),
		    .vaddr(ic_vaddr_dpvar),
		    .ready(ready),
		    .load_complete(load_complete),
		    .reset(reset)
		    );

   OutputControl oc (
	     	     .active_buffer(oc_actbuf_in),    
		     .clk(usb_clk),         
		     .pps_1s(pps_1s),      
		     .pps_10s(pps_10s),
		     .ext_trig(ext_trig),
		     .start(start),       
		     .stop(stop),
		     .ready(ready),       
		     .sync(sync),        
		     .din(dpdata_din_oc),        
		     .daddr(oc_daddr_dpdata),     
		     .vaddr(oc_vaddr_dpvar),     
		     .vin(dpvar_vin_oc),       
		     .out_port(out_port),  
		     .clk_out(clk_out),
		     .preload(preload),
		     .reset(reset),
		     .active(active),
		     .switch(switch)
		     );

   dpram data_buffer1(
		      .addra(ic_daddr_dpdata),
		      .addrb(oc_daddr_dpdata),
		      .clka(usb_clk),
		      .clkb(clk_out),
		      .dina(ic_dout_dpdata),
		      .doutb(dpdata_din_oc),
		      .wea(ic_dwe_dpdata)
		      );
   
   ddpram var_buffer1(
		      .a(ic_vaddr_dpvar),
		      .clk(usb_clk),
		      .d(ic_vout_dpvar),
		      .we(ic_vwe_dpvar),
		      .dpra(oc_vaddr_dpvar),
		      .qdpo_clk(clk_out),
		      .qdpo(dpvar_vin_oc),
		      .qspo()
		      );
endmodule