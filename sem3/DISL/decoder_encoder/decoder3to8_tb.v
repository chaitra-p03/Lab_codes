`timescale 1ns/1ns
`include "decoder3to8.v"

module decoder3to8_tb();
reg [2:0]w;
reg en;
wire [7:0]f;

decoder3to8 ex1(w,en,f);
initial
begin 
	$dumpfile("decoder3to8_tb.vcd");
	$dumpvars(0,decoder3to8_tb);
	w=3'b000; en=1;
	#20;
	w=3'b001; en=1;
	#20;
	w=3'b010; en=1;
	#20;
	w=3'b011; en=1; 
	#20;
	w=3'b100; en=1;
	#20;
	w=3'b101; en=1;
	#20;
	w=3'b110; en=1;
	#20;
	w=3'b111; en=1;
	#20;
	$display("Test complete");
end
endmodule
