-------------------------------------------------------------------------------
-- system_top.vhd
-------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

library UNISIM;
use UNISIM.VCOMPONENTS.ALL;

library work;
use work.packageVGA.all;

entity system_top is
  Port ( processing_system7_0_MIO : inout std_logic_vector(53 downto 0);
		processing_system7_0_PS_SRSTB : in std_logic;
		processing_system7_0_PS_CLK : in std_logic;
		processing_system7_0_PS_PORB : in std_logic;
		processing_system7_0_DDR_Clk : inout std_logic;
		processing_system7_0_DDR_Clk_n : inout std_logic;
		processing_system7_0_DDR_CKE : inout std_logic;
		processing_system7_0_DDR_CS_n : inout std_logic;
		processing_system7_0_DDR_RAS_n : inout std_logic;
		processing_system7_0_DDR_CAS_n : inout std_logic;
		processing_system7_0_DDR_WEB : out std_logic;
		processing_system7_0_DDR_BankAddr : inout std_logic_vector(2 downto 0);
		processing_system7_0_DDR_Addr : inout std_logic_vector(14 downto 0);
		processing_system7_0_DDR_ODT : inout std_logic;
		processing_system7_0_DDR_DRSTB : inout std_logic;
		processing_system7_0_DDR_DQ : inout std_logic_vector(31 downto 0);
		processing_system7_0_DDR_DM : inout std_logic_vector(3 downto 0);
		processing_system7_0_DDR_DQS : inout std_logic_vector(3 downto 0);
		processing_system7_0_DDR_DQS_n : inout std_logic_vector(3 downto 0);
		processing_system7_0_DDR_VRN : inout std_logic;
		processing_system7_0_DDR_VRP : inout std_logic;
		processing_system7_0_I2C0_SDA : inout std_logic;
		processing_system7_0_I2C0_SCL : inout std_logic;
		led_io : inout std_logic_vector(3 downto 0);
		push_io : in std_logic_vector(3 downto 0);
		switch_io : in std_logic_vector(3 downto 0);
		clk : in std_logic;
		RED : out std_logic_vector(4 downto 0);
  		GREEN : out std_logic_vector(5 downto 0);
  		BLUE : out std_logic_vector(4 downto 0);
		VGA_VS : out std_logic;
		VGA_HS : out std_logic;
		CAMERA_DATA : in std_logic_vector(7 downto 0);
    	--CAMERA_PWREN : out std_logic;
		--CAMERA_RST : out std_logic;
		--CAMERA_SCL : inout std_logic;
		--CAMERA_SDA : inout std_logic;		
		CAMERA_XCLK : out std_logic;
		CAMERA_PCLK : in std_logic;
		CAMERA_HS : in std_logic;
		CAMERA_VS : in std_logic
  );
end system_top;

architecture STRUCTURE of system_top is

component system is
	 Port ( processing_system7_0_MIO : inout std_logic_vector(53 downto 0);
			 processing_system7_0_PS_SRSTB : in std_logic;
			 processing_system7_0_PS_CLK : in std_logic;
			 processing_system7_0_PS_PORB : in std_logic;
			 processing_system7_0_DDR_Clk : inout std_logic;
			 processing_system7_0_DDR_Clk_n : inout std_logic;
			 processing_system7_0_DDR_CKE : inout std_logic;
			 processing_system7_0_DDR_CS_n : inout std_logic;
			 processing_system7_0_DDR_RAS_n : inout std_logic;
			 processing_system7_0_DDR_CAS_n : inout std_logic;
			 processing_system7_0_DDR_WEB : out std_logic;
			 processing_system7_0_DDR_BankAddr : inout std_logic_vector(2 downto 0);
			 processing_system7_0_DDR_Addr : inout std_logic_vector(14 downto 0);
			 processing_system7_0_DDR_ODT : inout std_logic;
			 processing_system7_0_DDR_DRSTB : inout std_logic;
			 processing_system7_0_DDR_DQ : inout std_logic_vector(31 downto 0);
			 processing_system7_0_DDR_DM : inout std_logic_vector(3 downto 0);
			 processing_system7_0_DDR_DQS : inout std_logic_vector(3 downto 0);
			 processing_system7_0_DDR_DQS_n : inout std_logic_vector(3 downto 0);
			 processing_system7_0_DDR_VRN : inout std_logic;
			 processing_system7_0_DDR_VRP : inout std_logic;
			 processing_system7_0_I2C0_SDA : inout std_logic;
			 processing_system7_0_I2C0_SCL : inout std_logic);
