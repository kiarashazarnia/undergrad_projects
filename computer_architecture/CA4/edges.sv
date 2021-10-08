module IF_ID(
                input clk,rst, kill_in,
                input[11:0] pc1_in,
                input[18:0] ins_in,
                output logic kill_out,
                output logic[11:0] pc1_out,
                output logic[18:0] ins_out);
    Register1 kill(clk,rst, kill_in, kill_out);
    Register12 pc1_reg(clk,rst, pc1_in, pc1_out);
    Register19 ins_reg(clk,rst, ins_in, ins_out);
endmodule

module ID_EX(
    input clk,rst,
    input regDst_in,
    input ALU1_mux_in,
    input status_en_in,
    input ALU_o_sh_in,
    input exm_o_mem_in,
    input RegWrite_in,
    input MemWen,
    input[1:0] pcmax,
    input[1:0] shiftOp_in,
    input[2:0] ALUop,
    input[7:0] val1_in, val2_in,
    input[11:0] jump_to_adr_in,
    input[18:0] ins_in,
    output logic RegDst_out,
    output logic ALU1_mux_out,
    output logic status_en_out,
    output logic ALU_o_sh_out,
    output logic exm_o_mem_out,
    output logic RegWrite_out,
    output logic MemWen_out,
    output logic[1:0] pcmax_out,
    output logic[1:0] shiftOp_out,
    output logic[2:0] ALUop_out,
    output logic[7:0] val1_out, val2_out,
    output logic[11:0] jump_to_adr_out,
    output logic[18:0] ins_out);

    Register13  signals_r   (clk,rst, {ALU1_mux_in, status_en_in, ALU_o_sh_in, exm_o_mem_in, RegWrite_in, MemWen, pcmax, shiftOp_in, ALUop}, {ALU1_mux_out, status_en_out, ALU_o_sh_out, exm_o_mem_out, RegWrite_out, MemWen_out, pcmax_out, shiftOp_out, ALUop_out});
    Register19  ins_r       (clk,rst, ins_in, ins_out);
    Register8   val1_r      (clk,rst, val1_in, val1_out);
    Register8   val2_r      (clk,rst,val2_in, val2_out);
    Register12  adr_r       (clk,rst, jump_to_adr_in, jump_to_adr_in);
    Register1 regDst_r (clk,rst, regDst_in, RegDst_out);
endmodule

module EX_MEM(
    input clk,rst,
    input ex_o_mem_in, RegWrite_in, MemWen_in,
    input regDst_in,
    input[7:0] Rd_in,
    input[7:0] resault_in,
    input[18:0] ins_in,
    output logic ex_o_mem_o, RegWrite_o, MemWen_o,
    output logic RegDst_out,
    output logic[7:0] Rd_o,
    output logic[7:0] resault_o,
    output logic[18:0] ins_out
    );
    Register3 memsignals_r (clk,rst, {ex_o_mem_in, RegWrite_in, MemWen_in}, {ex_o_mem_o, RegWrite_o, MemWen_o});
    Register8 Rd_r (clk,rst, Rd_in, Rd_o);
    Register8 Res_r (clk,rst, resault_in, resault_o);
    Register19  ins_r       (clk,rst, ins_in, ins_out);
    Register1 regDst_r (clk,rst, regDst_in, RegDst_out);
endmodule

module MEM_REG(
    input clk,rst,
    input RegWrite_in,
    input regDst_in,
    input[7:0] resault_in,
    input[18:0] ins_in,
    output logic RegWrite_o,
    output logic RegDst_out,
    output logic[7:0] resault_o,
    output logic[18:0] ins_out
);
    Register8 Res_r (clk,rst, resault_in, resault_o);
    Register1 RegWrite_r(clk,rst, RegWrite_in, RegWrite_o);
    Register19  ins_r       (clk,rst, ins_in, ins_out);
    Register1 regDst_r (clk,rst, regDst_in, RegDst_out);
endmodule
