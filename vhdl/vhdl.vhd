//D�claration RAM_image

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



//D�claration RAM_II

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


//D�claration RAM_II�

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


//D�claration RAM_image_ping

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


//D�claration RAM_II_ping

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



//D�claration RAM_II

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












   
//Machine � �tat




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
    	signal i_f, i_f_next : std_logic_vector(11 downto 0);
    	signal i_s, i_s_next : std_logic_vector(5 downto 0);
			signal i_r, i_r_next : std_logic_vector(2 downto 0);
			signal i_k, i_k_next : std_logic_vector(2 downto 0);
			signal l, l_next : std_logic_vector(2 downto 0);
			signal m, m_next : std_logic_vector(2 downto 0);
			signal mean: ??????????????????????;
			signal var: ???????????????????????;
			signal r: ?????????????????????????;
			signal rect: ??????????????????????;
			signal sum_s: integer;
			signal sum_f: integer;
			
			
begin

    P_STATE : process(clk)
    begin
     if rising_edge(clk) then
      if (RESET = '1') then
      current_state <= Wait0;
       
      else
                access_count <= access_count_next;
								i_f <= i_f_next;
								i_s <= i_s_next;
      		Current_State <= Next_State;
     end if;
    end if;
   end process P_STATE;

   



        P_FSM : process(current_state,access_count,if,is,img_RDY)
    	begin
        variable Ns: INTEGER;
	variable Nf: INTEGER;
	variable stage_OK : boolean;
	variable img_Termine : boolean;
     	case current_state is
       		when WAIT_IMG0 => 
			if(img_RDY='1') then
				next_state <= REQ_S1;
			else
				next_state <= WAIT0;
			end if;
			is <= '0';
              		if <= '0';
			access_count <= '0';
       		






		when REQ_S1 =>
                	if(is<Ns) then
				next_state <= ACK_S2;
				is <= is+1;
			
        	when ACK_S2 =>
                	next_sate <= REQ_F3;
        	when REQ_F3 =>
                	if(if < Nf) then
				if <= if+1;
				ir <= 0;
			end if;
        	when REQ_F4 =>
			if(ir=Nr) then
				next_state <= EVAL_F6;
			else
                		next_state <= REQ_PTS5;
				access_count <=0;
			end if;
        	when REQ_PTS5 =>
			if(access_count < 4) then
				next_state <= REQ_PTS5;
				access_count <= access_count +1;
			else
				if(ir < Nr) then
					ir <= ir+1;
					next_state <= REQ_F4;
		when EVAL_F6 =>
			if(if <Nf) then
				next_state <= REQ_F3;
			else 
				next_state <= EVAL_S7;
			end if;
		
		when EVAL_S7 =>
               		if (is < Ns and Stage_OK) then
				next_state <= REQ_S1;
			else if (not Stage_OK) then
				face_detected <= false;
				next_state <= ???????
			else if (is=Ns and Stage_OK) then
				face_detected <= true;
				next_state <= ???????????
		
		when SEND_DATA =>
			if(img_Termine) then
				next_state <= WAIT_IMG0;
			
			else
				next_state <= REQ_S1;
        	when others => next_state <= WAIT0;
        
	end case;
end process P_FSM;



//Trdauction du c vers vhdl
/* calcul l'int�grale sur un carre de coin x, y et de largeur (tx,ty) */
4 signaux de valeurs r�cup�rer depuis ram_img
    FUNCTION img_rect(L1 : IN std_logic_vector(7 downto 0); 
        L2 : IN std_logic_vector(7 downto 0);
	L3 : IN std_logic_vector(7 downto 0);
	L4 : IN std_logic_vector(7 downto 0)
    ) RETURN integer;

BEGIN
	RETURN L4-L3-L2+L1;
END img_rect;




//Process d'�valuation du stage
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
il faut la valeur totale de l'image int�grale carr�e sur le pixel  =sq_mean
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
variable variance: INTEGER; //on n' a pas besoin d'�tre hyper pr�cis je pense
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

    
