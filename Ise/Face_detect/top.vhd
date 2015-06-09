----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    09:17:21 06/08/2015 
-- Design Name: 
-- Module Name:    top - Behavioral 
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

entity top is
				Port(CLK : in  STD_LOGIC;
            RST : in  STD_LOGIC;
				Din : in  unsigned (7 downto 0);
				Vsync : in  STD_LOGIC;
				Href : in  STD_LOGIC;
			   Image_ready : in  STD_LOGIC;
			   Image_int_ready : out  STD_LOGIC;
				--affichage en sortie
				RED : out std_logic_vector(4 downto 0);
				GREEN : out std_logic_vector(5 downto 0);
				BLUE : out std_logic_vector(4 downto 0);
				VGA_VS : out std_logic;
				VGA_HS : out std_logic
			   
				);
			
end top;

architecture Behavioral of top is
				--signaux image inté
				SIGNAL Din_img : unsigned (7 downto 0);
			   SIGNAL Din_i : unsigned (31 downto 0);
			   SIGNAL Din_ic : unsigned (31 downto 0);
			   SIGNAL Dout_i : unsigned (31 downto 0);
			   SIGNAL Dout_ic : unsigned (31 downto 0);
			   SIGNAL Offset_lect_img : unsigned (15 downto 0);
			   SIGNAL Offset_ecr_int : unsigned (15 downto 0);
			   SIGNAL Offset_lect_int : unsigned (15 downto 0);
			   SIGNAL we_i : STD_LOGIC;
			   SIGNAL we_ic : STD_LOGIC;
			   --SIGNAL Det_end : STD_LOGIC;
				SIGNAL Image_int_ready : boolean;
				
				--signaux detection

				SIGNAL we_stage : std_logic;
				SIGNAL ad_stage : integer;
				SIGNAL datao_stage : unsigned(27 downto 0);
						
				SIGNAL we_feature  : std_logic;
				SIGNAL ad_feature  : integer;
				SIGNAL datao_feature : unsigned(60 downto 0);

				SIGNAL we_rectangle : std_logic;
				SIGNAL ad_rectangle : integer;
				SIGNAL datao_rectangle : unsigned(24 downto 0);
				
				--adresse de l'image dans la ram
				SIGNAL ad_img: integer;

				--SIGNAL we_II	: std_logic;
				SIGNAL ad_II: integer;
				SIGNAL datao_II: unsigned(31 downto 0);
				
				SIGNAL ad_II_2:  integer;
				--SIGNAL we_II_2 : std_logic;
				SIGNAL datao_II_2: unsigned(39 downto 0);

				SIGNAL face_detected :  boolean;
				SIGNAL send_img :  boolean;
				SIGNAL visage : Visage;
				
				--Rams
				SIGNAL adress : integer;
				SIGNAL we : std_logic;
				SIGNAL data_i : unsigned(31 downto 0);
				SIGNAL data_o : unsigned(31 downto 0);
				
				
				--Signal multiplex memoire image
				SIGNAL ping_pong : std_logic;

Component Frame_grabber
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
end Component Frame_grabber;

 Component Image_integrale
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
end Component Image_integrale;

Component ram_image is
	port (	clk : in std_logic;
				adress : in unsigned(31 downto 0);
				we : in std_logic;
				data_i : in unsigned(7 downto 0);
				data_o : out unsigned(7 downto 0)
			);
	end Component;
	
Component ram_image_2 is
	port (	clk : in std_logic;
				adress : in unsigned(31 downto 0);
				we : in std_logic;
				data_i : in unsigned(7 downto 0);
				data_o : out unsigned(7 downto 0)
			);
	end Component;
			  
COMPONENT RAM_II  --'test' is the name of the module needed to be tested.
    PORT(
         clk : IN  std_logic;
         adress : in  integer;
         we : IN  std_logic;
			data_i : IN  unsigned(31 downto 0);
			data_o : out  unsigned(31 downto 0)
        );
    END COMPONENT;
	 
COMPONENT RAM_II_2  --'test' is the name of the module needed to be tested.
    PORT(
         clk : IN  std_logic;
         adress : in  integer;
         we : IN  std_logic;
			data_i : IN  unsigned(39 downto 0);
			data_o : out  unsigned(39 downto 0)
        );
    END COMPONENT;
	 
	 
