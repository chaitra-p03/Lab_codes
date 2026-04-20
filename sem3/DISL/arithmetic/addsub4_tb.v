`timescale 1ns/1ns
`include "addsub4.v"
module addsub4_tb();
reg [3:0]x,y;
reg cin;
wire cout;
wire [3:0]s;

addsub4 ex1(x,y,cin,s,cout);
initial
begin
$dumpfile("addsub4_tb.vcd");
$dumpvars(0,addsub4_tb);
        x = 4'b0000; y = 4'b0000; cin = 1'b0;
        #20;
		x = 4'b0111; y = 4'b0011; cin = 1'b0;
		#20;
		x = 4'b0101; y = 4'b1111; cin = 1'b1;
		#20;
		x = 4'b1111; y = 4'b1111; cin = 1'b0;
        #20;
        x = 4'b0011; y = 4'b1000; cin = 1'b1;
        #20;
        x = 4'b0101; y = 4'b1010; cin = 1'b1;
        #20;
        x = 4'b1111; y = 4'b0000; cin = 1'b1;
        #20;
        x = 4'b1010; y = 4'b1010; cin = 1'b1;
        #20;
        x = 4'b0000; y = 4'b1111; cin = 1'b1;
        #20;
		x = 4'b0101; y = 4'b0011; cin = 1'b1;
		#20;
		x = 4'b0111; y = 4'b0001; cin = 1'b0;
		#20;
		$display("Test complete");
		
end
endmodule