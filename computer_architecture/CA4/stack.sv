module Stack(clk, rst, pop, push, in, out);
	
	input clk, rst, pop, push;
	input[11:0]  in;
	output logic[11:0] out;

	logic[11:0] address[7:0];
	logic[3:0] top;

	always@(posedge clk or posedge rst) begin
		if(rst)
			top <= 0;

        else if(push) begin
			address[top] <= in;
			top <= top + 1;
		end

        else if(pop) begin
			out <= address[top - 1];
			top <= top - 1;
		end
	end
endmodule
