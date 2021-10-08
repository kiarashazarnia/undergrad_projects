module InsMemory (
	input[11:0]  address,
	output[18:0]  ins_out
);
	logic[18:0] instruction [4095:0];
    initial begin
		/*case 1*/
    	// instruction[1] = 19'b1000000100001100100;
		 instruction[2] = 19'b1000001000001100110;
		 instruction[3] = 19'b0000001100101000000;
		 instruction[4] = 19'b1000101100001101000;
		 instruction[5] = 19'b1000000100001100101;
		 instruction[6] = 19'b1000001000001100111;
		 instruction[7] = 19'b0000101100101000000;
		 instruction[8] = 19'b1000101100001101001;
		/*case 2*/
		//instruction[1] = 19'b0000011100000000000;
		//instruction[2] = 19'b0000000100000000000;
		//instruction[3] = 19'b0101001100100010100;
		//instruction[4] = 19'b1010000000000001011;
		//instruction[5] = 19'b1000001000101100100;
		//instruction[6] = 19'b0001001111101000000;
		//instruction[7] = 19'b1011100000000001001;
		//instruction[8] = 19'b0000011101000000000;
		//instruction[9] = 19'b0100000100100000001;
		//instruction[10] = 19'b1110000000000000011;
    end
	assign ins_out = instruction[address];
endmodule
