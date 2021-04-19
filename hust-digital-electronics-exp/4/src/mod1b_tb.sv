`timescale 1ns / 1ps

module mod1b_tb (
    
);
    reg clk = 0;
    reg mode = 1;
    wire qcc;
    wire [3:0] q;
    mod1b _(clk, mode, q, qcc);
    initial forever #1 clk = ~clk;
    initial #40 mode = 0;
endmodule

