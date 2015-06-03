--Déclaration RAM_image

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
USE ieee.std_logic_unsigned.all;


entity ram_image is
port (Clk : in std_logic;
        address : in integer;
        we : in std_logic;
        data_i : in unsigned(7 downto 0);
        data_o : out unsigned(7 downto 0)
     );
end ram_image;

architecture Behavioral of ram_image is

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

end Behavioral;




library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
USE ieee.std_logic_unsigned.all;



--Déclaration RAM_II

entity ram_II is
port (Clk : in std_logic;
        address : in integer;
        we : in std_logic;
        data_i : in std_logic_vector(31 downto 0);
        data_o : out std_logic_vector(31 downto 0)
     );
end ram_II;

architecture Behavioral of ram_II is

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

end Behavioral;




library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
USE ieee.std_logic_unsigned.all;

--Déclaration RAM_II²

entity ram_II_2 is
port (Clk : in std_logic;
        address : in integer;
        we : in std_logic;
        data_i : in std_logic_vector(39 downto 0);
        data_o : out std_logic_vector(39 downto 0)
     );
end ram_II_2;

architecture Behavioral of ram_II_2 is

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

end Behavioral;





library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
USE ieee.std_logic_unsigned.all;


--Déclaration RAM_image_ping

entity ram_image_ping is
port (Clk : in std_logic;
        address : in integer;
        we : in std_logic;
        data_i : in std_logic_vector(7 downto 0);
        data_o : out std_logic_vector(7 downto 0)
     );
end ram_image_ping;

architecture Behavioral of ram_image_ping is

--Declaration of type and signal of a 256 element RAM
--with each element being 8 bit wide.
type ram_t is array (0 to 128*64) of std_logic_vector(7 downto 0);
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

end Behavioral;




library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
USE ieee.std_logic_unsigned.all;


--Déclaration RAM_II_ping

entity ram_II_ping is
port (Clk : in std_logic;
        address : in integer;
        we : in std_logic;
        data_i : in std_logic_vector(31 downto 0);
        data_o : out std_logic_vector(31 downto 0)
     );
end ram_II_ping;

architecture Behavioral of ram_II_ping is

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

end Behavioral;



library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
USE ieee.std_logic_unsigned.all;


--Déclaration RAM_II

entity ram_II_2_ping is
port (Clk : in std_logic;
        address : in integer;
        we : in std_logic;
        data_i : in std_logic_vector(39 downto 0);
        data_o : out std_logic_vector(39 downto 0)
     );
end ram_II_2_ping;

architecture Behavioral of ram_II_2_ping is

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

end Behavioral;




    
