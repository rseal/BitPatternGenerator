library verilog;
use verilog.vl_types.all;
entity okBTPipeIn is
    port(
        ok1             : in     vl_logic_vector(30 downto 0);
        ok2             : out    vl_logic_vector(16 downto 0);
        ep_addr         : in     vl_logic_vector(7 downto 0);
        ep_write        : out    vl_logic;
        ep_blockstrobe  : out    vl_logic;
        ep_dataout      : out    vl_logic_vector(15 downto 0);
        ep_ready        : in     vl_logic
    );
end okBTPipeIn;
