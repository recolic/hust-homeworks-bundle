`include "macro.vh"

module mod1 (
    input [3:0] abcd,
    input clk,
    input clr,
    input mode,
    input ld,
    output reg qcc,
    output reg [3:0] q
);
    initial begin
        q <= abcd;
    end
`ifdef USE_DIVIDER
    wire long_clk;
    divider __01(clk, long_clk);
    always @(posedge long_clk) begin
`else
    always @(posedge clk) begin
`endif
        if(ld == 0) begin
            q <= abcd;
            qcc <= 1;
        end else if(clr == 0) begin
            q <= 0;
            qcc <= 1;
        end else if(mode == 1) begin
            if(q == 15 || q == 7) // Warning: fit mod1b
                qcc <= 0;
            else
                qcc <= 1;
            q <= q + 1;
        end else if(mode == 0) begin
            if(q == 0 || q == 8) // Warning: fit mod1b
                qcc <= 0;
            else
                qcc <= 1;
            q <= q - 1;
        end
    end
endmodule
