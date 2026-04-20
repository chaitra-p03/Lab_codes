module mux41(w,s,f);
input [3:0]w;
input [1:0]s;
output f;
wire r1,r2;
mux21 m1(w[0],w[1],s[0],r1);
mux21 m2(w[2],w[3],s[0],r2);
mux21 m3(r1,r2,s[1],f);
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
