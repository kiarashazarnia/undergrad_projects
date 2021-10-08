module FF(
	input        clk,
	input        rst,
    input        en,
	input        in,
	output logic out);

	always @(posedge clk or posedge rst) begin
		if(rst) begin
			out <= 0;
		end else if(en)
			out <= in;
            else
            out <= out;
	end
endmodule

module PC (
	input        clk,
	input        rst,
	input[11:0]  pcIn,
	output logic[11:0] pcOut);

	always @(posedge clk or posedge rst) begin : proc_pcOut
		if(rst) begin
			pcOut <= 0;
		end else begin
			pcOut <= pcIn;
		end
	end
endmodule
