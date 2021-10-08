module Datapth(
    input clk,rst, ALU1_mux, status_en, ALU_o_sh, ex_o_mem, reg_write, MemWen, RegDst, kill_next, ALU1_forward, ALU2_forward,stallBr, push, pop,
    input[1:0] shiftOp, PCmux, PCmuxbc, R1_forward, R2_forward,
    input[2:0] ALUop,
    output logic kill_current, Cff, Zff,
    output logic[2:0]R1_dc_ex, R2_dc_ex, Rd_ex_mem, R1_if_dc, R2_if_dc, Rd_dc_ex,
    output logic[4:0]command1, command2
);
    logic[11:0] w1, w2, w4, w9, w15, w17, w18, w19, w20, wtemp;
    logic[18:0] w3, w5 ,w54, w56, w58;
    logic[2:0] w6, w7, w8, w21, w25, w66;
    logic[7:0] w10, w11, w12, w13, w14, w16, w22, w23, w24, w31, w32, w33, w35, w36, w37, w44, w45, w46, w47, w64;
    logic[1:0] w26, w63, w65;
    logic w27, w28, w29, w30, w34, w38, w39, w40, w41, w42, w48, w49, w50, w51, w52, w53, w55, w57, w59, w60, w61, w62;
    assign command1 = w5[18:14];
    assign command2 = w54[18:14];
    assign R1_dc_ex = w54[10:8];
    assign R2_dc_ex = w54[7:5];
    assign Rd_ex_mem = w56[13:11];
    assign R1_if_dc = w5[10:8];
    assign R2_if_dc = w5[7:5];
    assign Rd_dc_ex = w54[13:11];
    assign Cff = w39;
    assign Zff = w59;
    assign w21 = w54[7:5];
    assign w22 = w54[7:0];
    assign w6 = w5[10:8];
    assign w7 = w5[7:5];
    assign w9 = w5[11:0];
    assign w16 = w5[7:0];
    InsMemory ins_mem_u(w1,w3);
    Incrementer12 pcPlus1_u(w1, w2);
    PC PC_u(clk,rst,w4,w1);
    RegisterFile register_u(clk,rst,w48,w6,w66,w58[13:11],w10,w12,w11);
    Adder12 jumpBrAdr_u(w15,w17,w19);
    ALU alu_u(w39,w25,w31,w33,w42,w41,w36);
    shifter shift_u(w26,w21,w31/*???*/,w51,w52,w35);
    DataMem memory_u(clk,w45,w44,w53,w46);
    SignExt8to12 ext_u(w16,w15);
    IF_ID if_id_u(clk,rst,kill_next,w2,w3,kill_current,w17,w5);
    ID_EX id_ex_u(clk,rst, RegDst,ALU1_mux,status_en,ALU_o_sh,ex_o_mem,reg_write,MemWen,PCmux,shiftOp,ALUop,w13, w14,w19,w5, w60,w30,w29,w28,w27,w55,w50,w65,w26,w25,w23, w24,wtemp,w54);
    Register12 erer(
                    clk,
                    rst,
                    w19,
                    w20);
    EX_MEM ex_mem_u(clk,rst, w27, w55, w50,w60,w24,w37,w54,w49, w57, w53,w61,w44,w45,w56);
    MEM_REG mem_reg_u(clk,rst, w57,w61,w47,w56,w48,w62,w10,w58);
    Stack stack_u(clk, rst, pop, push, w17, w18);
    FF C_u(clk,rst,w29,w38,w39);
    FF Z_u(clk,rst, w29,w40,w59);
    mux4x12bit pcstate_u(w2, w20, w9, w18, w63, w4);
    mux2x2bit pcmux_r(PCmux, PCmuxbc, stallBr, w63);
    mux2x3bit rd_r(w7, w8, w62, w66);
    mux4x8bit read1For_u(w12, w37, w47, 8'bz, R1_forward, w13);
    mux4x8bit read2For_u(w11, w37, w47, 8'bz, R2_forward, w14);
    mux2x8bit impR2_u(w24, w47, ALU2_forward, w64);
    mux2x8bit alu1_u(w64, w22, w30, w33);
    mux2x8bit alu2_u(w23, w47, ALU1_forward, w31);
    mux2x1bit z_u(w41, w52, w28, w40);
    mux2x1bit c_u(w42, w51, w28 ,w38);
    mux2x8bit sh_alu_u(w36, w35, w28, w37);
    mux2x8bit ex_mem_mux_u(w45, w46, w49, w47);
endmodule
