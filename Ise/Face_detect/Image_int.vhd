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
           Image_i_ready : out  STD_LOGIC;
           Image_ic_ready : out  STD_LOGIC;
           Din_img : in  STD_LOGIC;
           Din_i : in  STD_LOGIC;
           Din_ic : in  STD_LOGIC;
           Dout_i : out  STD_LOGIC;
           Dout_ic : out  STD_LOGIC;
           Offset_lect_img : in  STD_LOGIC;
           Offset_ecr_int : in  STD_LOGIC;
           Offset_lect_int : in  STD_LOGIC;
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
  --declaration des registres
  signal r1_i,r1_ic,r2_i,r2_ic : integer;
begin

P_STATE : process(clk) 
	begin
     if clk'event and clk='1' then
      if (RST = '1') then
      current_state <= Init;
      else
      Current_State <= next_state;
		end if;
	  end if; 
   end process P_STATE;

P_FSM : process(current_state)
		-- declaration de variables
		variable Val_i : integer := 0;
		variable Val_ic : integer := 0;
		
    begin
    	-- initialisation des valeurs par defaut
		
		case Current_State is
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
				--declaration et affectation du registre r1 manque ici
				Dout_ic <= Val_ic;
				
				--incrementation de offsetlect_image
				
				
end Behavioral;
