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
  
  COMPONENT RAM_image  --'test' is the name of the module needed to be tested.
    PORT(
         clk : IN  std_logic;
         adress : in  unsigned(31 downto 0);
         we : IN  std_logic;
			data_i : IN  unsigned(7 downto 0);
			data_o : out  unsigned(7 downto 0)
        );
    END COMPONENT;
	 
	 
  COMPONENT RAM_II  
    PORT(
         clk : IN  std_logic;
         adress : in  unsigned(31 downto 0);
         we : IN  std_logic;
			data_i : IN  unsigned(31 downto 0);
			data_o : out  unsigned(31 downto 0)
        );
    END COMPONENT;
          
				
				SIGNAL RST : STD_LOGIC;
				SIGNAL Image_ready : STD_LOGIC;
				SIGNAL Image_int_ready : STD_LOGIC;
				SIGNAL Din_img : unsigned (7 downto 0);
				SIGNAL Dout_img : unsigned (7 downto 0);
				SIGNAL Din_i : unsigned (31 downto 0);
				SIGNAL Din_ic : unsigned (31 downto 0);
				SIGNAL Dout_i : unsigned (31 downto 0);
				SIGNAL Dout_ic : unsigned (31 downto 0);
				SIGNAL Offset_lect_img : unsigned (31 downto 0);
				SIGNAL Offset_ecr_int : unsigned (31 downto 0);
				SIGNAL Offset_lect_int : unsigned (15 downto 0);
				SIGNAL we2 : STD_LOGIC;
				SIGNAL we3 : STD_LOGIC;
				SIGNAL Det_end : STD_LOGIC;
			  
			  
				signal clk : std_logic := '0';
   

			  
			  constant clk_period : time := 1 ns;

			  signal adress: unsigned(31 downto 0):=(others=>'0');
			  signal we: std_logic;
			  
			  
			  
--			  
				--signal adress : unsigned(31 downto 0):=(others=>'0');
				signal adress_next: unsigned(31 downto 0):=(others=>'0');
--				signal we_2 : std_logic;
--				signal data_i_2 : unsigned(39 downto 0);
--				signal data_o_2 : unsigned(39 downto 0);
				signal counter : std_logic :='0';
				signal clock,endoffile : bit := '0';
				signal termine : boolean;

  BEGIN
  
  uut: ram_II PORT MAP (
			adress => Offset_ecr_int,
         clk => clk,
			 we => we2,
			 data_i => Din_i,
			 data_o=>Dout_i
        );
  
	uut_3: ram_image PORT MAP (
			adress => adress,
         clk => clk,
			 we => we,
			 data_i => Din_img,
			 data_o=>Dout_img
       ); 

  --  Test Bench Statements
  clk_process :process
		begin
        clk <= '0';
        wait for clk_period/2;  --for 0.5 ns signal is '0'.
        clk <= '1';
        wait for clk_period/2;  --for next 0.5 ns signal is '1'.
		end process;


cpt: process(clk)
	begin
	
	adress_next<= adress +1;
	
end process;












writing_RAM_image :
process
    file   infile    : text is in  "/user/6/guys/Bureau/PrjSpeFinal/PrjSpe/img/lena.ascii.retouche.pgm";   --declare input file
    variable  inline    : line; --line number declaration
    variable  dataread1    : integer;
	 variable counter: integer :=0;
	 
begin


wait until clk = '1' and clk'event;
if (not endfile(infile)) then   --checking the "END OF FILE" is not reached.
	we <= '1';
	readline(infile, inline);       --reading a line from the file.
	read(inline, dataread1);
	Din_img <=to_unsigned(dataread1,8);   --put the value available in variable in a signal.
	adress<=adress_next;

else
	we <= '0';
	termine <= true;
	if(counter = 0) then
		adress<=(others=>'0');
		counter :=1;
	else 
		adress<=adress_next;
	end if;
	endoffile <='1';         --set signal to tell end of file read file is reached.
end if;
wait until clk = '1' and clk'event;

end process writing_RAM_image;




























  END;
