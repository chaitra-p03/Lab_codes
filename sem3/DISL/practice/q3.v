/* p is the presence of person, d is day/night sensor
light is turned on only when p=1 and d=1 (night)
simplify using kmap and 2 bit energy counter that counts
when light is turned on.
*/

module q3(p,d,l);
input p,d;
output l;
assign l=p*d;
endmodule

module adder2(x,y,cin,s,cout);
input [1:0]x,y;
input cin;
output [1:0]s;
output cout;
wire c1;
full f1(x[0],y[0],cin,s[0],c1);
full f2(x[1],y[1],c1,s[1],cout);
endmodule

module full(x,y,cin,s,cout);
input x,y,cin;
output s,cout;
assign s=x^y^cin;
assign cout=(x*y)|(y*cin)|(cin*x);
endmodule