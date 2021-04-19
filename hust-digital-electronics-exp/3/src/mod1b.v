`timescale 1ns / 1ps
`include "macro.vh"

module mod1b(
    input clk,
    input _i,
    output wire _o
);

wire q0, q1;
wire one;
assign one = 1'b1;

`ifdef USE_DIVIDER
wire long_clk;
divider div(clk, long_clk);

tff tff1(one, long_clk, q0);
tff tff2(_i^q0, long_clk, q1);
`else
tff tff1(one, clk, q0);
tff tff2(_i^q0, clk, q1);
`endif
assign _o = _i & ~q1;

endmodule // mod1b