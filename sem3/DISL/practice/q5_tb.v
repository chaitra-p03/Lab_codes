`timescale 1ns/1ns
`include "q5.v"

module q5_tb();
reg [3:0] x, y;
wire [3:0] s;
wire cout,error;

q5 ex1(x,y,s,cout,error);
initial 
begin
    $dumpfile("q5_tb.vcd");
    $dumpvars(0, q5_tb);
    
    x = 4'b0000; y = 4'b0000;
    #10;
    
    x = 4'b0001; y = 4'b0001;
    #10;
    
    x = 4'b0100; y = 4'b0101;
    #10;
    
    x = 4'b0101; y = 4'b0101;
    #10;
    
    x = 4'b0110; y = 4'b0111;
    #10;
    
    x = 4'b1000; y = 4'b1001;
    #10;
    
    x = 4'b1001; y = 4'b1001;
    #10;
	
    x = 4'b1001; y = 4'b0001;
    #10;
	
    x = 4'b1111; y = 4'b1111;
    #10;
    
    $display("Test Complete");
end
endmodule