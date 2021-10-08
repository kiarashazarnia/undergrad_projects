library verilog;
use verilog.vl_types.all;
entity FF is
    port(
        clk             : in     vl_logic;
        rst             : in     vl_logic;
        en              : in     vl_logic;
        \in\            : in     vl_logic;
        \out\           : out    vl_logic
    );
end FF;
