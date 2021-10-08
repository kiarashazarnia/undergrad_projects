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