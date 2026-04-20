/* Design a BCD adder for 2 digits. Correct if it exceeds 9.
Use a comparator, if greater than 9 even after correction, light error */
`include "addsub4.v"

module q5(x,y,s,cout,error);
input [3:0]x,y;
output [3:0] s;
output cout;
output error;
wire c_adder;
wire unused_carry;
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

comparator cmp1(s,4'd9, error);

endmodule

module comparator(a,b,gt);
input[3:0]a,b;
output gt;
assign gt = (a>b);
endmodule