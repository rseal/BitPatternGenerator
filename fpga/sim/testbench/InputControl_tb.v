`timescale  1ns /  10ps

module InputControl_tb;

   //simulation variables
   parameter TEST_VECTOR_LENGTH=8196;
   parameter BLOCK_SIZE=4096;
  
   reg [15:0] testVector [0:2*TEST_VECTOR_LENGTH-1];
   reg [16:0] testVectorIter;
   
   reg [12:0] dataVectorIter;
   reg        we;
   reg 	      clk;
   reg 	      read_data;
   reg 	      read_delay;
   reg 	      read_complete;
   
   //control signals
   reg 	      reset;
   
   //status signals
   wire       ready, load_complete;
   reg 	      active_buffer;
   
   //data buffer signals
   reg  [15:0] din;
   wire [15:0] dout;
   wire [12:0] daddr;
   wire        dwe;

   //variable buffer signals
   wire [31:0] vout;   
   wire [3:0]  vaddr;   
   wire        vwe;

   //BRAM output variables
   wire [31:0] dout_b;
   reg [11:0]  daddr_b;
   wire [31:0] vout_b;
   reg [3:0]   vaddr_b;
   
   //Module under test
   InputControl ic(
		   .active_buffer(active_buffer),
		   .clk(clk),
		   .we(we),
		   .din(din),
		   .dwe(dwe),
		   .vwe(vwe),
		   .dout(dout),
		   .vout(vout),
		   .daddr(daddr),
		   .vaddr(vaddr),
		   .ready(ready),
		   .load_complete(load_complete),
		   .reset(reset)
		   );

   //data BRAM for InputControl output verification
   dpram data1(
	       .addra(daddr),
	       .addrb(daddr_b),
	       .clka(clk),
	       .clkb(clk),
	       .dina(dout),
	       .doutb(dout_b),
	       .wea(dwe)
	       );

   //variable BRAM for InputControl output verification
   ddpram dpvar1(
		 .a(vaddr),
		 .clk(clk),
		 .d(vout),
		 .we(vwe),
		 .dpra(vaddr_b),
		 .qdpo_clk(clk),
		 .qdpo(vout_b),
		 .qspo()
		 );
   
   //produce usb clock
   initial
     begin	
	clk=0;
	forever #10.42 clk = ~clk;
     end
   
   //initialize variables
   initial
     begin
	testVectorIter <= 0;
	dataVectorIter <= 0;
	read_data <= 0;
	active_buffer <= 1;
	vaddr_b <= 0;
	daddr_b <=0;
	read_delay <= 0;
	read_complete <= 0;
	we <= 0;
	din <= 0;
	reset <= 1;
     end

   //reset the fpga
   initial
     begin
	reset = #20.82 0;
	reset = #20.82 1;
	@(posedge clk) we = #5 1;
     end
   
   //produce output to view waveforms
   initial
     begin
	$dumpfile("InputControl.gtk");
	$dumpvars;
     end

   //initialize variables and read vector file
   initial
     begin	
	$readmemb("../input/data/test.bin", testVector);
	#150000 $finish;
     end

   //data is updated on negative edge
   always @ (posedge clk)
     begin
	if(we)
	  begin
	     din <= #15 testVector[testVectorIter];
     	     testVectorIter <= testVectorIter+1;
	  end
     end
   
   //read and compare data after buffer is loaded into BRAM
   always @ (posedge clk)
     begin

	//if all data has been loaded to the
	//InputControl module then read
	//RAM and verify results.
	if(testVectorIter == BLOCK_SIZE+2)
	  begin
	     read_data <= 1;
	     we <= 0;
	     testVectorIter <= 0;	     
	  end
     end // always @ (posedge clk)
   

   always @ (posedge clk)
     begin
	if(read_data)
	  if(dataVectorIter == 2048)
	    begin
	       read_complete <= 1;
	       dataVectorIter <= 0;
	       active_buffer <= ~active_buffer;
	    end
	  else
	    begin
	       dataVectorIter <= dataVectorIter + 1;
	       daddr_b <= dataVectorIter;
	    end // else: !if(dataVector == DRAM_LENGTH)
     end // always @ (negedge clk)

endmodule // InputControl_tb
