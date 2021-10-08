module controller(
    input C, Z,
    input[4:0] command,
    output logic store, R2_o_Rd, sel_imm, en1, sh_o_ALU, en, reg_write, pop, push,
    output logic [1:0] what_the_faz, pc_state
);

    always_comb begin
        {store, R2_o_Rd, sel_imm, en1, sh_o_ALU, en, reg_write, pop, push, what_the_faz, pc_state} = 0;
        if(command[4:3] == 2'b00) begin : ALU
            sel_imm = 0;
            en = 1;
            sh_o_ALU = 0;
            pc_state = 2'b00;
            what_the_faz = 2'b00;
            reg_write = 1;
        end
        
        else if(command[4:3] == 2'b01) begin : ALU_imm
            sel_imm = 1;
            en = 1;
            sh_o_ALU = 0;
            pc_state = 2'b00;
            what_the_faz = 2'b00;
            reg_write = 1;
        end
        
        else if(command[4:2] == 3'b110) begin : shift_or_rotate
            en = 1;
            sh_o_ALU = 1;
            pc_state = 2'b00;
            what_the_faz = 2'b10;
            reg_write = 1;
        end
        
        else if (command[4:2] == 3'b100) begin : memory
            if(command[1:0] == 2'b00) begin : load_word
                reg_write = 1;
                what_the_faz = 2'b01;
            end
            else if (command[1:0] == 2'b01) begin : store_word
                store = 1;
                R2_o_Rd = 1;
            end
        end
        
        else if (command[4:2] == 3'b101) begin : conditional_jump
            case (command[1:0])
            2'b00:  if(Z)    pc_state = 2'b11;
            2'b01:  if(~Z)    pc_state = 2'b11;
            2'b10:  if(C)    pc_state = 2'b11;
            2'b11:  if(~C)    pc_state = 2'b11;
            endcase
        end
        else if (command == 5'b11100) begin : jmp
            pc_state = 2'b10;
        end
        else if (command == 5'b11101) begin : jsb
            pc_state = 2'b10;
            push = 1;
        end
        else if (command == 5'b11110) begin : RET // 6 bits is required!???
            pop = 1;
            pc_state = 2'b01;
        end
        else
            {store, R2_o_Rd,sel_imm, en1, sh_o_ALU, en, reg_write, pop, push, what_the_faz, pc_state} = 0;
    end
endmodule