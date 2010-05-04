`timescale  1ns /  10ps

`define CLK20MHZ_PERIOD 5
`define CLK20MHZ_50 2.5
`define CLK10MHZ_PERIOD 10
`define CLK10MHZ_50 5


module clkDivider_tb;
   
		     
   reg         clk_20MHz;
   wire        clk_out;
   reg  [15:0] div;
   reg         rst;
   reg 	       clk_10MHz;
   reg [15:0]  count;
   reg 	       load_div;
   reg 	       change_count;
   
   ClockDivider clkdiv1 (
		    .clk_in(clk_20MHz),
		    .div(div),
	            .clk_out(clk_out),
		    .reset(rst)
		    );
    
   //produce reference clock
   initial
     begin
	clk_20MHz=0;
	forever #`CLK20MHZ_50 clk_20MHz = ~clk_20MHz;
     end

   //produce output clock
   initial
     begin
	clk_10MHz = 0;
	#2.5 clk_10MHz = 1;	
	forever #`CLK10MHZ_50 clk_10MHz = ~clk_10MHz;
     end
   
   initial
     begin
	div = 1;
	count = 200;
	load_div = 0;	
	rst = 1;
	rst = #20 0;
	rst = #20 1;
     end
   
   //write enable 
   initial
     begin
	#20000 $finish;	
     end

   
   always @ (negedge clk_out)
     begin
	if(count == 1)
	  begin
	     count <= 200;
	  end
	else
	  count <= count - 1;
     end

   always @(posedge clk_out)
     begin
	if(count == 1)
	  div <= div +1;
     end
   
   //produce output to view waveforms
   initial
     begin
	$dumpfile("ClockDivider.gtk");
	$dumpvars;
     end
   
endmodule // clkDivider_tb

