`timescale 1ns / 1ps

module dynamic_scan(clk,  seg, an);
input clk;              // ϵͳʱ��
output wire [7:0] seg;  		// �ֱ��ӦCA��CB��CC��CD��CE��CF��CG��DP
output wire [7:0] an;        // 8λ�����Ƭѡ�ź�

wire [2:0] num;
wire [3:0] rom_dat;
better_counter bt(clk, num);
decoder3to8 d38(num, an);
rom_32b r(num, rom_dat);
pattern pt(rom_dat, seg);


endmodule

