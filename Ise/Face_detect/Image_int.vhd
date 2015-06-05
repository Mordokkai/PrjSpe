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
use IEEE.NUMERIC_STD.ALL;

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
           Din_i : in  unsigned (31 downto 0);
           Din_ic : in  unsigned (31 downto 0);
           Dout_i : out  unsigned (31 downto 0);
           Dout_ic : out  unsigned (31 downto 0);
           Offset_lect_img : out  unsigned (15 downto 0);
           Offset_ecr_int : out  unsigned (15 downto 0);
           Offset_lect_int : out  unsigned (15 downto 0);
           we_i : out  STD_LOGIC;
           we_ic : out  STD_LOGIC;
           Det_end : in  STD_LOGIC);
end Image_integrale;

architecture Behavioral of Image_integrale is
	type State_type is (Init,
                      Case_1,
                      Ligne_1,
                      Colonne_1,
                      ResteImage,
							 Wait_state
                      );

  signal current_state, next_state : State_type;
  --declaration de signaux pr incrementer les offsets
  signal buff_offset, next_offset : unsigned (15 downto 0);
  signal buff_offset_li, next_offset_li : unsigned (15 downto 0);
  signal buff_offset_ei, next_offset_ei : unsigned (15 downto 0);
  --declaration des registres
  signal r1_i,r1_ic,r2_i,r2_ic, next_r1_i, next_r1_ic : unsigned (31 downto 0);
  constant L : unsigned := to_unsigned(20,8); --valeur a modifier, nb de lignes de l'image
  constant C : unsigned := to_unsigned(30,8); --valeur a modifier, nb de col de l'image
begin
Offset_lect_img <= buff_offset;
Offset_ecr_int <= buff_offset_ei;
Offset_lect_int <= buff_offset_li;


P_STATE : process(clk) 
	begin
     if clk'event and clk='1' then
      if (RST = '1') then
      current_state <= Init;
      else
      Current_State <= next_state;
		buff_offset <= next_offset;
		buff_offset_li <= next_offset_li;
		buff_offset_ei <= next_offset_ei;
		r1_i <= next_r1_i;
		r1_ic <= next_r1_ic;
		end if;
	  end if; 
   end process P_STATE;

P_FSM : process(current_state,Image_ready,Din_img,Din_ic,Din_i,Det_end)
		-- declaration de variables
		variable Val_i : unsigned := to_unsigned(0,32);
		variable Val_ic : unsigned := to_unsigned(0,32); 
		
    begin
    	-- initialisation des valeurs par defaut
		we_i <= '0'; 
		we_ic <= '0';
		Image_int_ready <= '0';
		
		
		case current_State is
			when Init =>
					next_offset_li <= (others => '0');
					next_offset_ei <= (others => '0');
					next_offset <= (others => '0');
				if (Image_ready='1') then
					--incrementation de offsetlect_image
				
					next_offset <= buff_offset + 1;
				
					next_state <= Case_1;
				else 
					next_state <= current_state;
				end if;
				
			when Case_1 =>
				we_i <= '1';
				we_ic <= '1';
				Val_i := x"000000" & Din_img;
				Val_ic := x"0000" & (Din_img * Din_img);
				Dout_i <= Val_i;
				next_r1_i <= Val_i;
				Dout_ic <= Val_ic;
				next_r1_ic <= Val_ic;
				
				--incrementation de offset img et offset int
				
				next_offset <= buff_offset + 1;
				next_offset_ei <= buff_offset_ei + 1;
				
				next_state <= Ligne_1;
			
			when Ligne_1 =>
				we_i <= '1';
				we_ic <= '1';
				Val_i := Din_img + r1_i;
				Val_ic := Din_img * Din_img + r1_i;
				Dout_i <= Val_i;
				next_r1_i <= Val_i;
				Dout_ic <= Val_ic;
				next_r1_ic <= Val_ic;
				next_offset <= buff_offset + 1;
				next_offset_ei <= buff_offset_ei + 1;
				

				
				if (buff_offset < C) then
					next_state <= current_state; 
				else 
					next_offset_li <= buff_offset_li + 1;
					next_state <= Colonne_1;
				end if;
			
			when Colonne_1 =>
				we_i <= '1';
				we_ic <= '1';
				Val_i := Din_img + Din_i;
				Val_ic := Din_img * Din_img + Din_ic;
				Dout_i <= Val_i;
				next_r1_i <= Val_i;
				r2_i <= Din_i;
				Dout_ic <= Val_ic;
				next_r1_ic <= Val_ic;
				r2_ic <= Din_ic;
				--incrementation des 3 offsets
				
				next_offset <= buff_offset + 1;
				next_offset_ei <= buff_offset_ei + 1;
				next_offset_li <= buff_offset_li + 1;
				
				next_state <= ResteImage;
				
			when ResteImage =>
				we_i <= '1';
				we_ic <= '1';
				Val_i := Din_img + Din_i + r1_i - r2_i;
				Val_ic := Din_img * Din_img + Din_ic + r1_ic - r2_ic;
				-- cette partie n'est pas forcement juste----------ca m'a l'air bon
				Dout_i <= Val_i;
				next_r1_i <= Val_i;
				r2_i <= Din_i;
				Dout_ic <= Val_ic;
				next_r1_ic <= Val_ic;
				r2_ic <= Din_ic;
				---------------------------------------------------
				--incrementation des 3 offsets
				
				next_offset <= buff_offset + 1;
				next_offset_ei <= buff_offset_ei + 1;
				next_offset_li <= buff_offset_li + 1;
				-----------CA
--				if ((Offset_lect_img mod C = 0) and (Offset_lect_img < C*L)) then
--					next_state <= Colonne_1; 
--				elsif ((Offset_lect_img mod C /= 0) and (Offset_lect_img < C*L)) then
--					next_state <= Current_state;
--				else
--					next_state <= Wait_state;
--				end if;
				
				--------OU CA
				if (buff_offset = C*L) then
					next_state <= Wait_state;
				else
					if (buff_offset mod C = 0) then
						next_state <= Colonne_1;
					else
						next_state <= Current_state;
					end if;
				end if;
				-------------
				
				
			when Wait_state =>
				Image_int_ready <= '1';
				if (Det_end = '1') then
					next_offset_li <= (others => '0');
					next_offset_ei <= (others => '0');
					next_offset <= (others => '0');
					next_state <= Init; 
				else 
					next_state <= Current_state;
				end if;
				
			when others =>
				next_state <= current_state;
					
		end case;
	end process P_FSM;	
				
				
				
				
end Behavioral;
