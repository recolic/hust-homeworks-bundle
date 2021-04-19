
module better_counter(
  _clk, out
);
input _clk;
output wire [2:0] out;

wire [7:0] long_clk;
divider d1(_clk, long_clk);
counter cter(long_clk, out);

endmodule // better_counter
