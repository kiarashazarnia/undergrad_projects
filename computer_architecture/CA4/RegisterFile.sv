module RegisterFile(
	input clk,
	input rst,
    input RegWrite,
	input[2:0] adr1,
	input[2:0] adr2,
	input[2:0] WrAdr,
	input[7:0] WrData,
	output[7:0] read1,
	output[7:0] read2);
	
	const logic [7:0] zero = 8'b0;
	logic [6:0] register[7:0];

	always@(posedge clk or posedge rst) begin: writing
		if(rst)
			register <= {zero, zero, zero, zero, zero, zero, zero, zero};			
		if(RegWrite)
			register[WrAdr] <= WrData;
	end

	assign read1 = adr1 == 0? zero : register[adr1];
	assign read2 = adr1 == 0? zero : register[adr2];
    
endmodule