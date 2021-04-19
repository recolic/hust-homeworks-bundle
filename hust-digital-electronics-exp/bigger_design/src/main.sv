`include "global.svh"
module main (
    input rst,
    input clk,
    input startBtn,
    input money_t sigCash,
    input item_t selProduct,
    input cancelBtn,
    output state_t status,
    output wire drinkReady,
    output wire [7:0] refundAmount,
    output wire [7:0] an
);
    wire [31:0] balance;
    numshow _m1(clk, balance, refundAmount, an);
    // startBtn is CPURESET btn so it must be reversed
    shopping _m2(rst, clk, ~startBtn, sigCash, selProduct, cancelBtn, status, drinkReady, balance);

// Fucking vivado simulator forbits to cast any other type to sv enum.
// I have to use its register type everywhere!!!!!
endmodule
