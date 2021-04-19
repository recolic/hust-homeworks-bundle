`timescale 1ns / 1ps

module mod2_tb (
    
);
    reg clk=0, val=0;
    wire flag;
    mod2 _1(clk, val, flag);

    initial forever #1 clk = ~clk;
    initial begin
        #2 val = 1;
        #2 val = 0;
        #2 val = 1;
        #2 val = 0;
        #2 val = 1;
        #2 val = 1;
        #2 val = 0;
        #2 val = 1;
        #2 val = 1;
        #2 val = 0;
    end
endmodule
