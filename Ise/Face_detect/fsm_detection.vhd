----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    16:01:45 06/04/2015 
-- Design Name: 
-- Module Name:    fsm_detection - Behavioral 
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

entity fsm_detection is
    Port ( Image_int_ready : in  STD_LOGIC;
           clk : in  STD_LOGIC;
           rst : in  STD_LOGIC;
           face_detected : out  STD_LOGIC;
           send_img : out  STD_LOGIC);
end fsm_detection;

architecture Behavioral of fsm_detection is

type   STATE is (Wait_RDY, Place_Detector, Req_s, Req_meanvar, D_meanvar, Req_f, Req_r, D_r, RAM_II, Eval_f, Eval_s);
    	signal Current_State, Next_State   : STATE;
    	signal access_count, access_count_next : std_logic_vector(3 downto 0);
    	signal if_q, if_d : std_logic_vector(11 downto 0);
    	signal is_q, is_d : std_logic_vector(5 downto 0);
		signal ir_q, ir_d : std_logic_vector(2 downto 0);
		signal ik_q, ik_d : std_logic_vector(2 downto 0);
		signal l_q, l_d : std_logic_vector(2 downto 0);
		signal m_q, m_d : std_logic_vector(2 downto 0);
		signal mean_q, mean_d: Mean;
		signal var_q, var_d: Var;
		signal r_q, r_d: R;
		signal rect_q,rect_d: Rects;
		signal sums_q,sums_d: integer;
		signal sumf_q,sumf_d: integer;
		signal img_Termine : boolean;
		signal det_q,det_d : Detector;
		signal s_q, s_d: unsigned(31 downto 0);
		signal f_q, f_d: unsigned(31 downto 0);
		signal z_q, z_d: integer;
			
begin

	P_STATE : process(clk)
	begin
		if rising_edge(clk) then
			if (RESET = '1') then
				current_state <= Wait_RDY;
       
			else
            access_count <= access_count_next;
				if_q <= if_d;
				is_q <= is_d;
				ir_q <= ir_d;
				ik_q <= ik_d;
				l_q <= l_d;
				m_q <= m_d;
				mean_q <= mean_d;
				var_q <= var_d;
				r_q <= r_d;
				rect_q <= rect_d;
				sums_q <= sums_d;
				sumf_q <= sumf_d;
				img_Termine_q <= img_Termine_d;
      		Current_State <= Next_State;
				s_q <= s_d;
				f_q <= f_d;
				z_q <= z_d;
			end if;
		end if;
   end process P_STATE;

   
--type   STATE is (Wait_RDY, Place_Detector, Req_s, Req_meanvar, D_meanvar, Req_f, Req_r, RAM_II, Eval_f, Eval_s);


	P_FSM : process(clk)
	
	variable stage_OK : boolean;
   begin
     	case current_state is 		
					
			when Wait_RDY => 
				if(Image_int_ready) then
					next_state <= Place_Detector;
				else 
					next_state <= Wait_RDY;
				end if;

					

			when Place_Detector =>
			--Deplacement du détecteur
				if(det_q.y > W-24) then
					det_d.x <= det_q.x+1;
					det_d.y <= 0;
				else 
					det_d.y <= det_q.y+1;
				end if; 
			--Changement d'état
				if(det_q.x=L-24 and det_q.y=W-25) then
					img_Termine_d <= true;
				else
					img_Termine_d <= false;
				end if;
				next_state <= Req_s;

					
					
			when Req_s =>
			--Récupération des valeurs
				we_stage <= 0;
				ad_stage <= is_d;
				we_II <= 0;
				ad_II <= (det_q.x+1)*W+det_q.y+1;
				we_II_2 <= 0;
				ad_II_2 <= (det_q.x+1)*W+det_q.y+1;
					
				--Changement d'état
				ik_d <= 0;
				next_state <= Req_meanvar;


			when Req_meanvar =>
			--Récupération des valeurs
				s <= datao_stage;
				mean_d(ik_q) <= datao_II;
				var_d(ik_q) <= datao_II_2;
				we_II <= 0;
				ad_II <= (det_q.x+1)*W+det_q.y+1+24*abs(l_q)+24*W*m_q;
				we_II_2 <= 0;
				ad_II_2 <= (det_q.x+1)*W+det_q.y+1+24*abs(l_q)+24*W*m_q;
						
			--Changement d'état
				if(ik_q<3) then
					ik_d <= ik_q+1;
					l_d <= l_q+1;
					if(m=0) then m_d <= "001"; end if;
					next_state <= Req_meanvar;
				else
					ik_d <= ik_q+1;
					is_d <= is_q + 1;
					sums_d <= 0;
					next_state <= D_meanvar;
				end if;


			

			when D_meanvar =>
			--Récupération des valeurs
				mean_d(ik_q) <= datao_II;
				var_d(ik_q) <= datao_II_2;

			--Changement d'état
				if_d <= 0;
				next_state <= Req_f;


			when Req_f =>
			--Récupération des valeurs
				we_feature <= 0;
				ad_feature <= s_q sll 12 + if_q;

			--Changement d'état
				if_d <= if_q +1;
				ir_d <= 0;
				sumf_d <= 0;
				next_state <= Req_r;
						


			when Req_r =>
			--Récupération des valeurs
				f <= datao_feature;
				we_rectangle <= 0;
				ad_rectangle <= f sll 12 + ir_d;

			--Changement d'état
				if(ir_q < Nr) then
					access_count_next <= 0;
					z_d <= 3;
					next_state <= D_r;
				else
					next_state <= Eval_f;
				end if;
				

			when D_r =>
				r(ir_q) <= datao_rectangle;
				we_II <= 0;
				ad_II <= r(ir_q) srl (12+5*z_q);	
				z_d <= z_q -1;
				next_state <= RAM_II;


			when RAM_II =>
				Rect_d(access_count_q) <= datao_II;
				we_II <= 0;
				ad_II <= r(ir_q) srl (12+5*z_q); --à modifier
					
				z_d <= z_q-1;
				if(access_count_q <4) then 
					access_count_d <= access_count_q+1;
					z_d <= z_q -1;
					next_state <= RAM_II;
				else
					ir_d <= ir_q +1 ;
					next_state <= Req_r;
				end if;
			
			
			when Eval_f => 
				--TODO
				if(if_q < Nf) then
					next_state <= Req_f;
				else
					next_state <= Eval_s;
				end if;
				
			when Eval_s =>
				if(is_q < Ns and Stage_OK) then
					next_state <= Req_s;
				elsif (is=Ns) then
					face_detected <= true;
					next_state <= Place_Detector;
				elsif (not Stage_OK) then
					face_detected <= false;
					next_state <= Place_Detector;
				else
					img_Termine <= true;
					next_state <= Wait_RDY;
				end if;
					
			-- TODO

			when others => next_state <= current_state;
			end case;
		end process P_FSM;
end  Behavioral;