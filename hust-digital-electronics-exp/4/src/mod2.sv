`define zero 1'b0
`define one 1'b1
`include "macro.vh"

module mod2 (
    input fclk,
    input val,
    output wire [7:0] status_view,
    output reg flag
);
    reg [4:0] seq = 5'b01101; // reversed 10110
    integer curr_status = 0;
    assign status_view = curr_status;
    always @(posedge fclk) begin
        if(val == seq[curr_status]) begin
            if(curr_status == 4) begin
                flag <= 1;
                curr_status <= 0;
            end else begin
                curr_status <= curr_status + 1;
                flag <= 0;
            end
        end else begin
            flag <= 0;
            case(curr_status)
                0:
                    curr_status <= 0;
                1:
                    curr_status <= 1;
                2:
                    curr_status <= 0;
                3:
                    curr_status <= 2;
                4:
                    curr_status <= 1;
            endcase
        end
    end

endmodule