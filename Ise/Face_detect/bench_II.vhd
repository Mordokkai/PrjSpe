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


  BEGIN
  
		-- Instantiate the Unit Under Test UUT

		uut: ram_II PORT MAP (
			adress => adress,
         clk => clk,
			 we => we,
			 data_i => data_i,
			 data_o=>data_o
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








  END;