end component system;

 attribute BOX_TYPE : STRING;
 attribute BOX_TYPE of system : component is "user_black_box";
 
component clk_pll
	 Port ( CLK_IN1 : in STD_LOGIC;
			CLK_OUT1 : out STD_LOGIC;
			CLK_OUT2 : out STD_LOGIC;
			RESET : in STD_LOGIC;
			LOCKED : out STD_LOGIC);
end component clk_pll;

--component Camera_Data_Simu
--    Port ( pclk : in STD_LOGIC;
--			  href : out STD_LOGIC;
--         vs : out STD_LOGIC;
--         data_out : out STD_LOGIC_VECTOR (7 downto 0));
--end component Camera_Data_Simu;

--component VGA_generator
--    Port ( clk : in STD_LOGIC;
--    		btn3 : in STD_LOGIC;								
--			Hsync : out STD_LOGIC;
--			Vsync : out STD_LOGIC;
--			addr : out STD_LOGIC_VECTOR (16 downto 0);
--			coord : out coordonnee;
--			activeArea : out boolean;
--			reset : out STD_LOGIC);
--end component VGA_generator;

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
end component Frame_grabber;

component VGA_out 
    Port ( CLK : in  STD_LOGIC;
           Din : in  unsigned (7 downto 0);
           HSync : out  STD_LOGIC;
           VSync : out  STD_LOGIC;
           R : out  unsigned (4 downto 0);
           G : out  unsigned (5 downto 0);
           B : out  unsigned (4 downto 0);
           Offset : out  unsigned (15 downto 0));
end component VGA_out;

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
			  send_img : in  boolean);
end Component Image_integrale;

--component Camera_Capture
--    Port ( pclk : in STD_LOGIC;
--    	   reset : in STD_LOGIC;
--         href : in STD_LOGIC;
--			vs_cam : in STD_LOGIC;
--			data_in : in STD_LOGIC_VECTOR (7 downto 0);
--			addr : out STD_LOGIC_VECTOR (16 downto 0);
--			data_out : out STD_LOGIC_VECTOR (15 downto 0);
--			coord : out coordonnee;
--			we : out STD_LOGIC_VECTOR(0 DOWNTO 0));
--end component Camera_Capture;

component mem_ram
	 Port ( clka : in STD_LOGIC;
			wea : in STD_LOGIC_VECTOR(0 DOWNTO 0);
    		addra : in STD_LOGIC_VECTOR(16 DOWNTO 0);
    		dina : in STD_LOGIC_VECTOR(15 DOWNTO 0);
    		clkb : in STD_LOGIC;
   		addrb : in STD_LOGIC_VECTOR(16 DOWNTO 0);
   		doutb : out STD_LOGIC_VECTOR(15 DOWNTO 0));
end component mem_ram;
--
--component multiplexer_RGB is
--    Port ( clk : in STD_LOGIC;
--    		sw0 : in STD_LOGIC;	
--			btn0 : in STD_LOGIC;					
--			btn1 : in STD_LOGIC;
--			btn2 : in STD_LOGIC;
--			coord : in coordonnee;
--			data  : in STD_LOGIC_VECTOR (15 downto 0);
--			activeArea : in boolean;
--			Hsync : in STD_LOGIC;
--			Vsync : in STD_LOGIC;
--			VGA_hs : out STD_LOGIC;
--			VGA_vs : out STD_LOGIC;
--			VGA_r : out STD_LOGIC_VECTOR (4 downto 0);
--			VGA_g : out STD_LOGIC_VECTOR (5 downto 0);
--			VGA_b : out STD_LOGIC_VECTOR (4 downto 0));
--end component multiplexer_RGB;

