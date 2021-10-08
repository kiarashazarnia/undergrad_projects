library verilog;
use verilog.vl_types.all;
entity controller is
    port(
        C               : in     vl_logic;
        Z               : in     vl_logic;
        command         : in     vl_logic_vector(4 downto 0);
        store           : out    vl_logic;
        R2_o_Rd         : out    vl_logic;
        sel_imm         : out    vl_logic;
        en1             : out    vl_logic;
        sh_o_ALU        : out    vl_logic;
        en              : out    vl_logic;
        reg_write       : out    vl_logic;
        pop             : out    vl_logic;
        push            : out    vl_logic;
        what_the_faz    : out    vl_logic_vector(1 downto 0);
        pc_state        : out    vl_logic_vector(1 downto 0)
    );
end controller;
