library verilog;
use verilog.vl_types.all;
entity SignExt8to12 is
    port(
        \in\            : in     vl_logic_vector(7 downto 0);
        \out\           : out    vl_logic_vector(11 downto 0)
    );
end SignExt8to12;
