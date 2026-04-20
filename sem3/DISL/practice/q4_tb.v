`timescale 1ns/1ns
`include "q4.v"

module q4_tb();
reg [3:0]x,y;
reg cin;
wire [3:0]s;

q4 ex1(x,y,cin,s);
initial 
begin
    $dumpfile("q4_tb.vcd");
    $dumpvars(0, q4_tb);
    
    x=4'b0101; y=4'b0010; cin=0;
    #20;
	x=4'b0010; y=4'b1101; cin=1;
	#20;
	x=4'b0010; y=4'b0100; cin=1;
	#20;
    x=4'b0111; y=4'b1010; cin=1;
    #20;
    x=4'b0011; y=4'b1010; cin=1;
    #20;
    x=4'b0101; y=4'b1101; cin=1;
    #20;
    
    $finish;
end
endmodule
