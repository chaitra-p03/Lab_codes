`timescale 1ns/1ns
`include "mux41.v"

module mux41_tb();
reg [3:0]w;
reg [1:0]s;
wire f;

mux41 ex1(w,s,f);
initial
begin
$dumpfile("mux41_tb.vcd");
$dumpvars(0,mux41_tb);

w=4'b0000; s=4'b00;
#20;
w=4'b0001; s=4'b00;
#20;
w=4'b0010; s=4'b00;
#20;
w=4'b0011; s=4'b10;
#20;
w=4'b0100; s=4'b00;
#20;
w=4'b0101; s=4'b00;
#20;
w=4'b0110; s=4'b10;
#20;
w=4'b0111; s=4'b10;
#20;
w=4'b1000; s=4'b10;
#20;
w=4'b0000; s=4'b11;
#20;
w=4'b0001; s=4'b01;
#20;
w=4'b0010; s=4'b01;
#20;
w=4'b0011; s=4'b01;
#20;
w=4'b0100; s=4'b01;
#20;
w=4'b0101; s=4'b11;
#20;
w=4'b0110; s=4'b11;
#20;
w=4'b0111; s=4'b11;
#20;
w=4'b1000; s=4'b11;
#20;	

$display("Test Complete");
end
endmodule
