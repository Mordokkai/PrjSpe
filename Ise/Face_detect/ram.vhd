--library IEEE;
--        use IEEE.std_logic_1164.all;
--        use IEEE.std_logic_textio.all;
--        use IEEE.std_logic_arith.all;
--        use IEEE.numeric_bit.all;
--        use IEEE.numeric_std.all;
--        use IEEE.std_logic_signed.all;
--        use IEEE.std_logic_unsigned.all;
--        use IEEE.math_real.all;
--        use IEEE.math_complex.all;
--
--        library STD;
--        use STD.textio;


--Déclaration RAM_image

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
USE ieee.std_logic_unsigned.all;
use ieee.numeric_std.all;


entity ram_image is
port (	clk : in std_logic;
			adress : in unsigned(31 downto 0);
			we : in std_logic;
			data_i : in unsigned(7 downto 0);
			data_o : out unsigned(7 downto 0)
     );
end ram_image;

architecture Behavioral1 of ram_image is

--Declaration of type and signal of a 256 element RAM
--with each element being 8 bit wide.
type ram_t is array (0 to 128*64) of unsigned(7 downto 0);
signal ram : ram_t := (others => (others => '0'));

begin

--process for read and write operation.
PROCESS(clk)
BEGIN
    if(rising_edge(clk)) then
        if(we='1') then
            ram(to_integer(adress)) <= data_i;
        end if;
        data_o <= ram(to_integer(adress));
    end if;
END PROCESS;

end Behavioral1;




library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
USE ieee.std_logic_unsigned.all;
use ieee.numeric_std.all;



--Déclaration RAM_II

entity ram_II is
port ( 	clk : in std_logic;
			adress : in integer;
			we : in std_logic;
			data_i : in unsigned(31 downto 0);
			data_o : out unsigned(31 downto 0)
     );
end ram_II;

architecture Behavioral2 of ram_II is

--Declaration of type and signal of a 256 element RAM
--with each element being 8 bit wide.
type ram_t is array (0 to 8192) of unsigned(31 downto 0);
signal ram : ram_t := (
0 => "00000000000000000000000000000001",
24 => "00000000000000000011000000001001",
3072 => "00000000000000000011000000001000",
3096 => "00000000000000000011000001001001",
772 => "00000000000000111110000001001001",
others => "00000000000000000000000000000000"
);

begin

--process for read and write operation.
PROCESS(clk)
BEGIN
    if(rising_edge(clk)) then
        if(we='1') then
            ram(adress) <= data_i;
        end if;
        data_o <= ram(adress);
    end if;
END PROCESS;

end Behavioral2;




library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
USE ieee.std_logic_unsigned.all;
use ieee.numeric_std.all;

--Déclaration RAM_II²

entity ram_II_2 is
port (	clk : in std_logic;
			adress : in integer;
			we : in std_logic;
			data_i : in unsigned(39 downto 0);
			data_o : out unsigned(39 downto 0)
     );
end ram_II_2;

architecture Behavioral3 of ram_II_2 is

--Declaration of type and signal of a 256 element RAM
--with each element being 8 bit wide.
type ram_t is array (0 to 128*64) of unsigned(39 downto 0);
signal ram : ram_t := (0 => "0000000000000000000000000000000000000001",
24 => 							 "0000000000000000000001100000000000001001",
3072 => 							 "0000000000000000000000000011000000001000",
3096 => 							 "0000000000000000000000000110000001001001",
772 => "0000000000000000000000111110000001001001",
						others => "0000000000000000000000000000000000000000"
);

begin

--process for read and write operation.
PROCESS(clk)
BEGIN
    if(rising_edge(clk)) then
        if(we='1') then
            ram(adress) <= data_i;
        end if;
        data_o <= ram(adress);
    end if;
END PROCESS;

end Behavioral3;





library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
USE ieee.std_logic_unsigned.all;
use ieee.numeric_std.all;

--Déclaration RAM_image_ping

entity ram_image_ping is
port (Clk : in std_logic;
        address : in integer;
        we : in std_logic;
        data_i : in unsigned(7 downto 0);
        data_o : out unsigned(7 downto 0)
     );
end ram_image_ping;

architecture Behavioral4 of ram_image_ping is

--Declaration of type and signal of a 256 element RAM
--with each element being 8 bit wide.
type ram_t is array (0 to 128*64) of unsigned(7 downto 0);
signal ram : ram_t := (others => (others => '0'));

begin

--process for read and write operation.
PROCESS(Clk)
BEGIN
    if(rising_edge(Clk)) then
        if(we='1') then
            ram(address) <= data_i;
        end if;
        data_o <= ram(address);
    end if;
END PROCESS;

end Behavioral4;




library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
USE ieee.std_logic_unsigned.all;
use ieee.numeric_std.all;


--Déclaration RAM_II_ping

entity ram_II_ping is
port (Clk : in std_logic;
        address : in integer;
        we : in std_logic;
        data_i : in std_logic_vector(31 downto 0);
        data_o : out std_logic_vector(31 downto 0)
     );
end ram_II_ping;

architecture Behavioral5 of ram_II_ping is

--Declaration of type and signal of a 256 element RAM
--with each element being 8 bit wide.
type ram_t is array (0 to 128*64) of std_logic_vector(31 downto 0);
signal ram : ram_t := (others => (others => '0'));

begin

--process for read and write operation.
PROCESS(Clk)
BEGIN
    if(rising_edge(Clk)) then
        if(we='1') then
            ram(address) <= data_i;
        end if;
        data_o <= ram(address);
    end if;
END PROCESS;

end Behavioral5;



library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
USE ieee.std_logic_unsigned.all;
use ieee.numeric_std.all;


--Déclaration RAM_II

entity ram_II_2_ping is
port (Clk : in std_logic;
        address : in integer;
        we : in std_logic;
        data_i : in std_logic_vector(39 downto 0);
        data_o : out std_logic_vector(39 downto 0)
     );
end ram_II_2_ping;

architecture Behavioral6 of ram_II_2_ping is

--Declaration of type and signal of a 256 element RAM
--with each element being 8 bit wide.
type ram_t is array (0 to 128*64) of std_logic_vector(31 downto 0);
signal ram : ram_t := (others => (others => '0'));

begin

--process for read and write operation.
PROCESS(Clk)
BEGIN
    if(rising_edge(Clk)) then
        if(we='1') then
            ram(address) <= data_i;
        end if;
        data_o <= ram(address);
    end if;
END PROCESS;

end Behavioral6;




    
