module shift6(data, clock, q);
  input data, clock;
  output [5:0]q;
  wire [5:0]d;
  
  //left shift
  assign d[0]=data;
  assign d[1]=q[0];
  assign d[2]=q[1];
  assign d[3]=q[2];
  assign d[4]=q[3];
  assign d[5]=q[4];
  
   //right shift
  // d0 has value of what goes to q0 on next clock edge
  //assign d[0]=q[1];
 // assign d[1]=q[2];
  //assign d[2]=q[3];
 // assign d[3]=q[4];
 // assign d[4]=q[5];
 // assign d[5]=data;
  
  
  dff ff0(d[0],q[0],clock);
  dff ff1(d[1],q[1],clock);
  dff ff2(d[2],q[2],clock);
  dff ff3(d[3],q[3],clock);
  dff ff4(d[4],q[4],clock);
  dff ff5(d[5],q[5],clock);
 
endmodule
  
  module dff(d,q,clock);
    input d,clock;
    output reg q;
    always @(posedge clock)
      q<=d;
  endmodule
 