signal clk_VGA, pclk_cam : STD_LOGIC; 
signal we : STD_LOGIC_VECTOR(0 DOWNTO 0);
signal address_cam, address_VGA : STD_LOGIC_VECTOR (16 downto 0);
signal data_cam, data_VGA : STD_LOGIC_VECTOR (15 downto 0);
signal coord_VGA, coord_cam : coordonnee;
signal img_active : boolean;
signal hs, vs : STD_LOGIC; 
signal rst_VGA : STD_LOGIC;

--signaux pour les cast
signal address_vga_unsigned : unsigned(15 downto 0);
signal address_cam_unsigned : unsigned(15 downto 0);
signal red_unsigned : unsigned (4 downto 0);
signal green_unsigned : unsigned (5 downto 0);
signal blue_unsigned : unsigned (4 downto 0); 
signal data_vga_unsigned : unsigned (7 downto 0);
signal camera_data_unsigned : unsigned (7 downto 0);
signal data_cam_unsigned : unsigned (7 downto 0);
signal we_stdlogic : std_logic;

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
				SIGNAL send_img :  boolean;
				SIGNAL Image_int_ready : std_logic;
				
				signal image_ready : std_logic;
				signal sig_true : std_logic := '1';
--signal CAMERA_DATA : STD_LOGIC_VECTOR (7 downto 0);
--signal CAMERA_HS, CAMERA_VS : STD_LOGIC;

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
				
				SIGNAL face_detected :  boolean;
				SIGNAL visage : Visage;
				
				SIGNAL data_i : unsigned (31 downto 0);
			   SIGNAL data_i_2 : unsigned (31 downto 0);
			   SIGNAL data_o : unsigned (31 downto 0);
			   SIGNAL data_o_2 : unsigned (31 downto 0);

begin

sig_true <= '1';
address_vga <= std_logic_vector("0" & address_vga_unsigned);
red <= std_logic_vector(red_unsigned);
green <= std_logic_vector(green_unsigned);
blue <= std_logic_vector(blue_unsigned);
data_vga_unsigned <= unsigned(data_vga(7 downto 0));
camera_data_unsigned <= unsigned(camera_data);
address_cam <= std_logic_vector("0" & address_cam_unsigned);
data_cam <= "00000000" & std_logic_vector(data_cam_unsigned);
we <= (0 => we_stdlogic);


system_i: system
	 Port map ( processing_system7_0_MIO => processing_system7_0_MIO,
			 processing_system7_0_PS_SRSTB => processing_system7_0_PS_SRSTB,
			 processing_system7_0_PS_CLK => processing_system7_0_PS_CLK,
			 processing_system7_0_PS_PORB => processing_system7_0_PS_PORB,
			 processing_system7_0_DDR_Clk => processing_system7_0_DDR_Clk,
			 processing_system7_0_DDR_Clk_n => processing_system7_0_DDR_Clk_n,
			 processing_system7_0_DDR_CKE => processing_system7_0_DDR_CKE,
			 processing_system7_0_DDR_CS_n => processing_system7_0_DDR_CS_n,
			 processing_system7_0_DDR_RAS_n => processing_system7_0_DDR_RAS_n,
			 processing_system7_0_DDR_CAS_n => processing_system7_0_DDR_CAS_n,
			 processing_system7_0_DDR_WEB => processing_system7_0_DDR_WEB,
			 processing_system7_0_DDR_BankAddr => processing_system7_0_DDR_BankAddr,
			 processing_system7_0_DDR_Addr => processing_system7_0_DDR_Addr,
			 processing_system7_0_DDR_ODT => processing_system7_0_DDR_ODT,
			 processing_system7_0_DDR_DRSTB => processing_system7_0_DDR_DRSTB,
			 processing_system7_0_DDR_DQ => processing_system7_0_DDR_DQ,
			 processing_system7_0_DDR_DM => processing_system7_0_DDR_DM,
			 processing_system7_0_DDR_DQS => processing_system7_0_DDR_DQS,
			 processing_system7_0_DDR_DQS_n => processing_system7_0_DDR_DQS_n,
			 processing_system7_0_DDR_VRN => processing_system7_0_DDR_VRN,
			 processing_system7_0_DDR_VRP => processing_system7_0_DDR_VRP,
			 processing_system7_0_I2C0_SDA => processing_system7_0_I2C0_SDA,
			 processing_system7_0_I2C0_SCL => processing_system7_0_I2C0_SCL
			 );

