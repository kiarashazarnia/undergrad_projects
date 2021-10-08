module BController(
    input Cff, Zff,
    input[4:0] command,
    output logic stall,
    output logic[1:0] PCmux
);

always_comb begin
    stall = 0;
    PCmux = 0;
    if (command[4:2] == 3'b101) begin : conditional_jump
        case (command[1:0])
            2'b00:  if(Zff)   begin stall = 1; PCmux = 1; end
            2'b01:  if(~Zff)  begin stall = 1; PCmux = 1; end
            2'b10:  if(Cff)   begin stall = 1; PCmux = 1; end
            2'b11:  if(~Cff)  begin stall = 1; PCmux = 1; end
        endcase
    end
end

endmodule
