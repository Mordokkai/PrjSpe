
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;
 
ENTITY bench_alu IS
END bench_alu;
 
ARCHITECTURE behavior OF bench_alu IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT adder
    PORT(
         In_A : IN  signed(15 downto 0);
         In_B : IN  signed(15 downto 0);
         In_param : IN  std_logic_vector(15 downto 0);
         out_AB : OUT  signed(15 downto 0);
         Out_param : OUT  std_logic_vector(8 downto 0)
        );
    END COMPONENT;
	 
	 Component mult 
	 port(
			In_A : IN  signed(15 downto 0);
         In_B : IN  signed(15 downto 0);
         In_param : IN  std_logic_vector(15 downto 0);
			out_AB : OUT  signed(31 downto 0);
         Out_param : OUT  std_logic_vector(9 downto 0)
			);
	 end component;
	 
	 
    

   --Inputs
   signal In_A : signed(15 downto 0) := (others => '0');
   signal In_B : signed(15 downto 0) := (others => '0');
   signal In_param : std_logic_vector(15 downto 0) := (others => '0');

 	--Outputs
   signal out_AB_add : signed(15 downto 0);
   signal Out_param_add : std_logic_vector(8 downto 0);
	signal out_Ab_mult : signed (31 downto 0);
	signal out_param_mult : std_logic_vector (9 downto 0);

 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut_add: adder PORT MAP (
          In_A => In_A,
          In_B => In_B,
          In_param => In_param,
          out_AB => out_Ab_add,
          Out_param => Out_param_add
        );
	
	uut_mult: mult PORT MAP (
          In_A => In_A,
          In_B => In_B,
          In_param => In_param,
          out_AB => out_Ab_mult,
          Out_param => Out_param_mult
        );
	in_A <= "0000000110000000";
	in_B <= "0000000000001000";
	in_param <="0100010000100010";



END;
