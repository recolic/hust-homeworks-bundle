`timescale 1ns / 1ps

module mod1_tb (
    
);
    reg clk = 0, clr = 1, mode = 1, ld = 1;
    wire qcc;
    reg [3:0] abcd = 2;
    wire [3:0] q;
    mod1 _1(abcd, clk, clr, mode, ld, qcc, q);

    initial forever #1 clk = ~clk;
    initial begin
        #20 clr = 0;
        #2 clr = 1;
        #30 ld = 0;
        #2 ld = 1;
        #40 mode = 0;
        #80 mode = 1;
    end
endmodule
