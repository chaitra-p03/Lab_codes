`timescale 1ns/1ns

module dec4to16_tb();
reg [3:0]w;
reg en;
wire [15:0]f;

dec4to16 ex1(w,en,f);
initial
begin 
	$dumpfile("dec4to16_tb.vcd");
	$dumpvars(0,dec4to16_tb);
	w=4'b0000; en=1;
	#20;
	w=4'b0001; en=1;
	#20;
	w=4'b0100; en=1;
	#20;
	w=4'b1111; en=1; 
	#20;
	w=4'b1010; en=1;
	#20;
	w=4'b1001; en=1;
	#20;
	$display("Test complete");
end
endmodule