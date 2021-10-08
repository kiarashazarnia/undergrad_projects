module Accumulator(
	input clk,
	input rst,
    input AcWen,
	input[1:0] AcAdr1,
	input[1:0] AcAdr2,
	input[1:0] WrAdr,
	input[7:0] WrData,
	output[7:0] Ac1,
	output[7:0] Ac2);
	
	const logic [7:0] zero = 8'b0;
	logic [7:0] Acc[3:0];

	always@(posedge clk or posedge rst) begin: writing
		if(rst)
			Acc <= {zero,zero,zero,zero};			
		if(AcWen)
			Acc[WrAdr] <= WrData;
	end

	assign Ac1 = Acc[AcAdr1];
	assign Ac2 = Acc[AcAdr2];
    
endmodule