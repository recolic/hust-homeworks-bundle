

module tff(
    input T,
    input clk,
    output reg Q
    );
    initial Q = 0;
    always @(posedge clk)
    begin
        if(T)
            Q <= ~Q;
    end
endmodule
