`timescale 1ns/1ns
`include "q2.v"

module q2_tb();
reg c,f,v;
wire fout;
reg[2:0] count;
wire [2:0]sum;
wire cout;

q2 ex1(c,f,v,fout);
adder3 counter(count,3'b001, 1'b0, sum,cout);
initial
begin 
$dumpfile("q2_tb.vcd");
$dumpvars(0,q2_tb);
	count = 3'b000;
	c=1;f=1; v=1;
	#20;
	if(fout&&~v) count = sum;
	#1;
	$display("count %b",count);
	c=1;f=1; v=0;
	#20;
	if(fout&&~v) count = sum;
	#1;
	$display("count %b",count);
	c=1;f=0; v=1;
	#20;
	if(fout&&~v) count = sum;
	#1;
	$display("count %b",count);
	c=0;f=0; v=0;
	#20;
	if(fout&&~v) count = sum;
	#1;
	$display("count %b",count);
	c=1 ;f=0 ;v=0;
	#20;
	if(fout&&~v) count = sum;
	#1;
	$display("count %b",count);
	c=1; f=1; v=1; 
	#20;
	if(fout&&~v) count = sum;
	#1;
	$display("count %b",count);
	$display("Test Complete");
	
	end
	endmodule