COMPONENT RAM_stages  --'test' is the name of the module needed to be tested.
    PORT(
         clk : IN  std_logic;
         adress : in  integer;
			data_o : out  unsigned(27 downto 0)
        );
    END COMPONENT;
	 
COMPONENT RAM_features  --'test' is the name of the module needed to be tested.
    PORT(
         clk : IN  std_logic;
         adress : in  integer;
			data_o : out  unsigned(60 downto 0)
        );
    END COMPONENT;
	 
COMPONENT RAM_rectangles  --'test' is the name of the module needed to be tested.
    PORT(
         clk : IN  std_logic;
         adress : in  integer;
			data_o : out  unsigned(24 downto 0)
        );
    END COMPONENT;
	 
	 
	 
COMPONENT FSM_DETECTION  --'test' is the name of the module needed to be tested.
    PORT(
			Image_int_ready : in  boolean;
          clk : in  STD_LOGIC;
          rst : in  STD_LOGIC;
					
			--Communications avec les RAMS
			we_stage : out std_logic;
			ad_stage : out integer;
			datao_stage : in unsigned(27 downto 0);
					
			we_feature : out std_logic;
			ad_feature : out integer;
			datao_feature : in unsigned(60 downto 0);

			we_rectangle : out std_logic;
			ad_rectangle : out integer;
			datao_rectangle : in unsigned(24 downto 0);

			we_II	: out std_logic;
			ad_II:	out integer;
			datao_II: in unsigned(31 downto 0);
			
			ad_II_2: out integer;
			we_II_2 : out std_logic;
			datao_II_2: in unsigned(39 downto 0);

         face_detected : out  boolean;
         send_img : out  boolean;
			visage : out Visage
        );
    END COMPONENT;

	 
	 begin

	 

uut : Image_integrale PORT MAP(
			  CLK => CLK,
           RST => RST,
			  Image_ready => Image_ready,
			  Image_int_ready => Image_int_ready,
			  Din_img => Din_img,
			  Din_i => data_i,
			  Din_ic => data_i_2,
			  Dout_i => data_o,
			  Dout_ic => data_o_2,
			  Offset_lect_img => ad_img, 
			  Offset_ecr_int => Offset_ecr_int,
			  Offset_lect_int => Offset_lect_int,
			  we_i => we_i,
			  we_ic => we_ic,
			  Det_end => send_img);

uut2 : Frame_grabber PORT MAP(
				Din => Din,
				Vsync => Vsync,
				Href => Href,
				CLK => CLK,
				Det_end => Det_end,
				RESET => RST,
				Dout => Dout,
				Offset => ad_img, --???
				We => we,
				Image_ready => Image_ready);
				
uut3: ram_image PORT MAP (
			adress => ad_img,
         clk => clk,
			 we => we,
			 data_i => data_i,
			 data_o=>data_o
        );				

				
uut4: ram_II PORT MAP (
			adress => ad_II,
         clk => clk,
			 we => we_i,
			 data_i => data_i,
			 data_o=>data_o
        );  

uut5: ram_II_2 PORT MAP (
			adress => ad_II_2,
         clk => clk,
			 we => we_ic,
			 data_i => data_i_2,
			 data_o=>data_o_2
       );   


uut6: fsm_detection PORT MAP (
			 Image_int_ready => Image_int_ready,
          clk => clk,
          rst => rst,
					
			--Communications avec les RAMS
			we_stage => we_stage,
			ad_stage => ad_stage,
			datao_stage => datao_stage,
					
			we_feature => we_feature,
			ad_feature => ad_feature,
			datao_feature => datao_feature,

			we_rectangle => we_rectangle,
			ad_rectangle => ad_rectangle,
			datao_rectangle => datao_rectangle,

			we_II	=> we_i,
			ad_II => ad_II,
			datao_II => data_o,
			
			ad_II_2 => ad_II_2,
			we_II_2 => we_ic,
			datao_II_2 => data_o_2,

         face_detected => face_detected,
         send_img => send_img,
			visage => visage
       ); 
		 
uut7: ram_stages PORT MAP (
			adress => ad_stage,
         clk => clk,
			 data_o=>datao_stage
       );   
		 
uut8: ram_features PORT MAP (
			adress => ad_feature,
         clk => clk,
			 data_o=>datao_feature
       );   
		 
uut9: ram_rectangles PORT MAP (
			adress => ad_rectangle,
         clk => clk,
			 data_o=>datao_rectangle
       );   
		


end Behavioral;

