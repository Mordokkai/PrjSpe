----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    15:59:47 06/02/2015 
-- Design Name: 
-- Module Name:    Frame_grabber - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
USE ieee.numeric_std.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity Frame_grabber is
    Port ( Din : in  unsigned (7 downto 0);
           Vsync : in  STD_LOGIC;
           Href : in  STD_LOGIC;
           CLK : in  STD_LOGIC;
           Det_end : in  STD_LOGIC;
			  RESET : in STD_LOGIC;
           Dout : out  unsigned (7 downto 0);
           Offset : out  unsigned (15 downto 0);
           We : out  STD_LOGIC;
           Image_ready : out  STD_LOGIC);
end Frame_grabber;

architecture Behavioral of Frame_grabber is
type State_type is (Init,
                      Lecture,
							 Wait_det
                      );

  signal current_state, next_state : State_type;
  --declaration des registres
  signal buff_offset, next_offset : unsigned (15 downto 0);
  
begin

	offset <= buff_offset;
	dout <= din;
	
	sync : process(clk) 
	begin
		if clk'event and clk='1' then
			if (RESET = '1') then
				current_state <= Init;
			else
				current_State <= next_state;
				buff_offset <= next_offset;
			end if;
		end if; 
	end process sync;

	FSM : process(current_state, Din, VSync, HREF, det_end)
	begin
		we <= '0';
		image_ready <= '0';
		case Current_State is
			when Init =>
				next_offset <= (others => '0');
				if (VSync='1') then
					next_state <= Lecture;
				else 
					next_state <= current_state;
				end if;
				
			when Lecture =>
				if (HREF = '1') then
					we <= '1';
					next_offset <= buff_offset + 1;
				end if;
				if (rising_edge(VSync)) then
					next_state <= Wait_det;
				else
					next_state <= current_state;
				end if;
			
			when Wait_det =>
				Image_ready <= '1';
				if (det_end = '1') then
					next_state <= Init;
				else
					next_state <= current_state;
				end if;
				
			when others =>
				null;
		end case;
					
	end process;

end Behavioral;

