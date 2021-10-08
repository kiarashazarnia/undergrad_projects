module CPU (input clk, rst);
logic stallBr, kill_current, ALU1_mux, status_en, ALU_o_sh, ex_o_mem, reg_write, MemWen, RegDst, kill_next,Cff, Zff, ALU1_forward, ALU2_forward, push, pop;
logic[1:0] shiftOp, PCmux, PCmuxbc, R1_forward, R2_forward;
logic[2:0] ALUop, R1_dc_ex, R2_dc_ex, Rd_ex_mem, R1_if_dc, R2_if_dc, Rd_dc_ex;
logic[4:0] command1, command2;
ForwardController forwardController(
    R1_dc_ex, R2_dc_ex, Rd_ex_mem,
                R1_if_dc, R2_if_dc, Rd_dc_ex,
    ALU1_forward, ALU2_forward,
    R1_forward, R2_forward
);
controller control(
    clk,
    stallBr, kill_current,
    command1,
    ALU1_mux, status_en, ALU_o_sh, ex_o_mem, reg_write, MemWen, RegDst, kill_next, push, pop,
    shiftOp, PCmux,
    ALUop
);
BController bcontroller(
        Cff, Zff,
        command2,
        stallBr,
        PCmuxbc
);
Datapth datapath(
    clk,rst,ALU1_mux, status_en, ALU_o_sh, ex_o_mem, reg_write, MemWen, RegDst, kill_next, ALU1_forward, ALU2_forward,stallBr,push, pop,
    shiftOp, PCmux, PCmuxbc, R1_forward, R2_forward,
    ALUop,
    kill_current, Cff, Zff,
    R1_dc_ex, R2_dc_ex, Rd_ex_mem, R1_if_dc, R2_if_dc, Rd_dc_ex,
    command1, command2
);
endmodule // cpu
