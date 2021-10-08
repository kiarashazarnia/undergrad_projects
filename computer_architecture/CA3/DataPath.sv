module DataPath(
    input clk, rst,
    input PCWen, DirWen, statusWen, MemWen, TempWen, InsWen, AcWen,
    input AcW_mux, Ac1_mux, PC_mux, Cin_mux, ALU_mux1, MemAdr_mux,
    input[1:0] ALU_mux2, ALU_op,
    output logic[3:0] opcode,
    output logic[1:0] jmp_mode,
    output logic[2:0] status);

    logic[12:0] w1, w2, w3;
    logic[4:0] w4;
    logic[7:0] w5;
    logic[12:0] w6, w7;
    logic[7:0] w8, w9, w10, w11, w12;
    logic[2:0] w13; // status
    logic w14, w15;
    logic[1:0] w16, w17;
    logic[7:0] w18;
    logic[4:0] w19;
    logic[1:0] w20;
    logic[7:0] bus;
    logic[1:0] src, dst;

    const logic[7:0] zero8 = 8'b0;

    Register13 PC_u(clk, rst, PCWen, w7, w1);
    Incrementer13 Inc_u(w1, w6);
    mux2x13bit PC_mux_u(w6, w3, PC_mux, w7);
    Register5 Direction_u(clk, rst, DirWen, w4, w19);
    mux2x2bit AcAdr1_mux_u(src, w20, Ac1_mux, w16);
    mux2x2bit WrAdr_mux_u(dst, w20, AcW_mux, w17);
    Accumulator Accumulator_u(clk, rst, AcWen, w16, dst, w17, w12, w10, w11);
    ALU ALU_u(w15, ALU_op, w9, w8, w13, w12);
    mux2x8bit ALU_a_mux_u(w10, zero8, ALU_mux1, w9);
    mux3x8bit ALU_b_mux_u(w11, w5, zero8, ALU_mux2, w8);
    Register3 status_u(clk, rst, statusWen, w13, status);
    mux2x1bit Cin_mux_u(zero8[0], w14, Cin_mux, w15);
    DataMem Memory(clk, w12, w2, MemWen, w5);
    mux2x13bit MemAdr_mux_u(w1, w3, MemAdr_mux, w2);
    Register8 InsReg_u(clk, rst, InsWen, w5, bus);
    Register8 TempReg_u(clk, rst, TempWen, w5, w18);
    always_comb begin : wiring
        w14 = status[2];
        w3 = {bus[4:0], w18};
        src = bus[1:0];
        dst = bus[3:2];
        w4 = bus[4:0];
        jmp_mode = w19[2:1];
        w20 = w19[4:3];
        opcode = bus[7:4];
    end
endmodule

 










