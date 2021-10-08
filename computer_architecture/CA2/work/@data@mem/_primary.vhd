library verilog;
use verilog.vl_types.all;
entity DataMem is
    port(
        clk             : in     vl_logic;
        address         : in     vl_logic_vector(7 downto 0);
        data            : in     vl_logic_vector(7 downto 0);
        store           : in     vl_logic;
        \out\           : out    vl_logic_vector(7 downto 0)
    );
end DataMem;
