module addsub4(x,y,cin,s,cout);
input [3:0]x,y;
input cin;
output [3:0]s;
output cout;
wire [3:0]c0;
assign c0[0]=y[0]^cin;
assign c0[1]=y[1]^cin;
assign c0[2]=y[2]^cin;
assign c0[3]=y[3]^cin;
adder4 a1(x,c0,cin,s,cout);
endmodule

module adder4(x,y,c0,s,cout);
input [3:0]x,y;
input c0;
output [3:0]s;
output cout;
wire c1,c2,c3;
full f1(x[0],y[0],c0,s[0],c1);
full f2(x[1],y[1],c1,s[1],c2);
full f3(x[2],y[2],c2,s[2],c3);
full f4(x[3],y[3],c3,s[3],cout);
endmodule

module full(x,y,cin,s,cout);
input x,y,cin;
output s,cout;
assign s = x^y^cin;
assign cout = (x&y)|(y&cin)|(cin&x);
endmodule