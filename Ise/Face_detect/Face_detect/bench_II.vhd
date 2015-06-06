-- TestBench Template 

  LIBRARY ieee;
  use IEEE.NUMERIC_STD.all;
  library std;
--use std.textio.all;
  USE ieee.std_logic_1164.ALL;
  USE ieee.numeric_std.ALL;
   USE ieee.std_logic_textio.all;
	use IEEE.STD_LOGIC_unsigned.ALL;
	use STD.textio.all;
  ENTITY testbench IS
  END testbench;

  ARCHITECTURE behavior OF testbench IS 


--Component declaration
COMPONENT ram_II  
    PORT(
        clk : in std_logic;
        address : in integer;
        we : in std_logic;
        data_i : in unsigned(31 downto 0);
        data_o : out unsigned(31 downto 0)
        ); END COMPONENT;
   --declare inputs and initialize them
   signal clk : std_logic := '0';
   -- Clock period definitions
   constant clk_period : time := 1 ns;

	signal adress: integer;
	signal we: std_logic;
	signal data_i : unsigned(31 downto 0);
	signal data_o : unsigned(31 downto 0);
 
          

  BEGIN
  
		-- Instantiate the Unit Under Test UUT

		uut: ram_II PORT MAP (
				clk => clk,
				we => we,
				address => adress,
				data_i => data_i,
				data_o=>data_o
        );   


  --  Test Bench Statements
--     tb : PROCESS
--     BEGIN
--
--        wait for 100 ns; -- wait until global set/reset completes
--
--        -- Add user defined stimulus here
--
--
--        wait; -- will wait forever
--     END PROCESS tb;
--  --  End Test Bench 
--

--  process
--      file file_pointer : text;
--        variable line_content : unsigned(7 downto 0);
--      variable line_num : line;
--        variable j : integer := 0;
--        variable char : character:='0';
--   begin
--        --Open the file read.txt from the specified location for reading(READ_MODE).
--      file_open(file_pointer,"/user/6/guys/Bureau/PrjSpeFinal/PrjSpe/c/Detection/detection/img_II.txt",READ_MODE);   
--      while not endfile(file_pointer) loop --till the end of file is reached continue.
--      
--		adress <= j;
--		readline (file_pointer,line_num);  --Read the whole line from the file
--		
--        --Read the contents of the line from  the file into a variable.
--      read (line_num,line_content);
--		data_i <= line_content;
--        
--        wait for 10 ns; --after reading each line wait for 10ns.
--			j:=j+1;
--      end loop;
--      file_close(file_pointer);  --after reading all the lines close the file. 
--        wait;
--    end process;
	 clk_process: process
	 begin
	 clk <= '0';
    wait for clk_period/2;  --for 0.5 ns signal is '0'.
    clk <= '1';
    wait for clk_period/2;  --for next 0.5 ns signal is '1'.
	 end process;
	 
	 
	 read_input_file:process
			variable inline:line;
			variable character_variable:integer;
			variable end_of_line:boolean;
			file myfile:text is "/user/6/guys/Bureau/PrjSpeFinal/PrjSpe/c/Detection/detection/img_II.txt";
	begin
		while not endfile(myfile) loop
			readline(myfile,inline);
			read(inline,character_variable,end_of_line);
			--end_of_line is EOLN boolean flag
			while end_of_line loop
				read(inline,character_variable,end_of_line);
				data_o <= to_unsigned(character_variable,32);
			end loop;
	end loop;
	wait;	--Do nothing when finished
	end process read_input_file;
  END;
