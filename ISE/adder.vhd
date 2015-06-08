library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity adder is
    Port ( In_A : in  signed (15 downto 0);
           In_B : in  signed (15 downto 0);
           In_param : in  STD_LOGIC_VECTOR (15 downto 0);
           out_AB : out  signed (15 downto 0);
           Out_param : out  STD_LOGIC_VECTOR (8 downto 0));
end adder;

architecture adder_arch of adder is

begin

process(In_A, In_B, In_param)
variable ae : unsigned (3 downto 0);
variable av : unsigned (3 downto 0);
variable be : unsigned (3 downto 0);
variable bv : unsigned (3 downto 0);
variable re : unsigned (4 downto 0);
variable rv : unsigned (3 downto 0);
variable a : integer;
variable b : integer;

begin
	ae:=unsigned(in_param(15 downto 12));
	av:=unsigned(in_param(11 downto 8));
	be:=unsigned(in_param(7 downto 4));
	bv:=unsigned(in_param(3 downto 0));
	a:= to_integer(in_A(to_integer(ae+av) downto 0));
	b:= to_integer (in_B(to_integer(be+bv) downto 0));
if ae > be then
	re:= '0' & ae;
else
	re:='0' & be;
end if;

if av > bv then
	rv :=av;
	b:=b*(2**to_integer(av-bv));
else
	rv:=bv;
	a:=a*(2**to_integer(av-bv));
end if;

re:=re+1;
out_param<= std_logic_vector(re) & std_logic_vector(rv);
out_ab<=to_signed((a+b),16);

end process;



end adder_arch;

