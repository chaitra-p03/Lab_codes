module decoder4to16(w,en,f);
input [3:0] w;
input en;
output [15:0] f;
wire [3:0] fin;

decoder2to4 d1(w[3:2],en,fin[3:0]);
// active low output from first converted into active high input for others
decoder2to4 d2(w[1:0],~fin[0],f[3:0]);
decoder2to4 d3(w[1:0],~fin[1],f[7:4]);
decoder2to4 d4(w[1:0],~fin[2],f[11:8]);
decoder2to4 d5(w[1:0],~fin[3],f[15:12]);

endmodule

module decoder2to4(w,en,f);
input [1:0] w;
input en;
output reg [3:0] f;

always @(w or en)
begin
    if(en) begin
        case(w)
            2'b00: f = 4'b1110; 
            2'b01: f = 4'b1101;  
            2'b10: f = 4'b1011;  
            2'b11: f = 4'b0111; 
            default: f = 4'b1111;
        endcase
    end 
	else f = 4'b1111; 

endmodule
