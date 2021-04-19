`timescale 1ns / 1ps
`include "macro.vh"

module mod3b(
    input sig_nsyn,
    input clk,
    output wire sig_syn
);

wire q0, q1;
`ifdef USE_DIVIDER
wire long_clk;
divider div(clk, long_clk);

dff dff0(sig_nsyn, long_clk, q0);
`else
dff dff0(sig_nsyn, clk, q0);
`endif
dff dff1(q0, clk, q1);
dff dff2(q1, clk, sig_syn);

endmodule // mod3b