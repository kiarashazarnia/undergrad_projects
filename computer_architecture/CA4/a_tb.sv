`timescale 1ns/1ns
module TB();

    logic clk, rst;

    CPU cpu_u( clk, rst);

    initial begin
        clk = 0;
        rst = 0;
        #30
        rst = 1;
        #30
        rst = 0;
    end

    initial begin
        #60
        repeat(1000)#10 clk = ~clk;
    end

endmodule
