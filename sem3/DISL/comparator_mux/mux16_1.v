module mux16_1(w,s,f);
input [15:0]w;
input [3:0]s;
output f;
wire [3:0]r;
mux4_1 m1(w[3:0],s[1:0],r[0]);
mux4_1 m2(w[7:4],s[1:0],r[1]);
mux4_1 m3(w[11:8],s[1:0],r[2]);
mux4_1 m4(w[15:12],s[1:0],r[3]);
mux4_1 m5(r,s[3:2],f);
endmodule

module mux4_1(w,s,f);
input [3:0]w;
input [1:0]s;
output f;
assign f = s[1] ?(s[0]?w[3]:w[2]) : (s[0]?w[1]:w[0]);
endmodule 

