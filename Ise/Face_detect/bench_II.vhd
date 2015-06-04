-- TestBench Template 

LIBRARY ieee;
library std;
use std.textio.all;
use ieee.numeric_std.all;
use ieee.std_logic_1164.all;



	use STD.textio.all;
  ENTITY testbench IS
  END testbench;

  ARCHITECTURE behavior OF testbench IS 


--Component declaration
COMPONENT RAM_II  --'test' is the name of the module needed to be tested.
    PORT(
         clk : IN  std_logic;
         adress : in  unsigned(31 downto 0);
         we : IN  std_logic;
			data_i : IN  unsigned(31 downto 0);
			data_o : out  unsigned(31 downto 0)
        );
    END COMPONENT;
	 
COMPONENT RAM_II_2  --'test' is the name of the module needed to be tested.
    PORT(
         clk : IN  std_logic;
         adress : in  unsigned(39 downto 0);
         we : IN  std_logic;
			data_i : IN  unsigned(39 downto 0);
			data_o : out  unsigned(39 downto 0)
        );
    END COMPONENT;
   --declare inputs and initialize them
   signal clk : std_logic := '0';
   -- Clock period definitions
   constant clk_period : time := 1 ns;

	signal adress: unsigned(31 downto 0):=(others=>'0');
	signal adress_next: unsigned(31 downto 0):=(others=>'0');
	signal we: std_logic;
	signal data_i : unsigned(31 downto 0);
	signal data_o : unsigned(31 downto 0);
	signal termine : boolean;
   signal clock,endoffile : bit := '0';
	signal counter : std_logic :='0';






	signal adress_2 : unsigned(39 downto 0):=(others=>'0');
	signal adress_next_2: unsigned(39 downto 0):=(others=>'0');
   signal we_2 : std_logic;
	signal data_i_2 : unsigned(39 downto 0);
	signal data_o_2 : unsigned(39 downto 0);
	signal counter_2 : std_logic :='0';
	signal clock_2,endoffile_2 : bit := '0';
	signal termine_2 : boolean;


			
			
  BEGIN
  
		-- Instantiate the Unit Under Test UUT

		uut: ram_II PORT MAP (
			adress => adress,
         clk => clk,
			 we => we,
			 data_i => data_i,
			 data_o=>data_o
        );  

		uut_2: ram_II_2 PORT MAP (
			adress => adress_2,
         clk => clk,
			 we => we_2,
			 data_i => data_i_2,
			 data_o=>data_o_2
       );   


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
	adress_next_2<= adress_2 +1;

end process;

	
	


writing_RAM :
process
    file   infile    : text is in  "/user/6/guys/Bureau/PrjSpeFinal/PrjSpe/c/Detection/detection/img_II_short.txt";   --declare input file
    variable  inline    : line; --line number declaration
    variable  dataread1    : integer;
	 
begin


wait until clk = '1' and clk'event;
if (not endfile(infile)) then   --checking the "END OF FILE" is not reached.
	we <= '1';
	readline(infile, inline);       --reading a line from the file.
	read(inline, dataread1);
	data_i <=to_unsigned(dataread1,32);   --put the value available in variable in a signal.
	adress<=adress_next;

else
	we <= '0';
	termine <= true;
	if(counter = '0') then
		adress<=(others=>'0');
		counter <= '1';
	else 
		adress<=adress_next;
	end if;
	endoffile <='1';         --set signal to tell end of file read file is reached.
end if;
wait until clk = '1' and clk'event;

end process writing_RAM;






--Pour l'image intégrale carrée

writing_RAM_2 :
process
    file   infile    : text is in  "/user/6/guys/Bureau/PrjSpeFinal/PrjSpe/c/Detection/detection/img_II_2_short.txt";   --declare input file
    variable  inline    : line; --line number declaration
    variable  dataread1    : integer;
	 
begin


wait until clk = '1' and clk'event;
if (not endfile(infile)) then   --checking the "END OF FILE" is not reached.
	we_2 <= '1';
	readline(infile, inline);       --reading a line from the file.
	read(inline, dataread1);
	data_i_2 <=to_unsigned(dataread1,40);   --put the value available in variable in a signal.
	adress_2<=adress_next_2;

else
	we_2 <= '0';
	termine_2 <= true;
	if(counter_2 = '0') then
		adress_2<=(others=>'0');
		counter_2 <= '1';
	else 
		adress_2<=adress_next_2;
	end if;
	endoffile_2 <='1';         --set signal to tell end of file read file is reached.
end if;
wait until clk = '1' and clk'event;

end process writing_RAM_2;





  END;
