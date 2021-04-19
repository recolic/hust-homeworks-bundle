`include "global.svh"
module main_tb (
    
);
    logic rst=0;
    logic clk=0;
    logic startBtn=0;
    money_t sigCash=CNY_NULL;
    item_t selProduct=ITEM_NULL;
    logic cancelBtn=0;
    logic drinkReady=0;
    state_t status=STATE_OFF;
    bit [7:0] refundAmount=0;
    bit [7:0] an=0;
    `SIMU_SET_CLK(clk);
    initial begin
        `SIMU_SET_BTN_ON(startBtn);
        `SIMU_PUSH_MONEY(CNY_1);
        `SIMU_PUSH_MONEY(CNY_1);
        `SIMU_PUSH_ITEM(ITEM_PRICED_2p5);
        `SIMU_PUSH_MONEY(CNY_1);
        `SIMU_PUSH_MONEY(CNY_1);
        `SIMU_PUSH_MONEY(CNY_10);
        `SIMU_PUSH_MONEY(CNY_1);
        `SIMU_PUSH_ITEM(ITEM_PRICED_5);
        `SIMU_PUSH_ITEM(ITEM_PRICED_2p5);
        `SIMU_PUSH_MONEY(CNY_1);
        `SIMU_PUSH_MONEY(CNY_1);
        `SIMU_SET_BTN_ON(cancelBtn);
        `SIMU_SET_BTN_ON(startBtn);
    end
    main _7(rst,clk,startBtn,sigCash,selProduct,cancelBtn,status,drinkReady,refundAmount,an);
 
endmodule