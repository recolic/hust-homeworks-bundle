`timescale 1ns / 1ps

module seg_updater (
    input clk,
    input [7:0] num32,
    output reg [7:0] seg,
    output reg [7:0] an
);

    wire [7:0] dec_dig [7:0];
    wire [7:0] seg_memory [7:0];

    assign dec_dig[0] = num32 % 10;
    assign dec_dig[1] = num32 / 10 % 10;
    assign dec_dig[2] = num32 / 100 % 10;
    assign dec_dig[3] = num32 / 1000 % 10;
    assign dec_dig[4] = num32 / 10000 % 10;
    assign dec_dig[5] = num32 / 100000 % 10;
    assign dec_dig[6] = num32 / 1000000 % 10;
    assign dec_dig[7] = num32 / 10000000 % 10;

    pattern _0(dec_dig[0], seg_memory[0]);
    pattern _1(dec_dig[1], seg_memory[1]);
    pattern _2(dec_dig[2], seg_memory[2]);
    pattern _3(dec_dig[3], seg_memory[3]);
    pattern _4(dec_dig[4], seg_memory[4]);
    pattern _5(dec_dig[5], seg_memory[5]);
    pattern _6(dec_dig[6], seg_memory[6]);
    pattern _7(dec_dig[7], seg_memory[7]);

    reg [2:0] cter;
    initial
        cter = 0;
    decoder3to8 __0(cter, an);
    always @(posedge clk) begin
        cter <= cter + 1;
        seg <= seg_memory[cter];
    end
    
endmodule