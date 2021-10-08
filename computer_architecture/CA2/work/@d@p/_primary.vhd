library verilog;
use verilog.vl_types.all;
entity DP is
    port(
        clk             : in     vl_logic;
        rst             : in     vl_logic;
        sel_imm         : in     vl_logic;
        store           : in     vl_logic;
        en              : in     vl_logic;
        pop             : in     vl_logic;
        push            : in     vl_logic;
        sh_o_ALU        : in     vl_logic;
        R2_o_Rd         : in     vl_logic;
        regWrite        : in     vl_logic;
        pc_state        : in     vl_logic_vector(1 downto 0);
        what_the_faz    : in     vl_logic_vector(1 downto 0);
        C_out           : out    vl_logic;
        Z_out           : out    vl_logic;
        command         : out    vl_logic_vector(4 downto 0)
    );
end DP;
