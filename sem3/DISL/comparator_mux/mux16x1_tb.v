`timescale 1ns/1ns
`include "mux16x1.v"

module mux16x1_tb();
reg [15:0]w;
reg [3:0]s;
wire f;

mux16x1 ex1(w,s,f);
initial
begin
$dumpfile("mux16x1_tb.vcd");
$dumpvars(0,mux16x1_tb);
	w=16'hFFFF; s=4'b0000;
	#20;
	w=16'h0000; s=4'b0000;
	#20;
	w=16'h5555; s=4'b0001;
	#20;
	w=16'hAAAA; s=4'b0010;
	#20;
	w=16'h0001; s=4'b0000;
	#20;
	w=16'h8000; s=4'b1111;
	#20;
	w=16'h00FF; s=4'b0111;
	#20;
	w=16'hFF00; s=4'b1000;
	#20;
	w=16'hF0F0; s=4'b0011;
	#20;
	w=16'h0F0F; s=4'b1100;
	#20;
$display("Test Complete");
end
endmodule
