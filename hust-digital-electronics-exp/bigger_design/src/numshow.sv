module numshow (
    input clk,
    input int num,
    output logic [7:0] phyPad,
    output wire [7:0] an//,
    //output wire decPoint
);
    wire [31:0] digits [3:0];
    _xilinx_bug_433316_workaround _xil_1(num, digits);
    wire [7:0] digits_7s [3:0];
    bit [1:0] cter = 0;
    int cterShowNextDigit = 0;
    //assign decPoint = 1;
    cterToAn _2(cter, an);
    digitToPhy _3(digits[3], digits_7s[2]);
    digitToPhyWithPt _4(digits[2], digits_7s[1]);
    digitToPhy _5(digits[1], digits_7s[0]);
    digitToPhy _6(digits[0], digits_7s[3]);

    always @(posedge clk) begin
`ifdef XILINX_ISIM
        // disable inline divider
        cterShowNextDigit <= 32000;
`else
        cterShowNextDigit <= cterShowNextDigit + 1;
`endif
        if(cterShowNextDigit == 32000) fork
           cter <= cter + 1;
           phyPad <= digits_7s[cter];
           cterShowNextDigit <= 0;
        join
    end

endmodule

module _xilinx_bug_433316_workaround(
    input int num,
    output wire [31:0] digits [3:0]
);
    assign digits = '{
        num>9999?20: num==9999?16: num/1000%10, 
        num>9999?20: num==9999?17: num/100%10, 
        num>9999?20: num==9999?18: num/10%10, 
        num>9999?20: num==9999?19: num/1%10
    };
    // if num > 9999, we must print `----`. This is why I give 20 > 19.
    // if num = 9999, we must print `helo`
    /* Reproduce:
       wire [31:0] digits [3:0] = num > 9999 ? '{20, 20, 20, 20} : 
                                  num== 9999 ? '{16, 17, 18, 19} : 
                                  '{num/1000%10, num/100%10, num/10%10, num/1%10};
    */
endmodule

module cterToAn (
    input wire [1:0] cter,
    output wire [7:0] an
);
    assign an = (cter == 0) ? 8'b11111110 :
                (cter == 1) ? 8'b11111101 :
                (cter == 2) ? 8'b11111011 :
                (cter == 3) ? 8'b11110111 : 8'b00001111;
endmodule

module digitToPhy (
    input wire [31:0] digit,
    output wire [7:0] phy
);
    // 0 1 2 3 4 5 6 7 8 9 a  b  c  d  e  f  h  e  l  o  -
    // 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 Error
    assign phy = 
                (digit == 0) ? 8'b11000000 :
                (digit == 1) ? 8'b11111001 :
                (digit == 2) ? 8'b10100100 :
                (digit == 3) ? 8'b10110000 :
                (digit == 4) ? 8'b10011001 :
                (digit == 5) ? 8'b10010010 :
                (digit == 6) ? 8'b10000010 :
                (digit == 7) ? 8'b11111000 :
                (digit == 8) ? 8'b10000000 :
                (digit == 9) ? 8'b10010000 :
                (digit == 10) ? 8'b10001000 :
                (digit == 11) ? 8'b10000011 :
                (digit == 12) ? 8'b11000110 :
                (digit == 13) ? 8'b10100001 :
                (digit == 14) ? 8'b10000110 :
                (digit == 15) ? 8'b10001110 : 
                (digit == 16) ? 8'b10001011 : 
                (digit == 17) ? 8'b10000110 : 
                (digit == 18) ? 8'b11000111 : 
                (digit == 19) ? 8'b10100011 : 
                8'b10111111;
endmodule

module digitToPhyWithPt (
    input wire [31:0] digit,
    output wire [7:0] phy
);
    assign phy[7] = 0;
    wire [7:0] joined;
    assign phy[6:0] = joined[6:0];
    digitToPhy _i1(digit, joined);
endmodule
