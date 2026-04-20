module comparator(a,b,gt,lt,eq);
input [3:0]a,b;
output gt,lt,eq;
wire i0,i1,i2,i3;
assign i3 = ~(a[3]^b[3]);
assign i2 = ~(a[2]^b[2]);
assign i1 = ~(a[1]^b[1]);
assign i0 = ~(a[0]^b[0]);
assign eq = i0&i1&i2&i3;
assign gt = ((a[3]&(~b[3]))|(i3&(a[2]&(~b[2])))|(i3&i2&(a[1]&(~b[1])))|(i3&i2&i1&(a[0]&(~b[0]))));
assign lt = ~(gt|eq);
endmodule