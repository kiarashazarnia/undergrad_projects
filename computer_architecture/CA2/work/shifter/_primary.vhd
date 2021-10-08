library verilog;
use verilog.vl_types.all;
entity shifter is
    generic(
        SHL             : vl_logic_vector(1 downto 0) := (Hi0, Hi0);
        SHR             : vl_logic_vector(1 downto 0) := (Hi0, Hi1);
        \ROL\           : vl_logic_vector(1 downto 0) := (Hi1, Hi0);
        \ROR\           : vl_logic_vector(1 downto 0) := (Hi1, Hi1)
    );
    port(
        fn              : in     vl_logic_vector(1 downto 0);
        shiftCount      : in     vl_logic_vector(2 downto 0);
        \in\            : in     vl_logic_vector(7 downto 0);
        shiftC          : out    vl_logic;
        shiftZ          : out    vl_logic;
        \out\           : out    vl_logic_vector(7 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of SHL : constant is 2;
    attribute mti_svvh_generic_type of SHR : constant is 2;
    attribute mti_svvh_generic_type of \ROL\ : constant is 2;
    attribute mti_svvh_generic_type of \ROR\ : constant is 2;
end shifter;
