-- TestBench Template 

LIBRARY ieee;
library std;
use std.textio.all;
use ieee.numeric_std.all;
use ieee.std_logic_1164.all;
	use STD.textio.all;


  ENTITY khalil IS
  END khalil;

  ARCHITECTURE behavior OF khalil IS 
          
			 Component Image_integrale
			  Port ( CLK : in  STD_LOGIC;
           RST : in  STD_LOGIC;
			  Image_ready : in  STD_LOGIC;
			  Image_int_ready : out  STD_LOGIC;
			  Din_img : in  unsigned (7 downto 0);
			  Din_i : in  unsigned (31 downto 0);
			  Din_ic : in  unsigned (31 downto 0);
			  Dout_i : out  unsigned (31 downto 0);
			  Dout_ic : out  unsigned (31 downto 0);
			  Offset_lect_img : out  unsigned (15 downto 0);
			  Offset_ecr_int : out  unsigned (15 downto 0);
			  Offset_lect_int : out  unsigned (15 downto 0);
			  we_i : out  STD_LOGIC;
			  we_ic : out  STD_LOGIC;
			  Det_end : in  STD_LOGIC);
			  end Component Image_integrale;
				
				SIGNAL RST : STD_LOGIC;
				SIGNAL Image_ready : STD_LOGIC;
				SIGNAL Image_int_ready : STD_LOGIC := '0';
				SIGNAL Din_img : unsigned (7 downto 0);
				SIGNAL Dout_img : unsigned (7 downto 0);
				SIGNAL Din_i : unsigned (31 downto 0);
				SIGNAL Din_ic : unsigned (31 downto 0);
				SIGNAL Dout_i : unsigned (31 downto 0);
				SIGNAL Dout_ic : unsigned (31 downto 0);
				SIGNAL Offset_lect_img : unsigned (15 downto 0);
				SIGNAL Offset_ecr_int : unsigned (15 downto 0);
				SIGNAL Offset_lect_int : unsigned (15 downto 0);
				SIGNAL we_i : STD_LOGIC;
				SIGNAL we_ic : STD_LOGIC;
				SIGNAL Det_end : STD_LOGIC;
			  
			  
				signal clk : std_logic := '0';			  
			   constant clk_period : time := 1 ns;

			  

  BEGIN

	uut : Image_integrale PORT MAP(
			  CLK => CLK,
           RST => RST,
			  Image_ready => Image_ready,
			  Image_int_ready => Image_int_ready,
			  Din_img => Din_img,
			  Din_i => Din_i,
			  Din_ic => Din_ic,
			  Dout_i => Dout_i,
			  Dout_ic => Dout_ic,
			  Offset_lect_img => Offset_lect_img, 
			  Offset_ecr_int => Offset_ecr_int,
			  Offset_lect_int => Offset_lect_int,
			  we_i => we_i,
			  we_ic => we_ic,
			  Det_end => Det_end);

	RST <= '1', '0' after 30 ns;

  --  Test Bench Statements
clk_process :process
	begin
      clk <= '0';
      wait for clk_period/2;  --for 0.5 ns signal is '0'.
      clk <= '1';
      wait for clk_period/2;  --for next 0.5 ns signal is '1'.
	end process clk_process;


integral_image : process
	variable cpt : unsigned (7 downto 0) := (others => '0');
	
	begin
	
	wait until clk = '1' and clk'event;
	wait until RST = '0';
	wait until rising_edge(CLK);
	Image_ready <= '1', '0' after 2 ns;
	
	while (cpt < 30) loop
		Din_img <= cpt;
		cpt := cpt + 1;
		wait until clk'event and clk='1';
	end loop;
	cpt := (others => '0');
	while (cpt < 255) loop
		Din_img <= cpt;
		Din_i <= x"000000" & cpt;
		Din_ic <= x"000000" & cpt;
		cpt := cpt + 1;
		wait until clk'event and clk='1';
	end loop;
	cpt := (others => '0');
	while (cpt < 255) loop
		Din_img <= cpt;
		Din_i <= x"000000" & cpt;
		Din_ic <= x"000000" & cpt;
		cpt := cpt + 1;
		wait until clk'event and clk='1';
	end loop;
	cpt := (others => '0');
	while (cpt < 255) loop
		Din_img <= cpt;
		Din_i <= x"000000" & cpt;
		Din_ic <= x"000000" & cpt;
		cpt := cpt + 1;
		wait until clk'event and clk='1';
	end loop;
	
	
	wait;
end process integral_image;	
		

  END;
