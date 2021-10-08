module Proccessor(input clk, rst);
    
    logic[1:0] jmp_mode;
    logic[2:0] status;
    logic[3:0] opcode;
    logic PCWen, DirWen, statusWen, MemWen, TempWen, InsWen, AcWen;
    logic AcW_mux, Ac1_mux, PC_mux, Cin_mux, ALU_mux1, MemAdr_mux;
    logic[1:0] ALU_mux2, ALU_op;

    controller controller_u(
        clk, rst,
        jmp_mode,
        status,
        opcode,
        PCWen, DirWen, statusWen, MemWen, TempWen, InsWen, AcWen,
        AcW_mux, Ac1_mux, PC_mux, Cin_mux, ALU_mux1, MemAdr_mux,
        ALU_mux2, ALU_op);

    DataPath DataPath_u(
        clk, rst,
        PCWen, DirWen, statusWen, MemWen, TempWen, InsWen, AcWen,
        AcW_mux, Ac1_mux, PC_mux, Cin_mux, ALU_mux1, MemAdr_mux,
        ALU_mux2, ALU_op,
        opcode,
        jmp_mode,
        status);

endmodule