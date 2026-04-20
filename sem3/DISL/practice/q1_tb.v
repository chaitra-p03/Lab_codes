`timescale 1ns/1ns
`include "q1.v"

module q1_tb();
reg [3:0]x,y;
reg cin; 
wire [3:0]s;
wire cout;

q1 ex1(x,y,cin,s,cout);
initial
begin
$dumpfile("q1_tb.vcd");
$dumpvars(0,q1_tb);
	x=4'b0011; y=4'b0001; cin=0;
	#20;
	x=4'b1111; y=4'b0000; cin=0;
	#20;
	x=4'b1111; y=4'b1101; cin=0; 
	#20;
	x=4'b1111; y=4'b1111; cin=0;
	#20;
	x=4'b0101; y=4'b1111; cin=1;
	#20;
	x=4'b0011; y=4'b1101; cin=1;
	#20;
	x=4'b0000; y=4'b1010; cin=1;
	#20;
	
	$display("Test Complete");
	end
	endmodule
	