module dec4to16(w,en,f);
input [3:0]w;
input en; 
output [15:0]f;
wire en1, en2;
assign en1 = (~w[3])&en;
assign en2 = w[3]&en;
dec3to8 d1(w[2:0],en1,f[7:0]);
dec3to8 d2(w[2:0],en2,f[15:8]);

endmodule

module dec3to8(w,en,f);
input [2:0]w;
input en; 
output reg [7:0]f;
integer i;
always@(w or en)
begin
	if(en==1'b1) begin
	f=8'b00000000;
		for(i=0; i<8; i=i+1) begin
			if(i==w) 
			f[i]=1'b1;
		end
	end
	else f=8'b00000000;
end

endmodule