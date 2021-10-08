module shifter(
    input[1:0] fn,
    input[2:0] shiftCount,
    input[7:0] in,
    output logic sh_Cout,
    output sh_Zout,
    output logic[7:0] out
);

    parameter[1:0] 
        SHL = 0,
        SHR = 1,
        ROL = 2,
        ROR = 3;
    always_comb begin
        sh_Cout = 0;
        case (fn)
            SHL:    {sh_Cout, out} = in << shiftCount;
            SHR:    {out, sh_Cout} = in >> shiftCount;
            ROL: begin
                case(shiftCount)
                0: out <= in;
                1: out <= {in[6:0], in[7:7]};
                2: out <= {in[5:0], in[7:6]};
                3: out <= {in[4:0], in[7:5]};
                4: out <= {in[3:0], in[7:4]};
                5: out <= {in[2:0], in[7:3]};
                6: out <= {in[1:0], in[7:2]};
                7: out <= {in[0:0], in[7:1]};
                endcase
            end
            ROR: begin
                case(shiftCount)
                0: out <= in;
                1: out <= {in[0:0], in[7:1]};
                2: out <= {in[1:0], in[7:2]};
                3: out <= {in[2:0], in[7:3]};
                4: out <= {in[3:0], in[7:4]};
                5: out <= {in[4:0], in[7:5]};
                6: out <= {in[5:0], in[7:6]};
                7: out <= {in[6:0], in[7:7]};
                endcase
            end
        endcase
    end
    assign sh_Zout = 0;
endmodule