library verilog;
use verilog.vl_types.all;
entity ALU is
    generic(
        ADD             : vl_logic_vector(2 downto 0) := (Hi0, Hi0, Hi0);
        ADDC            : vl_logic_vector(2 downto 0) := (Hi0, Hi0, Hi1);
        SUB             : vl_logic_vector(2 downto 0) := (Hi0, Hi1, Hi0);
        SUBC            : vl_logic_vector(2 downto 0) := (Hi0, Hi1, Hi1);
        \AND\           : vl_logic_vector(2 downto 0) := (Hi1, Hi0, Hi0);
        \OR\            : vl_logic_vector(2 downto 0) := (Hi1, Hi0, Hi1);
        \XOR\           : vl_logic_vector(2 downto 0) := (Hi1, Hi1, Hi0);
        MASK            : vl_logic_vector(2 downto 0) := (Hi1, Hi1, Hi1)
    );
    port(
        a               : in     vl_logic_vector(7 downto 0);
        b               : in     vl_logic_vector(7 downto 0);
        fn              : in     vl_logic_vector(2 downto 0);
        carryIn         : in     vl_logic;
        ALU_Z           : out    vl_logic;
        ALU_C           : out    vl_logic;
        \out\           : out    vl_logic_vector(7 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of ADD : constant is 2;
    attribute mti_svvh_generic_type of ADDC : constant is 2;
    attribute mti_svvh_generic_type of SUB : constant is 2;
    attribute mti_svvh_generic_type of SUBC : constant is 2;
    attribute mti_svvh_generic_type of \AND\ : constant is 2;
    attribute mti_svvh_generic_type of \OR\ : constant is 2;
    attribute mti_svvh_generic_type of \XOR\ : constant is 2;
    attribute mti_svvh_generic_type of MASK : constant is 2;
end ALU;
