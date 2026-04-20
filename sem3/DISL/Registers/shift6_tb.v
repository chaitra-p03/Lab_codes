  // Code your testbench here
// or browse Examples
`timescale 1ns/1ns
`include "shift6.v"
module shift6_tb();
    reg w;
    reg clk;
    wire [5:0] q;
    
    shift6 s1(w, clk, q);
    
    initial
    begin
        clk = 0;
        forever #20 clk = ~clk;
    end
    
    initial
    begin
        $dumpfile("shift6_tb.vcd");
        $dumpvars(0,shift6_tb);
        
        // Test sequence
        w = 1'b0; #20;  
        w = 1'b0; #20;    
        w = 1'b1; #20;  
        w = 1'b1; #20; 
        w = 1'b1; #20; 
        w = 1'b0; #20;
        w = 1'b1; #20;
        w = 1'b1; #20;
        
        $display("Test complete");
      #20;
        $finish;
    end
endmodule