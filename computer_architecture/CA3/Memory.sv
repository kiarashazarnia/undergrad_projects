module DataMem(
    input clk,
    input[7:0] WriteData,
    input[12:0] Address,
    input MemWen,
    output logic[7:0] ReadData
);

    byte word[8191:0];
    // byte is 8'bit signed number

    always_comb begin
        ReadData <= word[Address];
    end

    always@(posedge clk) begin
        if (MemWen) begin
            word[Address] <= WriteData;
        end
    end

    initial begin
        // Instructions
        word[0] = 8'b11101000;
        word[1] = 8'b00000011;
        word[2] = 8'b11101000;
        word[3] = 8'b01000011;
        word[4] = 8'b11101001;
        word[5] = 8'b00100011;
        word[6] = 8'b11110010;
        word[7] = 8'b10011100;
        word[8] = 8'b00000011;
        word[9] = 8'b11101010;
        word[10] = 8'b01000011;
        word[11] = 8'b11110010;
        word[12] = 8'b00100011;
        word[13] = 8'b11110011;
        word[14] = 8'b10011100;
        word[15] = 8'b00000011;
        word[16] = 8'b11101011;
        word[17] = 8'b01000011;
        word[18] = 8'b11110011;
        word[19] = 8'b00100011;
        word[20] = 8'b11110100;
        word[21] = 8'b10011100;
        word[22] = 8'b00000011;
        word[23] = 8'b11101100;
        word[24] = 8'b01000011;
        word[25] = 8'b11110100;
        word[26] = 8'b00100011;
        word[27] = 8'b11110101;
        word[28] = 8'b10011100;
        word[29] = 8'b00000011;
        word[30] = 8'b11101101;
        word[31] = 8'b01000011;
        word[32] = 8'b11110101;
        word[33] = 8'b00100011;
        word[34] = 8'b11110110;
        word[35] = 8'b10011100;
        word[36] = 8'b00000011;
        word[37] = 8'b11101110;
        word[38] = 8'b01000011;
        word[39] = 8'b11110110;
        word[40] = 8'b00100011;
        word[41] = 8'b11110111;
        word[42] = 8'b10011100;
        word[43] = 8'b00000011;
        word[44] = 8'b11101111;
        word[45] = 8'b01000011;
        word[46] = 8'b11110111;
        word[47] = 8'b00100011;
        word[48] = 8'b11111000;
        word[49] = 8'b10011100;
        word[50] = 8'b00000011;
        word[51] = 8'b11110000;
        word[52] = 8'b01000011;
        word[53] = 8'b11111000;
        word[54] = 8'b00100011;
        word[55] = 8'b11111001;
        word[56] = 8'b10011100;
        word[57] = 8'b00000011;
        word[58] = 8'b11110001;
        word[59] = 8'b01000011;
        word[60] = 8'b11111001;
        word[61] = 8'b00100011;
        word[62] = 8'b11111010;
        word[63] = 8'b10011100;
        word[64] = 8'b11111000;
        word[65] = 8'b00100111;
        word[66] = 8'b11010001;
        word[67] = 8'b11100000;
        word[68] = 8'b00000011;
        word[69] = 8'b11111010;
        word[70] = 8'b00100111;
        word[71] = 8'b11010000;


        //Data
        word[999] =  0;
        word[1000] = 50;
        word[1001] = 51;
        word[1002] = 52;
        word[1003] = 53;
        word[1004] = 54;
        word[1005] = 55;
        word[1006] = 56;
        word[1007] = 57;
        word[1008] = 58;
        word[1009] = 59;
        // result must be 545 = 010 00100001

    end
endmodule
