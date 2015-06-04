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
					
					--Communications avec les RAMS
					we_stage : out std_logic
					ad_stage : out integer;
					datao_stage : in unsigned(31 downto 0);
					
					we_feature : out std_logic;
					ad_feature : out std_logic;
					datao_feature : in unsigned(59 downto 0);

					we_rectangle : out std_logic;
					ad_rectangle : out std_logic;
					datao_rectangle : in unsigned(31 downto 0);

					we_II	: out std_logic;
					ad_II:	out integer;
					datao_II: in unsigned(31 downto 0);
					
					ad_II_2: out integer;
					we_II_2 : out std_logic;
					datao_II_2: in unsigned(39 downto 0);

          face_detected : out  STD_LOGIC;
          send_img : out  STD_LOGIC);
end fsm_detection;

architecture Behavioral of fsm_detection is

type   STATE is (Wait_RDY, Place_Detector, Req_s, Req_meanvar, D_meanvar, Req_f, Req_r, D_r, RAM_II, Eval_f, Eval_s);
    	signal Current_State, Next_State   : STATE;
    	signal access_count, access_count_next : std_logic_vector(3 downto 0);
    	signal if_q, if_d : integer;
    	signal is_q, is_d : integer;
			signal ir_q, ir_d : integer;
			signal ik_q, ik_d : integer;
			signal l_q, l_d : integer;
			signal m_q, m_d : integer);
			signal mean_q, mean_d: Mean;
			signal var_q, var_d: Var;
			signal r_q, r_d: R;
			signal rect_q,rect_d: Rectangles;
			signal sums_q,sums_d: integer;
			signal sumf_q,sumf_d: integer;
			signal img_Termine_q, img_Termine_d : boolean;
			signal det_q,det_d : Detector;
			signal s_q, s_d: Stage;
			signal f_q, f_d: Feature;

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
				det_q <= det_d;
				s_q <= s_d;
				f_q <= f_d;
			end if;
		end if;
   end process P_STATE;

  


	P_FSM : process(clk)
	variable calcul : integer;
	variable Stage_OK : boolean;
   begin
     	case current_state is 		
					
			when Wait_RDY => 
				if(Image_int_ready) then
					next_state <= Place_Detector;
				else 
					--On positionne le détecteur à sa position initiale
					det_d.x <= 24;
					det_d.y <= 0;
					next_state <= Wait_RDY;
				end if;

					

			when Place_Detector =>
			--Deplacement du détecteur
				if(det_q.y > IMG_WIDTH-24) then
					det_d.x <= det_q.x+1;
					det_d.y <= 0;
				else 
					det_d.y <= det_q.y+1;
				end if; 
			--Changement d'état
				if(det_q.x=IMG_HEIGHT and det_q.y=IMG_WIDTH-24) then
					img_Termine_d <= true;
				else
					img_Termine_d <= false;
				end if;
				is_d <= 0;
				next_state <= Req_s;

					
					
			when Req_s =>
			--Récupération des valeurs
				we_stage <= '0';
				ad_stage <= is_d;
				we_II <= 0;
				ad_II <= (det_q.x)*IMG_WIDTH+det_q.y; -- Le coin en bas à gauche du détecteur
				we_II_2 <= 0;
				ad_II_2 <= (det_q.x)*IMG_WIDTH+det_q.y; --idem
					
				--Changement d'état
				ik_d <= 0;
				next_state <= Req_meanvar;


			when Req_meanvar =>
			--Récupération des valeurs
				--s <= datao_stage;--A détailler
				s.threshold <= datao_stage(31 downto 12);
				s.ad_feature <= datao_stage(11 downto 0);
				mean_d(ik_q) <= datao_II;
				var_d(ik_q) <= datao_II_2;
				we_II <= 0;
				ad_II <= (det_q.x - 24* m_q)*IMG_WIDTH+det_q.y + 24*l_q;
				we_II_2 <= 0;
				ad_II_2 <= (det_q.x - 24*m_q)*IMG_WIDTH+det_q.y + 24*l_q;
						
			--Changement d'état
				if(ik_q<3) then
					if(ik_q = 0) then
						m_d <= 0;
						l_d <= 1;
					elsif(ik_q = 1) then
						m_d <= 1;
						l_d <= 0;
					elsif(ik_q = 2) then
						m_d <= 1;
						l_d <= 1;
					end if;
					ik_d <= ik_q+1;
					next_state <= Req_meanvar;
				else
					is_d <= is_q + 1;
					sums_d <= 0;
					next_state <= D_meanvar;
				end if;


			

			when D_meanvar =>	--Etape de transition
			--Récupération des valeurs
				mean_d(ik_q) <= datao_II;
				var_d(ik_q) <= datao_II_2;

			--Changement d'état
				if_d <= 0;
				next_state <= Req_f;


			when Req_f =>
			--Récupération des valeurs
				we_feature <= 0;
				ad_feature <= s_q.ad_feature + if_q;

			--Changement d'état
				if_d <= if_q +1;
				ir_d <= 0;
				sumf_d <= 0;
				next_state <= Req_r;
						


			when Req_r =>
			--Récupération des valeurs
				--f <= datao_feature;--A detailler
				f_d.threshold <= datao_feature(59 downto 44);
				f_d.greater <= datao_feature(27 downto 12);
				f_d.lower <= datao_feature(43 downto 28);
				f_d.ad_rectangle <= datao_feature(11 downto 0);
				next_state <= D_f;
				
			when D_f =>
				we_rectangle <= 0;
				ad_rectangle <= f.ad_rectangle + ir_q;
				
			--Changement d'état
				if(ir_q < f_q.nr) then
					access_count_next <= 0;
					next_state <= D_r;
				else
					next_state <= Eval_f;
				end if;
				

			when D_r =>
				--r(ir_q) <= datao_rectangle;
				--we_II <= 0;
				--ad_II <= r(ir_q) srl (12+5*z_q);	
				--z_d <= z_q -1;
				--next_state <= RAM_II;
				rect_d(ir_q).x <= datao_rectangle(31 downto  27);
				rect_d(ir_q).y <= datao_rectangle(26 downto  22);
				rect_d(ir_q).h <= datao_rectangle(21 downto  17);
				rect_d(ir_q).w <= datao_rectangle(16 downto  12);
				rect_d(ir_q).weight <= datao_rectangle(11 downto  0);
				next_state <= RAM_II;

			when RAM_II =>
				--r_d(access_count_q) <= datao_II;
				we_II <= 0;
				if(access_count = 0) then
					ad_II <= (det_q.x - rect_q.x) * IMG_WIDTH + (det_q.y + rect_q.y) ; 
				elsif(access_count = 1) then
					ad_II <= (det_q.x - rect_q.x - rect_q.h) * IMG_WIDTH + (det_q.y + rect_q.y); 
				elsif(access_count = 2) then
					ad_II <= (det_q.x - rect_q.x) * IMG_WIDTH + (det_q.y + rect_q.y + rect_q.w); 
				elsif(access_count = 3) then
					ad_II <= (det_q.x - rect_q.x - rect_q.h) * IMG_WIDTH + (det_q.y + rect_q.y + rect_q.w); 
				end if;
				
				if(access_count_q <4) then 
					access_count_d <= access_count_q+1;
					next_state <= RAM_II;
				else
					ir_d <= ir_q +1 ;
					next_state <= D_f;
				end if;
			
			
			when Eval_f => 
				--Calcul
				calcul := FeatureEval(r_q,rect_q);			
				if(calcul < f_d.threshold) then
					sumf_d <= sumf_q + f_d.greater;
				else
					sumf_d <= sumf_q + f_d.lower;
				end if;
 				--Changement d'état
				if(if_q < s_d.nf) then
					next_state <= Req_f;
				else
					next_state <= Eval_s;
				end if;
				
			when Eval_s =>
				if(sumf_d > s_d.threshold) then
					Stage_OK := true;
				if(is_q < Ns and Stage_OK) then --TODO
					next_state <= Req_s;
				elsif (is_q=Ns) then
					face_detected <= true;
					next_state <= Place_Detector;
				elsif (not Stage_OK) then
					face_detected <= false;
					next_state <= Place_Detector;
				else
					img_Termine <= true;
					next_state <= Wait_RDY;
				end if;
					
			when others => next_state <= current_state;

			end case;
		end process P_FSM;
end  Behavioral;
