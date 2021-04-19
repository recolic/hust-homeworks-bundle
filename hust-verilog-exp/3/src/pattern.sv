`timescale 1ns / 1ps

module pattern(
    input [3:0] code,
    output wire [7:0] seg
);

assign seg = (code == 0) ? 8'b11000000 :
(code == 1) ? 8'b11111001 :
(code == 2) ? 8'b10100100 :
(code == 3) ? 8'b10110000 :
(code == 4) ? 8'b10011001 :
(code == 5) ? 8'b10010010 :
(code == 6) ? 8'b10000010 :
(code == 7) ? 8'b11111000 :
(code == 8) ? 8'b10000000 :
(code == 9) ? 8'b10011000 :
(code == 10) ? 8'b10001000 :
(code == 11) ? 8'b10000011 :
(code == 12) ? 8'b11000110 :
(code == 13) ? 8'b10100001 :
(code == 14) ? 8'b10000110 :
(code == 15) ? 8'b10001110 : 0;

endmodule

