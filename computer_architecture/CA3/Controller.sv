module controller(
    input clk, rst,
    input[1:0] jmp_mode,
    input[2:0] status,
    input[3:0] opcode,
    output logic PCWen, DirWen, statusWen, MemWen, TempWen, InsWen, AcWen,
    output logic AcW_mux, Ac1_mux, PC_mux, Cin_mux, ALU_mux1, MemAdr_mux,
    output logic[1:0] ALU_mux2, ALU_op
    );

    logic[3:0] PS;
    logic[3:0] NS;

    logic C, Z, N;
    always_comb begin
        C = status[2];
        Z = status[1];
        N = status[0];
    end

// Debugging signals
    logic invalid_opcode;
    logic invalid_state;

    logic adress_instruction;
    assign adress_instruction = opcode[3:2] == 2'b01 || opcode[3:2] == 2'b00;

// Instructions
    parameter[3:0]
        LDA = 4'b0000,
        STA = 4'b0010,
        ADA = 4'b0100,
        ANA = 4'b0110,
        MVR = 4'b1000,
        ADR = 4'b1001,
        ANR = 4'b1010,
        ORR = 4'b1011,
        JMP = 4'b1100,
        LDI1 = 4'b1110,
        LDI2 = 4'b1111;

// States
    parameter[3:0]
        InsFetch =  4'b0001,
        InsDecode = 4'b0010,
        LoadTemp =  4'b0011,
        LDAProc =   4'b0100,
        STAProc =   4'b0101,
        ADAProc =   4'b0110,
        ANAProc =   4'b0111,
        MVRProc =   4'b1000,
        ADRProc =   4'b1001,
        ANRProc =   4'b1010,
        ORRProc =   4'b1011,
        JMPIns  =   4'b1100,
        LDIProc =   4'b1101,
        PCNext =    4'b1110,
        TempPCNext =4'b1111;

    always_comb begin: transfering
        invalid_state = 0;
        case (PS)
            InsFetch : NS = InsDecode;
            InsDecode : begin
                invalid_opcode = 0;
                case (opcode)
                    MVR : NS = MVRProc;
                    ADR : NS = ADRProc;
                    ANR : NS = ANRProc;
                    ORR : NS = ORRProc;
                    LDI1 : NS = LDIProc;
                    LDI2 : NS = LDIProc;
                    JMP : begin
                        case (jmp_mode)
                            2'b00 : NS = JMPIns;
                            2'b01 :
                                if(C)
                                    NS = JMPIns;
                                else
                                    NS = PCNext;
                            2'b10 :
                                if(Z)
                                    NS = JMPIns;
                                else
                                    NS = PCNext;
                            2'b11 :
                                if(N)
                                    NS = JMPIns;
                                else
                                    NS = PCNext;
                        endcase
                    end
                    default: begin
                        if(adress_instruction)
                            NS = TempPCNext;
                        else begin
                            invalid_opcode = 1;
                            NS = PCNext;
                        end
                    end
                endcase
            end
            LoadTemp : begin
                invalid_opcode = 0;
                case (opcode)
                    LDA : NS = LDAProc;
                    STA : NS = STAProc;
                    ADA : NS = ADAProc;
                    ANA : NS = ANAProc;
                    default: begin
                        invalid_opcode = 1;
                        NS = PCNext;
                    end
                endcase
            end
            TempPCNext : NS = LoadTemp;
            LDAProc : NS = PCNext;
            STAProc : NS = PCNext;
            ADAProc : NS = PCNext;
            ANAProc : NS = PCNext;
            MVRProc : NS = PCNext;
            ADRProc : NS = PCNext;
            ANRProc : NS = PCNext;
            ORRProc : NS = PCNext;
            LDIProc : NS = PCNext;
            JMPIns  : NS = InsFetch;
            PCNext : NS  = InsFetch;
            default: begin
                invalid_state = 1;
                NS = PCNext;
            end
        endcase
    end

// ALU operation
parameter[1:0]
            ADD = 2'b00,
            AND = 2'b01,
            OR =  2'b10;

always_comb begin: outputing
    {PCWen, DirWen, statusWen, MemWen, TempWen, InsWen, AcWen,
    AcW_mux, Ac1_mux, PC_mux, Cin_mux, ALU_mux1, MemAdr_mux,
    ALU_mux2, ALU_op} = 0;
    case (PS)
        InsFetch : begin
            MemAdr_mux = 0;
            InsWen = 1;
        end
        InsDecode : ;
        TempPCNext :begin
             PC_mux = 0;
             PCWen = 1;
        end
        LoadTemp : begin
            MemAdr_mux = 0;
            TempWen = 1;
        end
        LDAProc : begin
            MemAdr_mux = 1;
            ALU_mux2 = 1;
            ALU_mux1 = 1;
            AcW_mux = 1;
            AcWen = 1;
            ALU_op = ADD;
        end
        STAProc : begin
            Ac1_mux = 1;
            ALU_mux1 = 0;
            ALU_mux2 = 2;
            ALU_op = ADD;
            MemAdr_mux = 1;
            MemWen = 1;
        end
        ADAProc : begin
            Cin_mux = 1;
            ALU_mux2 = 1;
            ALU_op = ADD;
            statusWen = 1;
            Ac1_mux = 1;
            AcW_mux = 1;
            ALU_mux1 = 0;
            MemAdr_mux = 1;
            AcWen = 1;
        end
        ANAProc :  begin
            ALU_mux2 = 1;
            ALU_op = AND;
            Ac1_mux = 1;
            AcW_mux = 1;
            ALU_mux1 = 0;
            MemAdr_mux = 1;
            AcWen = 1;
            statusWen = 1;
        end
        MVRProc :  begin
            Ac1_mux = 0;
            ALU_mux1 = 0;
            ALU_mux2 = 2;
            ALU_op = ADD;
            AcW_mux = 0;
            AcWen = 1;
        end
        ADRProc :  begin
            ALU_mux1 = 0;
            ALU_mux2 = 0;
            ALU_op = ADD;
            AcW_mux = 0;
            Cin_mux = 1;
            AcWen = 1;
            statusWen = 1;
        end
        ANRProc :  begin
            Ac1_mux = 0;
            ALU_mux1 = 1;
            ALU_mux2 = 0;
            ALU_op = AND;
            AcW_mux = 0;
            AcWen = 1;
            statusWen = 1;
        end
        ORRProc :  begin
            Ac1_mux = 0;
            ALU_mux1 = 1;
            ALU_mux2 = 0;
            ALU_op = OR;
            AcW_mux = 0;
            AcWen = 1;
            statusWen = 1;
        end
        JMPIns  : begin
            PC_mux = 1;
            PCWen = 1;
        end
        LDIProc : begin
            DirWen = 1;
        end
        PCNext :begin
            PC_mux = 0;
            PCWen = 1;
        end
        default: begin : InvalidState
            {PCWen, DirWen, statusWen, MemWen, TempWen, InsWen, AcWen,
            AcW_mux, Ac1_mux, PC_mux, Cin_mux, ALU_mux1, MemAdr_mux,
            ALU_mux2, ALU_op} = 0;
        end
    endcase

    end

    always_ff @(posedge clk, posedge rst) begin: next
        if (rst) begin
            PS <= InsFetch;
        end
        else begin
            PS <= NS;
        end
    end
endmodule
