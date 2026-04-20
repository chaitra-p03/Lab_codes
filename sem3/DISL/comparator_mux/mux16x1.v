// Design 16-1 MUX using 8-1 and 2-1

module mux16x1(w,s,f);
input [15:0]w;
input [3:0]s;
output f;
wire r1,r2;
mux81 m1(w[7:0],s[2:0],r1);
mux81 m2(w[15:8],s[2:0],r2);
mux21 m3(r1,r2,s[3],f);
endmodule

module mux81(w,s,f);
input [7:0]w;
input [2:0]s;
output f;
reg f;
always@(s or w)
begin
case(s)
3'b000: f=w[0];
3'b001: f=w[1];
3'b010: f=w[2];
3'b011: f=w[3];
3'b100: f=w[4];
3'b101: f=w[5];
3'b110: f=w[6];
3'b111: f=w[7];
endcase
end
endmodule

module mux21(w0,w1,s,f);
input w0,w1,s;
output f;
reg f;
always@(w0 or w1 or s)
begin
if(s==0)
f=w0;
else
f=w1;
end
endmodule
