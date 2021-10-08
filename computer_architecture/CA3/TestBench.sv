`timescale 1ns/1ns

module A_TestBench();

    logic clk, rst;
    Proccessor proccessor_u (clk, rst);

    initial begin
        clk = 0;
        rst = 0;
        #30
        rst = 1;
        #30
        rst = 0;
    end

	initial repeat(1000)#10 clk = ~clk;
endmodule
