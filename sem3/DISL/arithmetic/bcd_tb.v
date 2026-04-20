`timescale 1ns/1ns
`include "bcd.v"

module bcd_tb();
reg [3:0]x,y;
wire [3:0]s;
wire cout;

bcd ex1(x,y,s,cout);
initial
begin
$dumpfile("bcd_tb.vcd");
$dumpvars(0,bcd_tb);
        x = 4'b0000; y = 4'b0000; #20;
        x = 4'b0101; y = 4'b0011; #20;
        x = 4'b0110; y = 4'b0100; #20;
        x = 4'b0111; y = 4'b1000; #20;
        x = 4'b1001; y = 4'b0001; #20;
        x = 4'b0101; y = 4'b0110; #20;
        x = 4'b1000; y = 4'b0111; #20;
        x = 4'b1001; y = 4'b0110; #20;
        x = 4'b1001; y = 4'b1001; #20;
        x = 4'b0010; y = 4'b0111; #20;

$display("Test complete");
end 
endmodule