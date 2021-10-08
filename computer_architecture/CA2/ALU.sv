module ALU(
	input[7:0]  a,
	input[7:0]  b,
	input[2:0]  fn,
	input       carryIn,
	output ALU_Z,
	output logic    ALU_C,
	output logic [7:0] out);

    parameter[2:0]
            ADD = 0,
            ADDC = 1,
            SUB = 2,
            SUBC = 3,
            AND = 4,
            OR = 5,
            XOR = 6,
            MASK = 7;

    always_comb begin
        {out, ALU_C} = 0; 
        case(fn)
        ADD:    {ALU_C, out} = a + b;
        ADDC:   {ALU_C, out} = a + b + carryIn;
        SUB:    {ALU_C, out} = a - b;
        SUBC:   {ALU_C, out} = a - b - carryIn;
        AND:    out = a & b;
        OR:     out = a | b;
        XOR:    out = a ^ b;
        MASK:   out = a & ~b;
        default: {out, ALU_C} = 0;
        endcase
    end

    assign ALU_Z = out == 0;
endmodule