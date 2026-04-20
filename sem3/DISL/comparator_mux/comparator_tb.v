`timescale 1ns/1ns
`include "comparator.v"

module comparator_tb();
reg [3:0]a,b;
wire gt,lt,eq;

comparator ex1(a,b,gt,lt,eq);
initial 
begin 
$dumpfile("comparator_tb.vcd");
$dumpvars(0,comparator_tb);
	a=4'b0000; b=4'b0000;
	#20;
	a=4'b0000; b=4'b0101;
	#20;
	a=4'b1111; b=4'b1011;
	#20;
	
	$display("Test Complete");
	
end
endmodule