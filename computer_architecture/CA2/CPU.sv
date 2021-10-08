module CPU(input clk, rst);

    logic C, Z, store, R2_o_Rd, sel_imm, en1, sh_o_ALU, en, reg_write, pop, push;
    logic[1:0] what_the_faz, pc_state;
    logic[4:0] command;

    controller controller_u(
    C, Z,
    command,
    store, R2_o_Rd, sel_imm, en1, sh_o_ALU, en, reg_write, pop, push,
    what_the_faz, pc_state);

    DP DP_u(
		clk, rst,
		sel_imm, store, en, pop, push, sh_o_ALU, R2_o_Rd, reg_write,
		pc_state, what_the_faz,
		C, Z,
		command);

endmodule
