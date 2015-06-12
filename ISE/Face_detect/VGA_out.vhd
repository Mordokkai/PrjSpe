----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    10:21:57 06/10/2015 
-- Design Name: 
-- Module Name:    VGA_out - Behavioral 
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

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;
 
entity VGA_out is
    Port ( CLK : in  STD_LOGIC;
           Din : in  unsigned (7 downto 0);
           HSync : out  STD_LOGIC;
           VSync : out  STD_LOGIC;
           R : out  unsigned (4 downto 0);
           G : out  unsigned (5 downto 0);
           B : out  unsigned (4 downto 0);
           Offset : out  unsigned (15 downto 0));
end VGA_out;

architecture Behavioral of VGA_out is

	constant HM: unsigned := to_unsigned(799,10);		-- Taille max horizontale
	constant HB: unsigned := to_unsigned(48,10);		-- Back porch horizontal
	constant HP: unsigned := to_unsigned(96,10);		-- Pulse horizontal
	constant VM: unsigned := to_unsigned(523,10);		-- Taille max verticale
	constant VB: unsigned := to_unsigned(31,10);		-- Back porch vertical
	constant VP: unsigned := to_unsigned(2,10);			-- Pulse vertical
	
	constant L : unsigned := to_unsigned(100,8); --valeur a modifier, nb de lignes de l'image
	constant C : unsigned := to_unsigned(100,8); --valeur a modifier, nb de col de l'image
	
	signal buff_offset, next_offset : unsigned (15 downto 0) := (others => '0');

	signal activeArea : std_logic;
	constant Hstart_img : unsigned := HP+HB;
	constant Vstart_img : unsigned := VP+VB;
	
	signal Hcnt, Vcnt : unsigned (10 downto 0) := (others => '0');
	signal x, y, next_x, next_y : unsigned (14 downto 0) := (others => '0');
	signal Hsync_temp, Vsync_temp : STD_LOGIC := '0';
	signal activeArea_h, activeArea_v : std_logic;

begin

	Offset <= buff_offset;

--	process(activeArea, Din)
--	begin
--		if (activeArea = '1') then
--			R <= Din(7 downto 3);
--			G <= Din(7 downto 2);
--			B <= Din(7 downto 3);
--   	else
--   		R <= "00000";
--   		G <= "000000";
--   		B <= "00000";
--   	end if;
--   	
--   end process;

-- Compteur et génération addresses
	process(clk)
	begin
		if rising_edge(clk) then
			if (Hcnt <= HM) then
				Hcnt <= Hcnt+1;
			else
				Hcnt <= (others => '0');
				if (Vcnt <= VM) then
					Vcnt <= Vcnt+1;
				else
					Vcnt <= (others => '0');
					buff_offset <= (others => '0');
				end if;
			end if;
			Hsync <= Hsync_temp;
			Vsync <= Vsync_temp;
			x <= next_x;
			y <= next_y;
			if (activeArea = '1') then
				R <= Din(7 downto 3);
				G <= Din(7 downto 2);
				B <= Din(7 downto 3);
			else
				R <= "00000";
				G <= "000000";
				B <= "00000";
			end if;
			activeArea <= activeArea_v and activeArea_h;
			if (activeArea_v = '1' and activeArea_h = '1') then
				buff_offset <= next_offset;
			end if;
		end if;
	end process;

	process(Hcnt, buff_offset)
	begin
		if (Hcnt >= Hstart_img and Hcnt < C + Hstart_img) then -- 144 <= Hcnt <= 783
			activeArea_h <= '1';
			next_x <= "0000" & Hcnt-Hstart_img; -- Décompte de horizontal pulse et backporch
			next_offset <= buff_offset + 1;
		else
			activeArea_h <= '0';
			next_x <= (others => '0');
			next_offset <= buff_offset;
		end if;
	end process;

	process(Vcnt)
	begin
		if (Vcnt >= Vstart_img and Vcnt < L + Vstart_img) then -- 33 <= Vcnt <= 512
			activeArea_v <= '1';
			next_y <= "0000" & Vcnt-Vstart_img; -- Décompte de vertical pulse et backporch
		else
        	activeArea_v <= '0';
       	next_y <= (others => '0');
		end if;
	end process;  

-- Génération Hsync
	process(Hcnt)
	begin
		if (Hcnt >= HP and Hcnt <= HM) then -- 96 <= Hcnt <= 799
			Hsync_temp <= '1';
		else
			Hsync_temp <= '0';
		end if;
	end process;

-- Génération Vsync
	process(Vcnt)
	begin
		if (Vcnt >= VP and Vcnt <= VM) then -- 2 <= Vcnt <= 523
			Vsync_temp <= '1';
		else
			Vsync_temp <= '0';
		end if;  		
	end process;
	
end Behavioral;
