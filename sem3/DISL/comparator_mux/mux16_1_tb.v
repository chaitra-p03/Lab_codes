`timescale 1ns/1ns
`include "mux16_1.v"

module mux16_1_tb();
reg [15:0]w;
reg [3:0]s;
wire f;

mux16_1 ex1(w,s,f);
initial
begin
$dumpfile("mux16_1_tb.vcd");
$dumpvars(0,mux16_1_tb);
	w=16'hFFFF; s=4'b0000;
	#20;
	w=16'hFAAF; s=4'b0001;
	#20;
	w=16'hFAAF; s=4'b0100;
	#20;
	w=16'h6FFF; s=4'b1000;
	#20;
	w=16'h1111; s=4'b1101;
	#20;
	w=16'h2211; s=4'b1111;
	#20;
	w=16'h1121; s=4'b0101;
	#20;


$display("Test Complete");
end
endmodule
