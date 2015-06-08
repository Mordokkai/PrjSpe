library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

package alu is
	
	procedure adder (signal in_A : in signed (15 downto 0) ; signal in_B : in signed (15 downto 0); 
						signal in_param: in std_logic_vector(15 downto 0); signal out_AB : out signed(16 downto 0)
						; signal out_param : out std_logic_vector (8 downto 0));
	procedure mult (signal in_A : in signed (15 downto 0) ; signal in_B : in signed (15 downto 0); 
						signal in_param: in std_logic_vector(15 downto 0); signal out_AB : out signed(31 downto 0)
						; signal out_param : out std_logic_vector (9 downto 0));
	function greater (signal in_A : in signed (31 downto 0); signal In_B : in signed (31 downto 0);
					in_param : in std_logic_vector (19 downto 0)) return boolean;

end alu;

package body alu is

	procedure adder (signal in_A : in signed (15 downto 0) ; signal in_B : in signed (15 downto 0); 
						signal in_param: in std_logic_vector(15 downto 0); signal out_AB : out signed(16 downto 0)
						; signal out_param : out std_logic_vector (8 downto 0)) is
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
end procedure;
	
	
	procedure mult (signal in_A : in signed (15 downto 0) ; signal in_B : in signed (15 downto 0); 
					signal in_param: in std_logic_vector(15 downto 0); signal out_AB : out signed(31 downto 0)
					; signal out_param : out std_logic_vector (9 downto 0))is

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

		end procedure;
			
function greater (signal in_A : in signed (31 downto 0); signal In_B : in signed (31 downto 0);
				in_param : in std_logic_vector (19 downto 0)) return boolean	is
	variable ae : unsigned (3 downto 0);
	variable av : unsigned (3 downto 0);
	variable be : unsigned (3 downto 0);
	variable bv : unsigned (3 downto 0);
	variable a : integer;
	variable b : integer;
begin

	ae:=unsigned(in_param(19 downto 15));
	av:=unsigned(in_param(14 downto 10));
	be:=unsigned(in_param(9 downto 5));
	bv:=unsigned(in_param(4 downto 0));
	a:= to_integer(in_A(to_integer(ae+av) downto 0));
	b:= to_integer (in_B(to_integer(be+bv) downto 0));
	if(av>bv) then 
		b:=b*(2**(to_integer(av-bv)));
	else
		a:=a*(2**(to_integer(bv-av)));
	end if;
	return a>b;
	
end function;
 
end alu;
