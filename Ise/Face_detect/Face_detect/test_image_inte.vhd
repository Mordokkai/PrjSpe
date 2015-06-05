-- TestBench Template 

  LIBRARY ieee;
  USE ieee.std_logic_1164.ALL;
  USE ieee.numeric_std.ALL;

  ENTITY testbench IS
  END testbench;

  ARCHITECTURE behavior OF testbench IS 
  
  COMPONENT RAM_II  
    PORT(
         clk : IN  std_logic;
         adress : in  unsigned(31 downto 0);
         we : IN  std_logic;
			data_i : IN  unsigned(31 downto 0);
			data_o : out  unsigned(31 downto 0)
        );
    END COMPONENT;
          
			  SIGNAL CLK : STD_LOGIC;
           SIGNAL RST : STD_LOGIC;
           SIGNAL Image_ready : STD_LOGIC;
           SIGNAL Image_int_ready : STD_LOGIC;
           SIGNAL Din_img : unsigned (7 downto 0);
           SIGNAL Din_i : unsigned (31 downto 0);
           SIGNAL Din_ic : unsigned (31 downto 0);
           SIGNAL Dout_i : unsigned (31 downto 0);
           SIGNAL Dout_ic : unsigned (31 downto 0);
           SIGNAL Offset_lect_img : unsigned (15 downto 0);
           SIGNAL Offset_ecr_int : unsigned (15 downto 0);
           SIGNAL Offset_lect_int : unsigned (15 downto 0);
           SIGNAL we2 : STD_LOGIC;
           SIGNAL we3 : STD_LOGIC;
           SIGNAL Det_end : STD_LOGIC;
			  
			  
			  constant clk_period : time := 1 ns;

			  signal adress: unsigned(31 downto 0):=(others=>'0');
			  signal we: std_logic;

  BEGIN
  
  uut: ram_II PORT MAP (
			adress => adress,
         clk => clk,
			 we => we,
			 data_i => data_i,
			 data_o=>data_o
        );
  

  --  Test Bench Statements
  clk_process :process
		begin
        clk <= '0';
        wait for clk_period/2;  --for 0.5 ns signal is '0'.
        clk <= '1';
        wait for clk_period/2;  --for next 0.5 ns signal is '1'.
		end process;
  
     tb : PROCESS
     BEGIN

        wait for 100 ns; -- wait until global set/reset completes

        -- Add user defined stimulus here

        wait; -- will wait forever
     END PROCESS tb;
  --  End Test Bench 

  END;
