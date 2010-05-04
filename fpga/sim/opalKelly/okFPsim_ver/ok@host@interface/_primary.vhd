library verilog;
use verilog.vl_types.all;
entity okHostInterface is
    port(
        hi_in           : in     vl_logic_vector(7 downto 0);
        hi_out          : out    vl_logic_vector(1 downto 0);
        hi_inout        : inout  vl_logic_vector(15 downto 0);
        ti_clk          : out    vl_logic;
        ok1             : out    vl_logic_vector(30 downto 0);
        ok2             : in     vl_logic_vector(16 downto 0)
    );
end okHostInterface;
