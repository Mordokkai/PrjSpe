---------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
library work;
use work.all;

entity ram is
    Port ( adress_I : in  unsigned (12 downto 0);
           in_I : in  signed (7 downto 0);
           we_I : in  STD_LOGIC;
           adress_II : in  unsigned (12 downto 0);
           in_II : in  signed (31 downto 0);
           we_II : in  STD_LOGIC;
           adress_II_sq : in  unsigned (12 downto 0);
           in_IIsq : in  signed (39 downto 0);
           we_II_sq : in  STD_LOGIC;
           out_I : out  signed (7 downto 0);
           out_II : out  signed (31 downto 0);
           out_IIsq : out  signed (29 downto 0);
			  clk : in std_logic;
           ping_pong : in  STD_LOGIC);

end ram;

architecture ram_arch of ram is

component ram_I is 
    Port ( clk : in  STD_LOGIC;
           adress : in  unsigned (12 downto 0);
           data_in : in  signed (7 downto 0);
           data_out : out  signed (7 downto 0);
           we : in  STD_LOGIC);
end component ram_I;

component ram_II is 
	 Port ( clk : in  STD_LOGIC;
           adress : in  unsigned (12 downto 0);
           data_in : in  signed (31 downto 0);
           data_out : out  signed (31 downto 0);
           we : in  STD_LOGIC);
end component ram_II;

component ram_II_sq is
	 Port ( clk : in  STD_LOGIC;
           adress : in  unsigned (12 downto 0);
           data_in : in  signed (39 downto 0);
           data_out : out  signed (39 downto 0);
           we : in  STD_LOGIC);
end component ram_II_sq;
	
signal data_in_I_1 : signed (7 downto 0);
signal data_in_I_2 : signed (7 downto 0);	
signal data_in_II_1: signed (31 downto 0);
signal data_in_II_2: signed (31 downto 0);
signal data_in_IIsq_1: signed (39 downto 0);
signal data_in_IIsq_2: signed (39 downto 0);
signal data_out_I_1 : signed (7 downto 0);
signal data_out_I_2 : signed (7 downto 0);	
signal data_out_II_1: signed (31 downto 0);
signal data_out_II_2: signed (31 downto 0);
signal data_out_IIsq_1: signed (39 downto 0);
signal data_out_IIsq_2: signed (39 downto 0);
signal we_I_1	:std_logic:='0';
signal we_I_2	:std_logic:='0';
signal we_II_1	:std_logic:='0';
signal we_II_2	:std_logic:='0';
signal we_IIsq_1	:std_logic:='0';
signal we_IIsq_2	:std_logic:='0';
		
begin

ram_I_1: ram_I port map(
		clk => clk,
		adress => adress_I,
		data_in => data_in_I_1,
		data_out => data_out_I_1,
		we => we_I_1
		);
ram_I_2: ram_I port map(
		clk => clk,
		adress => adress_I,
		data_in => data_in_I_2,
		data_out => data_out_I_2,
		we => we_I_2
		);

ram_II_1: ram_II port map(
		clk => clk,
		adress => adress_I,
		data_in => data_in_II_1,
		data_out => data_out_II_1,
		we => we_II_1
		);
		
ram_II_2: ram_II port map(
		clk => clk,
		adress => adress_I,
		data_in => data_in_II_2,
		data_out => data_out_II_2,
		we => we_II_2
		);
ram_IIsq_1: ram_II_sq port map(
		clk => clk,
		adress => adress_I,
		data_in => data_in_IIsq_1,
		data_out => data_out_IIsq_1,
		we => we_IIsq_1
		);
ram_IIsq_2: ram_II_sq port map(
		clk => clk,
		adress => adress_I,
		data_in => data_in_IIsq_2,
		data_out => data_out_IIsq_2,
		we => we_IIsq_2
		);
		
mux_ram_I: process(ping_pong, we_I, in_I, adress_I)
begin

	if(ping_pong='1') then
		if(we_I = '1')then
			we_I_1 <= we_I;
			we_I_2 <= '0';
			data_in_I_1<= in_I;
		else
			out_I <= data_out_I_2;
		end if; 
	else
		if(we_I ='1') then
			we_I_1<='0';
			we_I_2 <= we_I;
			data_in_I_2 <= in_I;
		else
			out_I <=data_out_I_1;
		end if;
	end if; 
end process mux_ram_I;

mux_ram_II: process(ping_pong, we_II, in_II, adress_II)
begin

	if(ping_pong='1') then
		if(we_II = '1')then
			we_II_1 <= we_II;
			we_II_2 <= '0';
			data_in_II_1<= in_II;
		else
			out_II <= data_out_II_2;
		end if; 
	else
		if(we_II ='1') then
			we_II_1<='0';
			we_II_2 <= we_II;
			data_in_II_2 <= in_II;
		else
			out_II <=data_out_II_1;
		end if;
	end if; 
end process mux_ram_II;

mux_ram_IIsq: process(ping_pong, we_II_sq, in_IIsq, adress_II_sq)
begin

	if(ping_pong='1') then
		if(we_II_sq = '1')then
			we_IIsq_1 <= we_II_sq;
			we_IIsq_2 <= '0';
			data_in_IIsq_1<= in_IIsq;
		else
			out_IIsq <= data_out_IIsq_2;
		end if; 
	else
		if(we_II_sq ='1') then
			we_IIsq_1<='0';
			we_IIsq_2 <= we_II_sq;
			data_in_IIsq_2 <= in_IIsq;
		else
			out_IIsq <=data_out_IIsq_1;
		end if;
	end if; 
end process mux_ram_IIsq;


end ram_arch;

