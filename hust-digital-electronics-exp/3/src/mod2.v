`timescale 1ns / 1ps
`include "macro.vh"
`ifndef py

module mod2(
    input clk,
    output reg res
);

integer cter = 0;
`ifdef USE_DIVIDER
wire long_clk;
divider div(clk, long_clk);

always @(posedge long_clk) begin
`else
always @(posedge clk) begin
`endif
    if (cter == 7) begin
        cter <= 0;
        res <= 1'b1;
    end
    else begin
        cter <= cter + 1;
        res <= 1'b0;
    end
end

endmodule // mod2
`else

module mod2(input clk, output res);
`ifdef USE_DIVIDER
    wire _clk;
    divider __01(clk, _clk);
`else
    wire _clk;
    assign _clk = clk;
`endif

    wire o1, o2, o3, o4;
    wire q1, q2, q3, q4, notq4;
    wire j4, in;

    assign res = _clk & q1 & q4;
    assign j4 = q3 & q2;
    assign in = 1;
    assign o1 = q1;
    assign o2 = q2;
    assign o3 = q3;
    assign o4 = q4;
    
    jkff _1(.clk(_clk), .j(in), .k(in), .q(q1));
    jkff _2(.clk(q1), .j(notq4), .k(in), .q(q2));
    jkff _3(.clk(q2), .j(in), .k(in), .q(q3));
    jkff _4(.clk(q1), .j(j4), .k(in), .q(q4), .notq(notq4));
endmodule
`endif