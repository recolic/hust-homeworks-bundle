

module adder (
    input clk,
    input rst,
    input start,
    output reg [7:0] sum
);

typedef reg [7:0] addr8_t;
typedef reg [7:0] data8_t;

logic done;
addr8_t ptr;

`define nullptr 8'hff
data8_t ram [1023:0];

initial begin
    ptr = 0;
    sum = 0;
    `include "ram.init.vh"
end

always @(posedge clk) begin
    if(rst) begin
        ptr <= 0;
        sum <= 0;
    end else if(start && ptr != `nullptr) begin
        sum = sum + ram[ptr + 1];
        ptr = ram[ptr];
    end
end

endmodule



