module mux2x8bit (
	input[7:0]  a,
	input[7:0]  b,
	input       sel,
	output[7:0] out
);
	assign out = sel ? b:a;
endmodule

module mux3x8bit (
	input[7:0]  a,
	input[7:0]  b,
    input[7:0]  c,
	input[1:2]  sel,
	output logic[7:0] out
);
	always_comb
        case(sel)
		2'b00:
            out = a;
    	2'b01:
            out = b;
        2'b10:
            out = c;
        default:
            out = 2'bzz;
	endcase
endmodule

module mux2x13bit (
	input[12:0]  a,
	input[12:0]  b,
	input       sel,
	output[12:0] out
);
	assign out = sel ? b:a;
endmodule

module mux2x2bit (
	input[1:0]  a,
	input[1:0]  b,
	input       sel,
	output[1:0] out
);
	assign out = sel ? b:a;
endmodule

module mux2x1bit(
	input a,
	input b,
	input sel,
	output out
);
	assign out = sel ? b:a;
endmodule