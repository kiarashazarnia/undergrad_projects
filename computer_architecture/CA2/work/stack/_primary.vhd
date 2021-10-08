library verilog;
use verilog.vl_types.all;
entity stack is
    port(
        clk             : in     vl_logic;
        rst             : in     vl_logic;
        pop             : in     vl_logic;
        push            : in     vl_logic;
        inp             : in     vl_logic_vector(11 downto 0);
        \out\           : out    vl_logic_vector(11 downto 0)
    );
end stack;
