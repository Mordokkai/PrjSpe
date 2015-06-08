----------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity mult is
    Port ( In_A : in  signed (15 downto 0);
           In_B : in  signed (15 downto 0);
           In_param : in  STD_LOGIC_VECTOR (15 downto 0);
           out_ab : out  signed (31 downto 0);
           out_param : out  STD_LOGIC_VECTOR (9 downto 0));
end mult;

architecture mult_arch of mult is

begin

process(In_A, In_B, In_param)
variable ae : unsigned (3 downto 0);
variable av : unsigned (3 downto 0);
variable be : unsigned (3 downto 0);
variable bv : unsigned (3 downto 0);
variable re : unsigned (4 downto 0);
variable rv : unsigned (4 downto 0);
variable a : integer;
variable b : integer;

begin
	ae:=unsigned(in_param(15 downto 12));
	av:=unsigned(in_param(11 downto 8));
	be:=unsigned(in_param(7 downto 4));
	bv:=unsigned(in_param(3 downto 0));
	a:= to_integer(in_A(to_integer(ae+av) downto 0));
	b:= to_integer (in_B(to_integer(be+bv) downto 0));
	
	rv:= ('0'& av)+('0'& bv);
	re:= ('0'& ae)+ ('0'& be);
	
out_param<= std_logic_vector(re) & std_logic_vector(rv);
out_ab<=to_signed((a*b),32);

end process;


end mult_arch;

