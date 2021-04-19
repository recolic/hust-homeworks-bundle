`include "global.svh"
module numshow_tb (
    
);
    bit clk = 0;
    int num = 5301;
    bit [7:0] phyPad;
    bit [7:0] an;

    
    `SIMU_SET_CLK(clk);
    numshow _1(clk, num, phyPad, an);
    
endmodule