library verilog;
use verilog.vl_types.all;
entity PCAdd1 is
    port(
        pcIn            : in     vl_logic_vector(11 downto 0);
        pcOut           : out    vl_logic_vector(11 downto 0)
    );
end PCAdd1;
