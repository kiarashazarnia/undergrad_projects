module Register8(input clk, rst, Wen,
                input[7:0] in,
                output logic[7:0] out);
    always_ff@(posedge clk, posedge rst) begin
        if(rst)
            out <= 0;
        else
            out <= Wen? in : out;
    end
endmodule

module Register13(input clk, rst, Wen,
                input[12:0] in,
                output logic[12:0] out);
    always_ff@(posedge clk, posedge rst) begin
        if(rst)
            out <= 0;
        else
            out <= Wen? in : out;
    end
endmodule

module Register5(input clk, rst, Wen,
                input[4:0] in,
                output logic[4:0] out);
    always_ff@(posedge clk, posedge rst) begin
        if(rst)
            out <= 0;
        else
            out <= Wen? in : out;
    end
endmodule

module Register3(input clk, rst, Wen,
                input[2:0] in,
                output logic[2:0] out);
    always_ff@(posedge clk, posedge rst) begin
        if(rst)
            out <= 0;
        else
            out <= Wen? in : out;
    end
endmodule