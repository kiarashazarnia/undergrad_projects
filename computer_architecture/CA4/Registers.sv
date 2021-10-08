module Register1(
                input clk,
                input rst,
                input in,
                output logic out);
    always@(posedge clk, posedge rst)
        if(rst)
            out <= 0;
        else
            out <= in;
endmodule

module Register8(
                input clk,
                input rst,
                input[7:0] in,
                output logic[7:0] out);
    always@(posedge clk, posedge rst)
        if(rst)
            out <= 0;
        else
            out <= in;
endmodule

module Register3(
                input clk,
                input rst,
                input[2:0] in,
                output logic[2:0] out);
    always@(posedge clk, posedge rst)
        if(rst)
            out <= 0;
        else
            out <= in;
endmodule

module Register12(
                input clk,
                input rst,
                input[11:0] in,
                output logic[11:0] out);
    always@(posedge clk, posedge rst)
        if(rst)
            out <= 0;
        else
            out <= in;
endmodule

module Register13(
                input clk,
                input rst,
                input[12:0] in,
                output logic[12:0] out);
    always@(posedge clk, posedge rst)
        if(rst)
            out <= 0;
        else
            out <= in;
endmodule

module Register19(
                input clk,
                input rst,
                input[18:0] in,
                output logic[18:0] out);
    always@(posedge clk, posedge rst)
        if(rst)
            out <= 0;
        else
            out <= in;
endmodule
