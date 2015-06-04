//Déclaration RAM_image

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity ram_image is
port (Clk : in std_logic;
        address : in integer;
        we : in std_logic;
        data_i : in std_logic_vector(7 downto 0);
        data_o : out std_logic_vector(7 downto 0)
     );
end ram_example;

architecture Behavioral of ram_image is

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



//Déclaration RAM_II

entity ram_II is
port (Clk : in std_logic;
        address : in integer;
        we : in std_logic;
        data_i : in std_logic_vector(31 downto 0);
        data_o : out std_logic_vector(31 downto 0)
     );
end ram_example;

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


//Déclaration RAM_II²

entity ram_II_2 is
port (Clk : in std_logic;
        address : in integer;
        we : in std_logic;
        data_i : in std_logic_vector(39 downto 0);
        data_o : out std_logic_vector(39 downto 0)
     );
end ram_example;

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


//Déclaration RAM_image_ping

entity ram_image_ping is
port (Clk : in std_logic;
        address : in integer;
        we : in std_logic;
        data_i : in std_logic_vector(7 downto 0);
        data_o : out std_logic_vector(7 downto 0)
     );
end ram_example;

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


//Déclaration RAM_II_ping

entity ram_II_ping is
port (Clk : in std_logic;
        address : in integer;
        we : in std_logic;
        data_i : in std_logic_vector(31 downto 0);
        data_o : out std_logic_vector(31 downto 0)
     );
end ram_example;

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



//Déclaration RAM_II

entity ram_II_2_ping is
port (Clk : in std_logic;
        address : in integer;
        we : in std_logic;
        data_i : in std_logic_vector(39 downto 0);
        data_o : out std_logic_vector(39 downto 0)
     );
end ram_example;

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












   
//Machine à état




library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity fsm is
    port(
        CLK                     : in  std_logic;
        RESET                   : in  std_logic;
				img_ready								:	in	std_logic;
				face_detected		: out boolean;
				send_img		: out boolean;
        ) ;
end fsm;


architecture A of FSM is
    	type   STATE is (Wait_RDY, Place_Detector, Req_s, Req_meanvar, D_meanvar, Req_f, Req_r, RAM_II, Eval_f, Eval_s);
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
      current_state <= Wait0;
       
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

   
type   STATE is (Wait_RDY, Place_Detector, Req_s, Req_meanvar, D_meanvar, Req_f, Req_r, RAM_II, Eval_f, Eval_s);


        P_FSM : process(current_state,access_count,if,is,img_RDY)
    	begin
        
	variable stage_OK : boolean;
	
     	case current_state is
       		when Wait_RDY => 
						if(img_rdy) then
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
						mean_d[ik_q] <= datao_II;
						var_d[ik_q] <= datao_II_2;
						we_II <= 0;
						ad_II <= (det_q.x+1)*W+det_q.y+1+24*abs(l_q)+24*W*m_q;
						we_II_2 <= 0;
						ad_II_2 <= (det_q.x+1)*W+det_q.y+1+24*abs(l_q)+24*W*m_q;
						
						--Changement d'état
						if(ik_q<3) then
								ik_d <= ik_q+1;
								l_d <= l_q+1;
								if(m=0) m_d <= 1;
								next_state <= Req_meanvar;
						else
								ik_d <= ik_q+1;
								is_d <= is_q + 1;
								sums_d <= 0;
								next_state <= D_meanvar;
						end if;


			

					when D_meanvar =>
						--Récupération des valeurs
						mean_d[ik_q] <= datao_II;
						var_d[ik_q] <= datao_II_2;

						--Changement d'état
						if_d <= 0;
						next_state <= Req_f;



					when Req_f =>
						--Récupération des valeurs
						we_feature <= 0;
						ad_feature <= s_q<<12 + if_q;

						--Changement d'état
						if_d <= if_q +1;
						ir_d <= 0;
						sumf_d <= 0;
						next_state <= Req_r;
						


					when Req_r =>
						--Récupération des valeurs
						f <= datao_feature;
						we_rectangle <= 0;
						ad_rectangle <= f<<12 + ir_d;

						--Changement d'état
						access_count_next <= 0;
						z_d <= 3;
						next_state <= RAM_II;



					when RAM_II =>
						r <= datao_rectangle;
						-- TODO








end process P_FSM;



//Trdauction du c vers vhdl
/* calcul l'intégrale sur un carre de coin x, y et de largeur (tx,ty) */
4 signaux de valeurs récupérer depuis ram_img
    FUNCTION img_rect(L1 : IN std_logic_vector(7 downto 0); 
        L2 : IN std_logic_vector(7 downto 0);
	L3 : IN std_logic_vector(7 downto 0);
	L4 : IN std_logic_vector(7 downto 0)
    ) RETURN integer;

BEGIN
	RETURN L4-L3-L2+L1;
END img_rect;




//Process d'évaluation du stage
il faut la valeur des sommes des features
il faut la valeur du seuil du stage
 FUNCTION eval_Stage(sum_s: INTEGER
    ) RETURN Boolean;

BEGIN
	RETURN (sum_s < seuil);
END eval_Stage;
   









//Evaluate feature
il faut l'ancienne valeur du feature prev_f
il faut les v0 et v1
il faut la valeur totale de l'image intégrale carrée sur le pixel  =sq_mean
il faut la surface du pixel = area
il faut les 4 valeurs des rectangles = R1,R2,R3,R4
il faut les poids des 4 rectangles = P1,P2,P3,P4;
il faut le seuil du feature = seuil
use IEEE.MATH_REAL.ALL;

 FUNCTION eval_Feature(prev_f: INTEGER;
			v0: INTEGER;
			v1: INTEGER;
			sq_mean: INTEGER;
			mean: INTEGER;
			R1: INTEGER;
			R2: INTEGER;
			R3: INTEGER;
			R4: INTEGER;
			P1: INTEGER;
			P2: INTEGER;
			P3: INTEGER;
			P4: INTEGER;
			seuil: INTEGER;
    ) RETURN integer;
variable variance_sq: INTEGER;
variable variance: INTEGER; //on n' a pas besoin d'être hyper précis je pense
variable sum_f: INTEGER;
variable test: BOOLEAN;
variable alpha: BOOLEAN;

BEGIN

	variance_sq=sq_mean*area-mean*mean; 
    	variance=sqrt(variance_sq);
    
    	sum_f = P1*R1+P2*R2+P3*R3+P4*R4;
 
      	float t = mult_fixe( mult_fixe(seuil*seuil)*variance_sq);
      	//   Test le feature
      	test = (sum_f*sum_f) >= t;
      	if (sum_f>= 0 ) then
        {
          	if (th>=0) then
            		alpha= test ? 1 : 0;
          	else
            		alpha=1;
		end if;
        }
      	else
        {
          	if (th>0) then
            		alpha= 0;
         	else
            		alpha= (!test) ? 1 : 0;
		end if;
        }
	end if;
	if(alpha=FALSE) then 
		RETURN prev_f+v0;
	else 
		RETURN prev_f+v1;
	end if;

END eval_Feature;

    

