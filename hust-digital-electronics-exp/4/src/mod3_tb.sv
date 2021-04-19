`timescale 1ns / 1ps

module mod3_tb (
    
);
    reg [2:0] l, r;
    wire greater, even, smaller;
    mod3 _1(l,r,greater,even,smaller);
    initial begin
        l = 7;
        r = 4;
        #2 l = 1;
        #4 r = 1;
    end
endmodule