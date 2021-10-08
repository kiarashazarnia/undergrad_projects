library verilog;
use verilog.vl_types.all;
entity InsMemory is
    port(
        address         : in     vl_logic_vector(11 downto 0);
        ins_out         : out    vl_logic_vector(18 downto 0)
    );
end InsMemory;
