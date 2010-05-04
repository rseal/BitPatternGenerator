`timescale  1ns /  10ps

module dpRamCore_tb;

   parameter SIZE=2048*4 + 6;

   reg [15:0] dataVector [0:SIZE-1];
   reg [15:0] varVector  [0:2];
   
   wire [12:0] addr1a, addr2a;
   wire [11:0] addr1b, addr2b;
   wire [3:0]  addr3a, addr3b, addr4a, addr4b;
   wire [15:0] din1, din2;
   wire [47:0] din3, din4;
   wire [31:0] dout1, dout2;
   wire [47:0] dout3, dout4;
   wire [15:0] output_port;   
   wire        ren1, ren2, ren3, ren4;
   wire        wea1, wea2, wea3, wea4, wea5, wea6;
   reg 	       active_buffer=0;
   reg 	       clk;
   reg [11:0]  j,k;
   reg         ren=0, wea=0;
   reg [15:0]  in;
   wire [15:0] out;
   wire        ready;
   
   
   dpram dp1(
	     .addra(addr1a),
	     .addrb(addr1b),
	     .clka(clk),
	     .clkb(clk),
	     .dina(din1),
	     .doutb(dout1),
	     .wea(wea1)
	     );

   dpram dp2(
	     .addra(addr2a),
	     .addrb(addr2b),
	     .clka(clk),
	     .clkb(clk),
	     .dina(din2),
	     .doutb(dout2),
	     .wea(wea2)
	     );

   ddpram ddp1(
	       .A(addr3a),
	       .CLK(clk),
	       .D(din3),
	       .WE(wea3),
	       .DPRA(addr3b),
	       .QDPO_CLK(clk),
	       .QDPO(dout3),
	       .QSPO()
	       );
   
   ddpram ddp2(
	       .A(addr4a),
	       .CLK(clk),
	       .D(din4),
	       .WE(wea4),
	       .DPRA(addr4b),
	       .QDPO_CLK(clk),
	       .QDPO(dout4),
	       .QSPO()
	       );
          

   OutputControl oc(
	     	    .active_buffer(active_buffer),
		    .clk(clk), 
		    .rst(rst), 
		    .ren(ren),
		    .dout(output_port), 
		    .din1(dout1),
		    .din2(dout2),
		    .din3(dout3),
		    .din4(dout4),
		    .addr1(addr1b),
		    .addr2(addr2b),
		    .addr3(addr3b),
		    .addr4(addr4b)
		    );
   
  InputControl ic(
		  .active_buffer(active_buffer),
		  .clk(clk),
		  .rst(rst),
		  .wen(wea),
		  .din(in),
		  .wout1(wea1),
		  .wout2(wea2),
		  .wout3(wea3),
		  .wout4(wea4),
		  .dout1(din1),
		  .dout2(din2),
		  .dout3(din3),
		  .dout4(din4),
		  .addr1(addr1a),
		  .addr2(addr2a),
		  .addr3(addr3a),
		  .addr4(addr4a),
		  .ready(ready)
		  );


   
   //produce clock
   initial
     begin	
	clk=0;
	forever #5 clk = ~clk;
     end

   //write enable 
   initial
     begin
	ren =0;	
	wea = 0;
	wea = #10 1;
	ren = #10 1;
	
//	forever #82100 wea = ~wea;
     end

   
   //produce output to view waveforms
   initial
     begin
	$dumpfile("dpram.out");
	$dumpvars;
     end

   //initialize variables and read vector file
   initial
     begin
	j<=0;
	k<=0;	
	$readmemb("randomInput.vec", dataVector);
	#100000 $finish;
     end

   //test code
   always @ (negedge clk & wea)     
     begin
	in <= dataVector[j];
	j  <= j==SIZE-1 ? 0 : j+1;
	if(j==30) ren = 1;
     end
   

   always @ (negedge clk & ren)
     begin
	k <= k==SIZE-1 ? 0 : k+1;
     end

/* -----\/----- EXCLUDED -----\/-----

     always @ ( posedge clk & wea)
       out   <= dout;
 -----/\----- EXCLUDED -----/\----- */
   
endmodule // demux1to4_tb
