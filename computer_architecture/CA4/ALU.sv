module ALU(
    input Ci,
    input[2:0]  ALUop,
	input[7:0]  a,
	input[7:0]  b,
	output logic Cout, Zout,
	output logic [7:0] out);

    parameter[2:0]
        ADD = 0,
        ADDC = 1,
        SUB = 2,
        SUBC = 3,
        AND = 4,
        OR  = 5,
        XOR = 6,
        MASK = 7;

    always_comb begin
        {Zout, Cout} = 0;
        case(ALUop)
        ADD : {Cout, out} = a + b;
        ADDC: {Cout, out} = a + b + Ci;
        SUB : {Cout, out} = a - b;
        SUBC: {Cout, out} = a - b + Ci;
        AND : out = a & b;
        OR  : out = a | b;
        XOR : out = a ^ b;
        MASK: out = a & ~b;
        default: out = 8'bz; 
        endcase
        Zout = out == 0;
    end

endmodule

module Incrementer12(input[11:0] in, output[11:0] out);
    assign out = in + 1;
endmodule

module Adder12(input[11:0] a, b, output[11:0] out);
    assign out = a + b;
endmodule

module SignExt8to12(
    input[7:0] in,
    output[11:0] out);
    assign out = {in[7], in};
endmodule