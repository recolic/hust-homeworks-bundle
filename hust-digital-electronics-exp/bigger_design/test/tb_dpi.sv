// https://en.wikipedia.org/wiki/SystemVerilog_DPI
module tb_dpi;

  import "DPI-C" function int _add();
  import "DPI-C" function int sleep(input int secs);
  int j;
  
  initial
  begin
    $display("Entering in SystemVerilog Initial Block");
    #20
    j = _add();
    $display("Value of J = %d", j);
    $display("Sleeping for 3 seconds with Unix function");
    sleep(3);
    $display("Exiting from SystemVerilog Initial Block");
    #5 $finish;
  end

endmodule