

module tff(
    input T,
    input clk,
    output reg Q
    );
    always @(posedge clk)
    begin
        if(T)
            Q <= ~Q;
    end
endmodule
