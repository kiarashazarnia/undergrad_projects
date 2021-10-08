module DataMem(
    input clk,
    input[7:0] address,
    input[7:0] data,
    input store,
    output logic[7:0] out
);
    logic[7:0] sector[255:0];
    initial begin
        /*case 1 0000010000000001 + 0000010100000001 = 0000100100000010*/
        // sector[100] = 8'b10000001;
        // sector[101] = 8'b00000001;
        // sector[102] = 8'b10000100;
        // sector[103] = 8'b00000101;
        /*case 2*/
        sector[100] = 1;
        sector[101] = 2;
        sector[102] = 3;
        sector[103] = 4;
        sector[104] = 5;
        sector[105] = 6;
        sector[106] = 7;
        sector[107] = 8;
        sector[108] = 9;
        sector[109] = 10;
        sector[110] = 11;
        sector[111] = 15;
        sector[112] = 14;
        sector[113] = 13;
        sector[114] = 12;
        sector[115] = 10;
        sector[116] = -8;
        sector[117] = 10;
        sector[118] = 1;
        sector[119] = 10;
    end
    always_comb begin
        out <= sector[address];
    end

    always@(posedge clk) begin
        if (store) begin
            sector[address] <= data;
        end
    end
endmodule
