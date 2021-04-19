`timescale 1ns / 1ps

module main (
    input clk,
    input rst,
    input start,
    output reg [7:0] seg,
    output reg [7:0] an
);

wire [7:0] res;
wire long_clk;

divider _1(clk, long_clk);
adder _2(long_clk, rst, start, res);
seg_updater _3(clk, res, seg, an);
    
endmodule

