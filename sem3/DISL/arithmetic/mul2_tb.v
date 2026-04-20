`timescale 1ns/1ns
`include "mul2.v"
module mul2_tb();
reg [1:0]x,y;
wire [3:0]p;

mul2 ex1(x,y,p);
initial
begin
$dumpfile("mul2_tb.vcd");
$dumpvars(0,mul2_tb);
        x = 2'b00; y = 2'b00;
        #20;
        x = 2'b00; y = 2'b01;
        #20;
        x = 2'b00; y = 2'b10;
        #20;
        x = 2'b00; y = 2'b11;
        #20;
        x = 2'b01; y = 2'b00;
        #20;
        x = 2'b01; y = 2'b01;
        #20;
        x = 2'b01; y = 2'b10;
        #20;
        x = 2'b01; y = 2'b11;
        #20;
        x = 2'b10; y = 2'b00;
        #20;
        x = 2'b10; y = 2'b01;
        #20;
        x = 2'b10; y = 2'b10;
        #20;
        x = 2'b10; y = 2'b11;
        #20;
        x = 2'b11; y = 2'b00;
        #20;
        x = 2'b11; y = 2'b01;
        #20;
        x = 2'b11; y = 2'b10;
        #20;
        x = 2'b11; y = 2'b11;
        #20;
        $display("Test complete");
        
end
endmodule