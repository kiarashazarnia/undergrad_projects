library verilog;
use verilog.vl_types.all;
entity mux4x8bit is
    port(
        a               : in     vl_logic_vector(7 downto 0);
        b               : in     vl_logic_vector(7 downto 0);
        c               : in     vl_logic_vector(7 downto 0);
        d               : in     vl_logic_vector(7 downto 0);
        sel             : in     vl_logic_vector(1 downto 0);
        e               : out    vl_logic_vector(7 downto 0)
    );
end mux4x8bit;
