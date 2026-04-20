/*Design a circuit that takes two 4-bit numbers and a
control signal, Use a ripple carry adder/subtractor. 
Then use a comparator to check if the result is negative.
If negative, output the absolute value using mux.
*/

module q4(x,y,cin,s);
input [3:0]x,y;
input cin;
output [3:0]s;

wire cout;
wire [3:0]c0;
wire c1,c2,c3;

wire neg;
wire [3:0] raw_res;
wire [3:0] abs_res;

assign c0[0]=y[0]^cin;
assign c0[1]=y[1]^cin;
assign c0[2]=y[2]^cin;
assign c0[3]=y[3]^cin;
full f1(x[0],c0[0],cin,raw_res[0],c1);
full f2(x[1],c0[1],c1,raw_res[1],c2);
full f3(x[2],c0[2],c2,raw_res[2],c3);
full f4(x[3],c0[3],c3,raw_res[3],cout);

assign neg = raw_res[3];
assign abs_res = (~raw_res)+4'b0001;
mux_4bit mux1(raw_res,abs_res,neg,s);
endmodule

module mux_4bit(w0, w1, sel, out);
input [3:0]w0, w1;
input sel;
output [3:0]out;
assign out = sel ? w1:w0;
endmodule

module full(x,y,cin,s,cout);
input x,y,cin;
output s,cout;
assign s = x^y^cin;
assign cout = (x&y)|(y&cin)|(cin&x);
endmodule
