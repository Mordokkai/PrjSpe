----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity ram_II_sq is
    Port ( clk : in  STD_LOGIC;
           adress : in  unsigned (12 downto 0);
           data_in : in  signed (39 downto 0);
           data_out : out  signed (39 downto 0);
           we : in  STD_LOGIC);
end ram_II_sq;

architecture ram_II_sq_arch of ram_II_sq is

type ram is array (0 to 2**13) of signed (39 downto 0);
signal ram_img : ram := (others => (others=>'0'));

begin
	
process(clk)
begin
	if(clk'event and clk='1') then
		if we='1' then 
			ram_img(to_integer(adress)) <= data_in;
		else
			data_out <= ram_img(to_integer(adress));
		end if;
	end if;
end process;


end ram_II_sq_arch;

