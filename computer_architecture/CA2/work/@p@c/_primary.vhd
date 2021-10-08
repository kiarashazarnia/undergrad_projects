library verilog;
use verilog.vl_types.all;
entity PC is
    port(
        clk             : in     vl_logic;
        rst             : in     vl_logic;
        pcIn            : in     vl_logic_vector(11 downto 0);
        pcOut           : out    vl_logic_vector(11 downto 0)
    );
end PC;
