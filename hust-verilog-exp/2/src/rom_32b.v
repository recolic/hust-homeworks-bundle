
module rom_32b(
  addr_3b, out_data_4b
);
input [2:0] addr_3b;
output wire [3:0] out_data_4b;

reg [3:0] fake_mem [7:0];
integer i;

initial begin
  fake_mem[0] = 0;
  fake_mem[1] = 2;
  fake_mem[2] = 4;
  fake_mem[3] = 6;
  fake_mem[4] = 8;
  fake_mem[5] = 10;
  fake_mem[6] = 12;
  fake_mem[7] = 14;
  //for(i=0; i<8; i=i+1)
  //  fake_mem[i] = i*2;
  //$display("content=%b", fake_mem[0]);
end

assign out_data_4b = fake_mem[addr_3b];

endmodule // rom_32b
