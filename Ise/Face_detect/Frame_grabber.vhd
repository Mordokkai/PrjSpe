----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    15:59:47 06/02/2015 
-- Design Name: 
-- Module Name:    Frame_grabber - Behavioral 
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

entity Frame_grabber is
    Port ( Din : in  STD_LOGIC;
           Vsync : in  STD_LOGIC;
           Href : in  STD_LOGIC;
           CLK : in  STD_LOGIC;
           Det_end : in  STD_LOGIC;
           Dout : out  STD_LOGIC;
           Offset : out  STD_LOGIC;
           We : out  STD_LOGIC;
           Image_ready : out  STD_LOGIC);
end Frame_grabber;

architecture Behavioral of Frame_grabber is

begin


end Behavioral;

