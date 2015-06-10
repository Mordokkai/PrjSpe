----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    10:21:57 06/10/2015 
-- Design Name: 
-- Module Name:    VGA_out - Behavioral 
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

entity VGA_out is
    Port ( CLK : in  STD_LOGIC;
           Din : in  unsigned (7 downto 0);
           HSync : out  STD_LOGIC;
           VSync : out  STD_LOGIC;
           R : out  unsigned (4 downto 0);
           G : out  unsigned (5 downto 0);
           B : out  unsigned (4 downto 0));
end VGA_out;

architecture Behavioral of VGA_out is

begin


end Behavioral;

