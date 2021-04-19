`timescale 1ns / 1ps

module dynamic_scan(clk,  seg, an);
input clk;              // 系统时钟
output wire [7:0] seg;  		// 分别对应CA、CB、CC、CD、CE、CF、CG和DP
output wire [7:0] an;        // 8位数码管片选信号

wire [2:0] num;
wire [3:0] rom_dat;
better_counter bt(clk, num);
decoder3to8 d38(num, an);
rom_32b r(num, rom_dat);
pattern pt(rom_dat, seg);


endmodule

