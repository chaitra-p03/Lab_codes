module mul2(x,y,p);
input [1:0]x,y;
output [3:0]p;
wire c0,c1;
wire a1,a2,a3;
assign p[0] = x[0]&y[0];
assign a1 = x[1]&y[0];
assign a2 = x[0]&y[1];
assign a3 = x[1]&y[1];
half h1(a1,a2,p[1],c0);
half h2(c0,a3,p[2],c1);
assign p[3] = c1;
endmodule



module half(x,y,s,cout);
input x,y;
output s,cout;
assign s = x^y;
assign cout = x&y;
endmodule