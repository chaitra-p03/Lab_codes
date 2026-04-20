module decoder3to8(w,en,f);
input [2:0]w;
input en; 
output [7:0]f;
wire en1,en2;

assign en1 = en & (~w[2]);
assign en2 = en & w[2];
decoder2to4 dec1(w[1:0],en1,f[3:0]);
decoder2to4 dec2(w[1:0],en2,f[7:4]);

endmodule

module decoder2to4(w,en,f);
input [1:0] w;
input en;
output reg [3:0] f;

always @(w or en)
begin
	f=4'b0000;
	if(en) begin
		case(w)
			2'b00: f[0]=1'b1;
			2'b01: f[1]=1'b1;
			2'b10: f[2]=1'b1;
			2'b11: f[3]=1'b1;
		endcase
	end
end
endmodule