pll: clk_pll
	 Port map ( CLK_IN1 => clk,	 -- 125 MHz
			CLK_OUT1 => clk_VGA,		 -- 24 MHz
			CLK_OUT2 => CAMERA_XCLK, -- 24 MHz
			RESET => push_io(3),
			LOCKED => led_io(0)
			);

led_io(1) <= '0';
led_io(2) <= '0';
led_io(3) <= '1';
		
--cam_clk_buf : IBUFG
--	Port map
--   (O => pclk_cam,
--    I => CAMERA_PCLK);
    
--cam_simu: Camera_Data_Simu
--    Port map ( pclk => pclk_cam,
--			    href => CAMERA_HS,
--           vs => CAMERA_VS,
--           data_out => CAMERA_DATA
--			    );

--vga: VGA_generator
--    Port map ( clk => clk_VGA,
--    		  btn3 => push_io(3),
--           Hsync => hs,
--           Vsync => vs,
--			  addr => address_VGA,
--			  coord => coord_VGA,
--			  activeArea => img_active,
--			  reset => rst_VGA
--			  );
--
--capture: Camera_Capture
--    Port map ( pclk => CAMERA_PCLK,
--    		  reset => rst_VGA,
--           href => CAMERA_HS,
--           vs_cam => CAMERA_VS,
--           data_in => CAMERA_DATA,
--           addr => address_cam,
--           data_out => data_cam,
--           coord => coord_cam,
--           we => we
--			  );


vga: VGA_out
    Port map ( clk => clk_VGA,    	
           Hsync => VGA_HS,
           Vsync => VGA_VS,
			  offset => address_VGA_unsigned,
			  r => RED_unsigned,
			  g => GREEN_unsigned,
			  b => BLUE_unsigned,
			  Din => Data_VGA_unsigned
			  );

capture: Frame_grabber
    Port map ( clk => CAMERA_PCLK,
    		  reset => rst_VGA,
           href => CAMERA_HS,
           vsync => CAMERA_VS,
           din => CAMERA_DATA_unsigned,
			  det_end => sig_true,
           offset => address_cam_unsigned,
           dout => data_cam_unsigned,
           image_ready => image_ready,
           we => we_stdlogic
			  );

			  
ram: mem_ram
	 Port map ( clka => CAMERA_PCLK,
			  wea => we,
    		  addra => address_cam,
    		  dina => data_cam,
    		  clkb => clk_VGA,
   		  addrb => address_VGA,
   		  doutb => data_VGA
   		  );
   		  
--mux: multiplexer_RGB
--    Port map ( clk => clk_VGA,
--    		  sw0 => switch_io(0),
--    		  btn0 => push_io(0),
--			  btn1 => push_io(1),	
--			  btn2 => push_io(2),
--			  coord => coord_VGA,
--			  data => data_VGA,
--			  activeArea => img_active,
--			  Hsync => hs,
--			  Vsync => vs,
--			  VGA_hs => VGA_HS,
--			  VGA_vs => VGA_VS,
--			  VGA_r => RED,
--			  VGA_g => GREEN,
--			  VGA_b => BLUE
--			  );
			  
image_int: Image_integrale PORT MAP(
			  CLK => CLK,
           RST => rst_VGA,
			  send_img => send_img,
			  Image_int_ready => Image_int_ready,
			  Din_img => Din_img,
			  Din_i => data_i,
			  Din_ic => data_i_2,
			  Dout_i => data_o,
			  Dout_ic => data_o_2,
			  Offset_lect_img => address_cam_unsigned, 
			  Offset_ecr_int => Offset_ecr_int,
			  Offset_lect_int => Offset_lect_int,
			  we_i => we_i,
			  we_ic => we_ic,
			  Det_end => send_img);		


detection: fsm_detection 
	PORT MAP (
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
			visage => visage); 
		 			  

end architecture STRUCTURE;

