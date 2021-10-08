module ALU(
    input Ci,
    input[1:0]  ALUop,
	input[7:0]  a,
	input[7:0]  b,
	output logic[2:0] status,
	output logic [7:0] out);

    parameter[1:0]
            ADD = 2'b00,
            AND = 2'b01,
            OR =  2'b10;

    logic Cout;
    logic Zero;
    logic Neg;

    always_comb begin
        {Zero, Neg, Cout} = 0;
        case(ALUop)
        ADD:    {Cout, out} = a + b + Ci;
        AND:    out = a & b;
        OR:     out = a | b;
        default: out = 8'bz; 
        endcase
        Zero = out == 0;
        Neg = out < 0;
    end

    assign status = {Cout, Zero, Neg};
endmodule

module Incrementer13(input[12:0] in, output[12:0] out);
    assign out = in + 1;
endmodule