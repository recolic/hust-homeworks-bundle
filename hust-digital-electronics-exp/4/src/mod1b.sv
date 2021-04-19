`include "macro.vh"
module mod1b (
    input clk,
    input mode,
    output wire [3:0] q,
    output wire qcc
);
    wire [3:0] _q;
    wire [3:0] __q;

    mod1 _1(0, clk, 1, mode, 1, qcc, _q);
    assign __q[2:0] = _q[2:0];
    assign __q[3] = 0;
    assign q = __q + 2;
endmodule