----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    11:43:37 06/02/2015 
-- Design Name: 
-- Module Name:    Image_integrale - Behavioral 
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
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity Image_integrale is
    Port ( CLK : in  STD_LOGIC;
           RST : in  STD_LOGIC;
           Image_ready : in  STD_LOGIC;
           Image_int_ready : out  STD_LOGIC;
           Din_img : in  unsigned (7 downto 0);
           Din_i : in  unsigned (7 downto 0);
           Din_ic : in  unsigned (7 downto 0);
           Dout_i : out  unsigned (7 downto 0);
           Dout_ic : out  unsigned (7 downto 0);
           Offset_lect_img : out  unsigned (15 downto 0);
           Offset_ecr_int : out  unsigned (15 downto 0);
           Offset_lect_int : out  unsigned (15 downto 0);
           we2 : out  STD_LOGIC;
           we3 : out  STD_LOGIC;
           Det_end : in  STD_LOGIC);
end Image_integrale;

architecture Behavioral of Image_integrale is
	type State_type is (Init,
                      Case1,
                      Ligne1,
                      Colonne1,
                      ResteImage,
							 Wait_state
                      );

  signal current_state, next_state : State_type;
  --declaration de signaux pr incrementer les offsets
  signal buff_offset, next_offset : unsigned (15 downto 0);
  --declaration des registres
  signal r1_i,r1_ic,r2_i,r2_ic : integer;
  constant L : integer := 20; --valeur a modifier, nb de lignes de l'image
  constant C : integer := 30; --valeur a modifier, nb de col de l'image
begin

P_STATE : process(clk) 
	begin
     if clk'event and clk='1' then
      if (RST = '1') then
      current_state <= Init;
      else
      Current_State <= next_state;
		buff_offset <= next_offset;
		end if;
	  end if; 
   end process P_STATE;

P_FSM : process(current_state)
		-- declaration de variables
		variable Val_i : integer := 0;
		variable Val_ic : integer := 0; 
		
    begin
    	-- initialisation des valeurs par defaut
		next_offset <= 0;
		
		case current_State is
			when Init =>
				if (Image_ready='1') then
					Offset_lect_img <= 0;
					Offset_ecr_int <= 0;
					Offset_lect_int <= 0;
					next_state <= Case_1;
				else 
					next_state <= current_state;
				end if;
				
			when Case_1 =>
				we_i <= 0;
				we_ic <= 0;
				Val_i := Din_img;
				Val_ic := Din_img * Din_img;
				Dout_i <= Val_i;
				r1_i <= Val_i;
				Dout_ic <= Val_ic;
				r1_ic <= Val_ic;
				
				--incrementation de offsetlect_image
				
				next_offset <= buff_offset + 1;
				Offset_lect_img <= buff_offset + 1;
				
				next_state <= Ligne_1;
			
			when Ligne_1 =>
				we_i <= 1;
				we_ic <= 1;
				Val_i := Din_img + r1_i;
				Val_ic := Din_img * Din_img + r1_i;
				Dout_i <= Val_i;
				r1_i <= Val_i;
				Dout_ic <= Val_ic;
				r1_ic <= Val_ic;
				--incrementation de offset img et offset int
				
				next_offset <= buff_offset + 1;
				Offset_lect_img <= buff_offset + 1;
				Offset_ecr_int <= buff_offset + 1;

				
				if (Offset_lect_img < C) then
					next_state <= current_state; 
				else 
					next_state <= Colonne_1;
				end if;
			
			when Colonne_1 =>
				we_i <= 1;
				we_ic <= 1;
				Val_i := Din_img + Din_i;
				Val_ic := Din_img * Din_img + Din_ic;
				Dout_i <= Val_i;
				r1_i <= Val_i;
				r2_i <= Din_i;
				Dout_ic <= Val_ic;
				r1_ic <= Val_ic;
				r2_ic <= Din_ic;
				--incrementation des 3 offsets
				
				next_offset <= buff_offset + 1;
				Offset_lect_img <= buff_offset + 1;
				Offset_ecr_int <= buff_offset + 1;
				Offset_lect_int <= buff_offset + 1;
				
				next_state <= ResteImage;
				
			when ResteImage =>
				we_i <= 1;
				we_ic <= 1;
				Val_i := Din_img + Din_i + r1_i - r2_i;
				Val_ic := Din_img * Din_img + Din_ic + r1_ic - r2_ic;
				-- cette partie n'est pas forcement juste----------
				Dout_i <= Val_i;
				r1_i <= Val_i;
				r2_i <= Din_i;
				Dout_ic <= Val_ic;
				r1_ic <= Val_ic;
				r2_ic <= Din_ic;
				---------------------------------------------------
				--incrementation des 3 offsets
				
				next_offset <= buff_offset + 1;
				Offset_lect_img <= buff_offset + 1;
				Offset_ecr_int <= buff_offset + 1;
				Offset_lect_int <= buff_offset + 1;
				
				if ((Offset_lect_img mod C = 0) and (Offset_lect_img < C*L)) then
					next_state <= Colonne_1; 
				elsif ((Offset_lect_img mod C /= 0) and (Offset_lect_img < C*L)) then
					next_state <= Current_state;
				else
					next_state <= Wait_state;
				end if;
				
			when Wait_state =>
				Image_int_ready <= 1;
				if (Det_end = 1) then
					next_state <= Init; 
				else 
					next_state <= Current_state;
				end if;
				
			when others =>
				next_state <= current_state;
					
		end case;
	end process P_FSM;	
				
				
				
				
end Behavioral;
