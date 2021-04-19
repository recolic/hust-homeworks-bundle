`include "macro.vh"

module mod3 (
    input [2:0] left,
    input [2:0] right,
    output wire left_greater,
    output wire equal,
    output wire left_smaller
);
    assign left_greater = (left > right) ? 1 : 0;
    assign equal = (left == right) ? 1 : 0;
    assign left_smaller = (left < right) ? 1 : 0;
endmodule


`ifdef silly_hust
module mod3s (
    input left,
    input right,
    output wire left_greater,
    output wire equal,
    output wire left_smaller
);
    assign left_greater = (left > right) ? 1 : 0;
    assign equal = (left == right) ? 1 : 0;
    assign left_smaller = (left < right) ? 1 : 0;
endmodule

module mod3p (
    input [2:0] left,
    input [2:0] right,
    output wire left_greater,
    output wire equal,
    output wire left_smaller
);
    wire _1, _2, _3;
    reg [2:0] _4, _5;
    mod3s _0(_4, _5, _1, _2, _3);
    assign left_greater = (left > right) ? 1 : 0;
    assign equal = (left == right) ? 1 : 0;
    assign left_smaller = (left < right) ? 1 : 0;
endmodule
`endif
