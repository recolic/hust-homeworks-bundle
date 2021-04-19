
/******************************************************************
 * Date: Aug. 28, 1999
 * File: Decoder 3 to 8.v (440 Examples)
 *
 * Module of a 3 to 8 Decoder with an active high enable input and
 * and active low outputs. This model uses a trinary continuous
 * assignment statement for the combinational logic
 *******************************************************************/
//*****************************************************************
module decoder3to8(num, sel);
//*****************************************************************
input [2:0] num;
output wire [7:0] sel;
assign sel = ( num == 3'b000) ? 8'b1111_1110 :
 ( num == 3'b001) ? 8'b1111_1101 :
 ( num == 3'b010) ? 8'b1111_1011 :
 ( num == 3'b011) ? 8'b1111_0111 :
 ( num == 3'b100) ? 8'b1110_1111 :
 ( num == 3'b101) ? 8'b1101_1111 :
 ( num == 3'b110) ? 8'b1011_1111 :
 ( num == 3'b111) ? 8'b0111_1111 :
 8'b1111_1111;


endmodule
