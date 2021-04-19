`include "global.svh"

module shopping (
    input logic rst,
    input logic clk,
    input logic startBtn,
    input money_t sigCash,
    input item_t selProduct,
    input logic cancelBtn,
    output state_t state,
    output logic drinkReady,
    // state is {running, occupied, drinkReady, refundReady}
    output int balance
    // connected to number output. Unit: cent
);

    int cash; // tmpVar
    bit moneyEnough; // tmpVar
    money_t sigCashOld = CNY_NULL;
    item_t selProductOld = ITEM_NULL;

    bit [7:0] clk_fucker = 0;
    always @(posedge clk) begin
`ifndef XILINX_ISIM
// disable divider on simulation
        clk_fucker <= clk_fucker + 1;
`endif
        if(clk_fucker == 0) begin
        if(rst) begin
            state <= STATE_OFF;
            balance <= 99999; // shows ----
        end else
        case(state) inside
            STATE_OFF: fork
                state <= STATE_ON;
                balance <= 9999; // shows helo
                drinkReady <= 0;
            join
            STATE_ON, STATE_REFUND:
                if(startBtn) fork
                    state <= STATE_OCCUPIED;
                    balance <= 0;
                    drinkReady <= 0;
                join
            STATE_OCCUPIED:
                if(cancelBtn) fork
                    state <= STATE_TEMP; // tip: no latency
                join else begin
                    // Not canceled
                    if(balance > 499) fork
                        state <= STATE_MONEY_GE_5;
                    join else if(balance > 249) fork
                        state <= STATE_MONEY_GE_3;
                    join else if(sigCash != CNY_NULL && sigCashOld == CNY_NULL) fork
                        // Inserting cash
                        cashToPrice(sigCash, cash);
                        balance <= balance + cash;
                    join
                end
            STATE_MONEY_GE_3:
                if(cancelBtn) fork
                    state <= STATE_TEMP; // tip: no latency
                join else begin
                    // Not canceled
                    if(balance < 249) fork
                        state <= STATE_OCCUPIED;
                    join else if (balance > 499) fork
                        state <= STATE_MONEY_GE_5;
                    join else if(sigCash != CNY_NULL && sigCashOld == CNY_NULL) fork
                        // Inserting cash
                        cashToPrice(sigCash, cash);
                        balance <= balance + cash;
                    join else if(selProduct != ITEM_NULL && selProductOld == ITEM_NULL) fork
                        // purchasing
                        fuck_balance(selProduct, balance, drinkReady);
                    join
                end
            STATE_MONEY_GE_5:
                if(cancelBtn) fork
                    state <= STATE_TEMP; // tip: no latency
                join else begin
                    // Not canceled. Deal with QiongBi first.
                    if(balance < 249) fork
                        state <= STATE_OCCUPIED;
                    join else if(balance < 499) fork
                        state <= STATE_MONEY_GE_3;
                    join else if(sigCash != CNY_NULL && sigCashOld == CNY_NULL) fork
                        // Inserting cash
                        cashToPrice(sigCash, cash);
                        balance <= balance + cash;
                    join else if(selProduct != ITEM_NULL && selProductOld == ITEM_NULL) fork
                        // purchasing
                        fuck_balance(selProduct, balance, drinkReady);
                    join
                end
           STATE_TEMP:
                if(balance != 0)
                    state <= STATE_REFUND;
                else
                    state <= STATE_ON;
            default: begin end
        endcase

        sigCashOld <= sigCash;
        selProductOld <= selProduct;
        end
    end

    task automatic cashToPrice(input money_t sig, output int cash);
        case(sig)
            CNY_NULL:
                cash = 0;
            CNY_1:
                cash = 100;
            CNY_10:
                cash = 1000;
            default:
                cash = 9999;
        endcase
    endtask //automatic

    task automatic fuck_balance(input item_t purchased, ref int balance, ref logic ok);
        int price;
        itemToPrice(purchased, price);
        if(balance < price)
            ok = 0;
        else begin
            ok = 1;
            balance = balance - price;
        end
    endtask //automatic

    task automatic itemToPrice(input item_t item, output int price);
        // if the price is 12.34, it must return price=1234
        case(item)
            ITEM_PRICED_2p5:
                price = 250;
            ITEM_PRICED_5:
                price = 500;
            ITEM_NULL:
                price = 0;
            default:
                price = 7777;
        endcase
    endtask //automatic
/* Fucking vivado failed to simulate these code
    function cashToPrice(input money_t sig);
        case(sig)
            CNY_NULL:
                return 0;
            CNY_1:
                return 100;
            CNY_10:
                return 1000;
            default:
                return 9999;
        endcase
    endfunction

    task automatic fuck_balance(input item_t purchased, ref int balance, ref bit ok);
        int price;
        price = itemToPrice(purchased);
        if(balance < price)
            ok = 0;
        else begin
            ok = 1;
            balance = balance - price;
        end
    endtask //automatic

    function itemToPrice(input item_t item);
        // if the price is 12.34, it must return price=1234
        case(item)
            ITEM_PRICED_2p5:
                return 250;
            ITEM_PRICED_5:
                return 500;
            ITEM_NULL:
                return 0;
            default:
                return 7777;
        endcase
    endfunction
*/    
endmodule