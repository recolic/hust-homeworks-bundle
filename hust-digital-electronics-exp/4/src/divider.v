/*
 * Copyright 2018-2018 Recolic Keghart <root@recolic.net>
 * Licensed under GPL 3.0
 */

module divider(clk, clk_N);
input clk;
output reg clk_N;

parameter N = 100_000_000; // times,N=fclk/fclk_N
//reg [31:0] counter;
integer counter;
always @(posedge clk)  begin
    if(counter == N/2 - 1)
    begin
        clk_N <= ~clk_N;
        counter <= 0;
    end
    else 
        counter <= counter + 1;
end
endmodule

