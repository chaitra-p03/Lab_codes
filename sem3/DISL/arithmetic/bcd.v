`include "addsub4.v"

module bcd(x,y,s,cout);
input [3:0]x,y;
output [3:0] s;
output cout;

wire c_adder;
wire [3:0] s_adder;
adder4 a1(x,y,1'b0,s_adder,c_adder);

wire r1,r2;
wire correction;
and(r1,s_adder[3],s_adder[2]);
and(r2,s_adder[3],s_adder[1]);
or(correction,c_adder,r1,r2);

wire [3:0] c_six;
assign c_six[0]=1'b0;
assign c_six[1]=correction;
assign c_six[2]=correction;
assign c_six[3]=1'b0;
adder4 a2(s_adder,c_six,1'b0,s,unused_carry);
assign cout = correction;
endmodule