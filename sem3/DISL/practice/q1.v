//saturated result adder/subtractor
module q1(x,y,cin,s,cout);
input [3:0]x,y;
input cin; 
output [3:0]s;
output cout;
wire [3:0]y_new;
assign y_new[0]=y[0]^cin;
assign y_new[1]=y[1]^cin;
assign y_new[2]=y[2]^cin;
assign y_new[3]=y[3]^cin;
wire c1,c2,c3;
wire [3:0]initial_sum;
full f1(x[0],y_new[0],cin,initial_sum[0],c1);
full f2(x[1],y_new[1],c1,initial_sum[1],c2);
full f3(x[2],y_new[2],c2,initial_sum[2],c3);
full f4(x[3],y_new[3],c3,initial_sum[3],cout);
reg [3:0]s;
always@(cout or cin or initial_sum)
begin 
if(cin==0 && cout ==1)
s=4'b1111;
else if (cin==1 && cout==0)
s=4'b0000;
else s=initial_sum;
end
endmodule


module full(x,y,cin,s,cout);
input x,y,cin;
output s,cout;
assign s = x^y^cin;
assign cout = x*y | y*cin | cin*x;
endmodule