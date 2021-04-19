`ifndef RELE_GLOBAL_SVH_
`define RELE_GLOBAL_SVH_ 1

`timescale 1ns / 1ps
typedef enum bit [1:0] { CNY_1 = 2'b01, CNY_10 = 2'b10, CNY_NULL = 2'b00 } money_t;
typedef enum bit [1:0] { ITEM_PRICED_2p5 = 2'b01, ITEM_PRICED_5 = 2'b10, ITEM_NULL=2'b00 } item_t;
typedef enum bit [4:0] {
    STATE_OFF        = 5'b00000, 
    STATE_ON         = 5'b10000, 
    STATE_OCCUPIED   = 5'b11000,
    STATE_MONEY_GE_3 = 5'b11001,
    STATE_MONEY_GE_5 = 5'b11011,
    STATE_REFUND     = 5'b10100,
    STATE_TEMP        = 5'b11111
} state_t;
// state is {running, occupied,, refundReady, extraBit1, extraBit2}

`ifdef XILINX_ISIM
`define CHECK_SIMU_MACRO ;
`define SIMU_SET_CLK(clkName) initial forever #1 clkName = ~clkName;
`else
`define CHECK_SIMU_MACRO $error("You're using SIMU macro but you're not setting macro `XILINX_ISIM`. Please add `-d XILINX_ISIM` to vlog compiler options in simulation settings.");
`define SIMU_SET_CLK(clkName) `CHECK_SIMU_MACRO
`endif
`define SIMU_SET_BTN(btnName, valActive, valLazy) `CHECK_SIMU_MACRO #2 btnName = valActive; #2 btnName = valLazy;
`define SIMU_SET_BTN_ON(btnName) `SIMU_SET_BTN(btnName, 1, 0)
`define SIMU_PUSH_MONEY(m) `SIMU_SET_BTN(sigCash, m, CNY_NULL)
`define SIMU_PUSH_ITEM(i) `SIMU_SET_BTN(selProduct, i, ITEM_NULL)

`endif
