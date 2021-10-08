library verilog;
use verilog.vl_types.all;
entity mux2x1bit is
    port(
        a               : in     vl_logic;
        b               : in     vl_logic;
        sel             : in     vl_logic;
        c               : out    vl_logic
    );
end mux2x1bit;
