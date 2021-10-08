library verilog;
use verilog.vl_types.all;
entity RegisterFile is
    port(
        clk             : in     vl_logic;
        rst             : in     vl_logic;
        reg1            : in     vl_logic_vector(2 downto 0);
        reg2            : in     vl_logic_vector(2 downto 0);
        regw            : in     vl_logic_vector(2 downto 0);
        write           : in     vl_logic_vector(7 downto 0);
        regWrite        : in     vl_logic;
        read1           : out    vl_logic_vector(7 downto 0);
        read2           : out    vl_logic_vector(7 downto 0)
    );
end RegisterFile;
