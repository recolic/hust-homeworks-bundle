`timescale 1ns / 1ps

`define fsm_out {ld_sum, ld_next, sum_sel, next_sel, a_sel, done}
`define fsm_in {rst, start, next_zero}
`define fsm_register_state(_state, _out_union) _state: fsm_out <= _out_union

module fsm(
    input clk,
    input rst,
    input start,
    input next_zero,
    output reg ld_sum,
    output reg ld_next,
    output reg sum_sel,
    output reg next_sel,
    output reg a_sel,
    output reg done
);
    typedef enum logic [1:0] {st_start, st_compute_sum, st_get_next, st_done} state_t;

    state_t state;
    always @(posedge clk)
    begin
        case(state)
            st_start: 
                `fsm_out <= 6'b000000;
            st_compute_sum: 
                `fsm_out <= 6'b101110;
            st_get_next: 
                `fsm_out <= 6'b011100;
            st_done: 
                `fsm_out <= 6'b000001;
        endcase

        //task automatic determine_state(input state_t curr, input rst, input start, input next_zero);
        if (rst || !start) begin
            state <= st_start;
        end
        else begin
            case(state)
                st_start:
                    if(start)
                        state <= st_compute_sum;
                st_compute_sum:
                    state <= st_get_next;
                st_get_next:
                    if(next_zero)
                        state <= st_done;
                    else
                        state <= st_compute_sum;
            endcase
        end
    end
endmodule
