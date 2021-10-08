module stack (
	input        clk, rst,
	input        pop,
	input        push,
	input[11:0]  inp,
	output logic[11:0] out);

	logic[11:0] address[7:0];
	logic[3:0] head;

	always@(posedge clk or posedge rst) begin : proc_wire
		if(rst)
			head = 0;

        else if(push) begin
			address[head] = inp;
			head = head + 1;
		end

        else if(pop) begin
			out = address[head - 1];
			head = head - 1;
		end
	end
endmodule
