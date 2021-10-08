module controller(
    input clk,
    input stallBr, kill_current,
    input[4:0] command,
    output logic ALU1_mux, status_en, ALU_o_sh, ex_o_mem, reg_write, MemWen, RegDst, kill_next, push , pop,
    output logic[1:0] shiftOp, PCmux,
    output logic[2:0] ALUop
    );

always_comb begin
    {ALU1_mux, status_en, ALU_o_sh, ex_o_mem, reg_write, MemWen, RegDst, kill_next,
    shiftOp, PCmux, ALUop, push, pop} = 0;

if(stallBr) begin
    kill_next = 1;
end

if(!kill_current && !stallBr) begin

    if(command[4:3] == 2'b00) begin : ALU
        ALU1_mux = 0;
        status_en = 1;
        ALU_o_sh = 0;
        ex_o_mem = 0;
        reg_write = 1;
        MemWen = 0;
        PCmux = 0;
        ALUop = command[2:0];
        RegDst = 0;
    end

    else if(command[4:3] == 2'b01) begin : ALU_imm
        ALU1_mux = 1;
        status_en = 1;
        ALU_o_sh = 0;
        ex_o_mem = 0;
        reg_write = 1;
        MemWen = 0;
        PCmux = 0;
        ALUop = command[2:0];
        RegDst = 0;
    end

    else if(command[4:2] == 3'b110) begin : shift_or_rotate
        status_en = 1;
        ALU_o_sh = 1;
        ex_o_mem = 0;
        reg_write = 1;
        MemWen = 0;
        PCmux = 0;
        RegDst = 0;
        shiftOp = command[1:0];
    end

    else if (command[4:2] == 3'b100) begin : memory
        if(command[1:0] == 2'b00) begin : load_word
            ALU1_mux = 1;
            ALU_o_sh = 0;
            ex_o_mem = 1;
            reg_write = 1;
            PCmux = 0;
            ALUop = 3'b000;
        end
        else if (command[1:0] == 2'b01) begin : store_word
            ALU1_mux = 1;
            ALU_o_sh = 0;
            ex_o_mem = 1;
            MemWen = 1;
            PCmux = 0;
            ALUop = 3'b000;
            RegDst = 1;
        end
    end

    else if (command[4:2] == 3'b101) begin : conditional_jump
    // this controller does nothing
    end

    else if (command == 5'b11100) begin : jmp
        PCmux = 2;
        kill_next = 1;
    end
    else if (command == 5'b11101) begin : jsb
        PCmux = 2;
        kill_next = 1;
        push = 1;
    end
    else if (command == 5'b11110) begin : RET
        pop = 1;
        PCmux = 3;
    end
end
end
endmodule
