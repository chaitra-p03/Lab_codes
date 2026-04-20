/* Consider a gate with 3 sensors 
A sensor (C) to detect if the car is present or not 
C=1 when the car is present and C=0 if the car is not present
F=1 when the parking lot is full and F=0 when there's space available 
V=1 when the car is a VIP car and V=0 if it isn't 
The gate should open to allow a car to enter the parking lot only when 
i) The parking lot has empty space 
ii) If the car isn't VIP , it should be allowed in even if the parking lot is full 
Implement the circuit using nand gates and use a 3 bit adder to count the number 
of instances the gate opened to let normal cars in.
Write a verilog code and testbench to simulate atleast 2 normal cases and 2 VIP cases */

module q2(c,f,v,fout);
input c,f,v;
output fout;
nand(nv,v,v);
nand(nf,f,f);
nand(r1,c,nv);
nand(r2,c,nf);
nand(fout,r1,r2);
endmodule

module adder3(x,y,cin,s,cout);
input [2:0]x,y;
input cin;
output [2:0]s;
output cout;
wire c1,c2;
full f1(x[0],y[0],cin,s[0],c1);
full f2(x[1],y[1],c1,s[1],c2);
full f3(x[2],y[2],c2,s[2],cout);
endmodule

module full(x,y,cin,s,cout);
input x,y,cin;
output s,cout;
assign s=x^y^cin;
assign cout=(x*y)|(y*cin)|(cin*x);
endmodule
