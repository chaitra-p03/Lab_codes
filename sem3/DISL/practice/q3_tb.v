`timescale 1ns/1ns
`include "q3.v"

module q3_tb();
reg p,d;
wire l;
reg [1:0]count;
wire [1:0]s;
wire cout;

q3 ex1(p,d,l);
adder2 counter(count,2'b01,1'b0,s,cout);
initial
begin
$dumpfile("q3_tb.vcd");
$dumpvars(0,q3_tb);
	count=2'b00;
	p=0;d=0;
	#20;
	if(p&&d) count=s;
	p=1;d=1;
	#20;
	if(p&&d) count=s;
	$display("p=%b, d=%b, L=%b, count=%b", p, d, l, count);
	p=0;d=1;
	#20;
	if(p&&d) count=s;
	p=1;d=0;
	#20;
	if(p&&d) count=s;
	$display("p=%b, d=%b, L=%b, count=%b", p, d, l, count);
	$display("Test Complete");
	
	end
	endmodule
	
