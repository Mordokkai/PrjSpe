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
							 Wait_Frame,
                      Lecture_High_First,
							 Lecture_Low,
							 Lecture_High,
							 Wait_det
                      );

  signal current_state, next_state : State_type;
  --declaration des registres
  signal buff_offset, next_offset : unsigned (15 downto 0);
  signal data, next_data : unsigned (7 downto 0);
  signal x, y, next_x, next_y : unsigned (14 downto 0);
  
  constant L : unsigned := to_unsigned(20,8); --valeur a modifier, nb de lignes de l'image
  constant C : unsigned := to_unsigned(30,8); --valeur a modifier, nb de col de l'image
  
begin

	offset <= buff_offset;
	
	sync : process(clk) 
	begin
		if clk'event and clk='1' then
			if (RESET = '1') then
				current_state <= Init;
			else
				current_State <= next_state;
				buff_offset <= next_offset;
				data <= next_data;
				x <= next_x;
				y <= next_y;
			end if;
		end if; 
	end process sync;

	FSM : process(current_state, Din, VSync, HREF, det_end, data, x, y)
		variable R, G, B : unsigned (7 downto 0);
	begin
		dout <= (others => '0');
		we <= '0';
		image_ready <= '0';
		next_offset <= buff_offset;
		next_state <= current_state;
		next_data <= data;
		next_x <= x;
		next_y <= y;
		
		case Current_State is
			when Init =>
				next_offset <= (others => '0');
				next_x <= (others => '0');
				next_y <= (others => '0');
				if (VSync='1') then
					next_state <= Wait_Frame;
				end if;
				
			when Wait_Frame =>
				if (VSync='0') then
					next_state <= Lecture_High_First;
				end if;
				
			when Lecture_High_First =>
				next_data <= Din;
				if (HREF = '1') then
					next_state <= Lecture_Low;
				end if;
				
			when Lecture_Low =>
				next_x <= x + 1;
				if ((x < C) and (y < L)) then
					next_offset <= buff_offset + 1;
					R := "000" & data(7 downto 3);
					G := "00" & data(2 downto 0) & din(7 downto 5);
					B := "000" & din(4 downto 0);
					dout <= R + G + B;
					we <= '1';
				end if;
				next_state <= Lecture_High;
			
			when Lecture_High =>
				next_data <= din;
				if (HREF = '1') then			
					next_state <= Lecture_Low;
				else
					if (y < (L - 1)) then
						next_x <= (others => '0');
						next_y <= y + 1;
						next_state <= Lecture_High_First;
					else
						next_state <= Wait_det;						
					end if;
				end if;
			
			when Wait_det =>
				Image_ready <= '1';
				if (det_end = '1') then
					next_state <= Init;
				end if;
				
		end case;
					
	end process;

end Behavioral;

