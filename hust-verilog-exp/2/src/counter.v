/*
 * Copyright 2018-2018 Recolic Keghart <root@recolic.net>
 * Licensed under GPL 3.0
 */
`timescale 1ns/1ps

module counter(
  _clk, out
);
input _clk;
output reg [2:0] out;

always @(posedge _clk)
begin
  out <= out + 1;
end

endmodule // counter
