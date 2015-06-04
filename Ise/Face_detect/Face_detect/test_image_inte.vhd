-- TestBench Template 

  LIBRARY ieee;
  USE ieee.std_logic_1164.ALL;
  USE ieee.numeric_std.ALL;

  ENTITY testbench IS
  END testbench;

  ARCHITECTURE behavior OF testbench IS 


          SIGNAL <signal1> :  std_logic;
          SIGNAL <signal2> :  std_logic_vector(3 downto 0);
          

  BEGIN
			  SIGNAL CLK : STD_LOGIC;
           SIGNAL RST : STD_LOGIC;
           SIGNAL Image_ready : STD_LOGIC;
           SIGNAL Image_int_ready : STD_LOGIC;
           SIGNAL Din_img : unsigned (7 downto 0);
           SIGNAL Din_i : unsigned (7 downto 0);
           SIGNAL Din_ic : unsigned (7 downto 0);
           SIGNAL Dout_i : unsigned (7 downto 0);
           SIGNAL Dout_ic : unsigned (7 downto 0);
           SIGNAL Offset_lect_img : unsigned (15 downto 0);
           SIGNAL Offset_ecr_int : unsigned (15 downto 0);
           SIGNAL Offset_lect_int : unsigned (15 downto 0);
           SIGNAL we2 : STD_LOGIC;
           SIGNAL we3 : STD_LOGIC;
           SIGNAL Det_end : STD_LOGIC;


  --  Test Bench Statements
     tb : PROCESS
     BEGIN

        wait for 100 ns; -- wait until global set/reset completes

        -- Add user defined stimulus here

        wait; -- will wait forever
     END PROCESS tb;
  --  End Test Bench 

  END;
