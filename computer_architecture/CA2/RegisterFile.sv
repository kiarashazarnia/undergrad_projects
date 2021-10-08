module RegisterFile (
	input clk,
	input rst,
	input[2:0]  reg1,
	input[2:0]  reg2,
	input[2:0]  regw,
	input[7:0]  write,
	input       regWrite,
	output[7:0] read1,
	output[7:0] read2);

	const logic [7:0] zero = 8'b0;
	logic [7:0] register[7:0];
	initial begin
		register[0] = zero;	
	end
	always@(posedge clk or posedge rst) begin: writing
		if(rst)
			register <= {zero,zero,zero,zero,zero,zero,zero,zero};
		if(regWrite)
			register[regw] <= write;
	end
	assign read1 = register[reg1];
	assign read2 = register[reg2];
endmodule
