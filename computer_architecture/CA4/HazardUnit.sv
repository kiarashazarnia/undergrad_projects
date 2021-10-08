module ForwardController(
    input[2:0]  R1_dc_ex, R2_dc_ex, Rd_ex_mem,
                R1_if_dc, R2_if_dc, Rd_dc_ex,
    output logic ALU1_forward, ALU2_forward,
    output logic[1:0] R1_forward, R2_forward
);
    always_comb begin
        if(R1_dc_ex == Rd_ex_mem)
            ALU1_forward = R1_dc_ex == Rd_ex_mem;
        else
            ALU1_forward = 0;
        if(R2_dc_ex == Rd_ex_mem)
            ALU2_forward = R2_dc_ex == Rd_ex_mem;
        else
            ALU2_forward = 0;
        if(R1_if_dc == Rd_dc_ex)
            R1_forward = 1;
        else if(R1_if_dc == Rd_ex_mem)
            R1_forward = 2;
        else
            R1_forward = 0;
        if(R2_if_dc == Rd_dc_ex)
            R2_forward = 1;
        else if(R2_if_dc == Rd_ex_mem)
            R2_forward = 2;
        else
            R2_forward = 0;
    end
endmodule
