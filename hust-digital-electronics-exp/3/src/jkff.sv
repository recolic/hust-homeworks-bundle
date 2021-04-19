
module jkff(clk, j, k, q, notq);
    input clk;
    input j, k;
    output reg q;
    output notq;
    
    assign notq = ~q;
    
    initial begin
        q = 0;
    end
    
    always @(negedge clk)
    begin
        case({j, k})
            2'b00 : q <= q;
            2'b01 : q <= 0;
            2'b10 : q <= 1;
            2'b11 : q <= ~q;
        endcase
    end
endmodule