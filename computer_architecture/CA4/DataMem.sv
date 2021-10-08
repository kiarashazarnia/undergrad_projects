module DataMem(
    input clk,
    input[7:0] address,
    input[7:0] data,
    input store,
    output logic[7:0] out
);
    logic[7:0] word[255:0];
    initial begin
        /*case 1 0000010000000001 + 0000010100000001 = 0000011000000101*/
         word[100] = 8'b00000001;
         word[101] = 8'b00000001;
         word[102] = 8'b00000100;
         word[103] = 8'b00000101;
        /*case 2*/
        //word[100] = 8'b00000001;
        //word[101] = 8'b00000001;
        //word[102] = 8'b00000100;
        //word[103] = 8'b00000101;
        //word[104] = 8'b00000001;
        //word[105] = 8'b00000001;
        //word[106] = 8'b00000100;
        //word[107] = 8'b00000101;
        //word[108] = 8'b00000001;
        //word[109] = 8'b00000001;
        //word[110] = 8'b00000100;
        //word[111] = 8'b00000101;
        //word[112] = 8'b00000001;
        //word[113] = 8'b00000001;
        //word[114] = 8'b00000100;
        //word[115] = 8'b00000101;
        //word[116] = 8'b11000001;
        //word[117] = 8'b00000001;
        //word[118] = 8'b00000100;
        //word[119] = 8'b10000101;
    end
    always_comb begin
        out <= word[address];
    end

    always@(posedge clk) begin
        if (store) begin
            word[address] <= data;
        end
    end
endmodule
