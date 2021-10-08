module mux2x8bit (
	input[7:0]  a,
	input[7:0]  b,
	input       sel,
	output[7:0] c
);
	assign c = sel ? b:a;
endmodule

module mux2x1bit (
	input a,
	input b,
	input sel,
	output c
);
	assign c = sel ? b:a;
endmodule

module mux4x12bit (
	input[11:0]  a,
	input[11:0]  b,
	input[11:0]  c,
	input[11:0]  d,
	input[1:0]   sel,
	output logic[11:0] e
);
always_comb begin
	if(sel == 2'b00) begin
		e = a;
	end
	else if(sel == 2'b01) begin
		e = b;
	end
	else if(sel == 2'b10) begin
		e = c;
	end
	else if(sel == 2'b11) begin
		e = d;
	end
end
endmodule

module mux4x8bit(
	input[7:0]  a,
	input[7:0]  b,
	input[7:0]  c,
	input[7:0]  d,
	input[1:0]  sel,
	output logic[7:0] e
);
    always_comb begin
        if (sel == 2'b00) begin
            e = a;
        end else if (sel == 2'b01) begin
            e = b;
        end else if (sel == 2'b10) begin
            e = c;
        end else if (sel == 2'b11) begin
            e = d;
        end
    end
endmodule
