library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

package alu is

	type FixedPoint is 
	record
		val: signed (31 downto 0);
		e: unsigned (4 downto 0);
		v: unsigned (4 downto 0);
	end record;
	
	function  adder ( in_A : in FixedPoint ; in_B : in FixedPoint) return FixedPoint;
	function mult (in_A : in FixedPoint ; in_B : in FixedPoint) return FixedPoint;
	function greater (in_A : in FixedPoint ; in_B : in FixedPoint) return boolean;

end alu;

package body alu is

	function adder (in_A : in FixedPoint ; in_B : in FixedPoint) return FixedPoint is
		variable ae : unsigned (4 downto 0);
		variable av : unsigned (4 downto 0);
		variable be : unsigned (4 downto 0);
		variable bv : unsigned (4 downto 0);
		variable re : unsigned (4 downto 0);
		variable rv : unsigned (4 downto 0);
		variable a : integer;
		variable b : integer;
		variable result : FixedPoint;

		begin
			ae:=In_A.e;
			av:=In_A.v;
			be:=In_B.e;
			bv:=In_B.v;
			a:= to_integer(in_A.val(to_integer(ae+av) downto 0));
			b:= to_integer (in_B.val(to_integer(be+bv) downto 0));
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
		result.e:=re;
		result.v:=rv;
		result.val:=to_signed((a+b),32);
		return result;
end function;
	
	
	function mult (in_A : in FixedPoint ; in_B : in FixedPoint) return FixedPoint is

		variable ae : unsigned (4 downto 0);
		variable av : unsigned (4 downto 0);
		variable be : unsigned (4 downto 0);
		variable bv : unsigned (4 downto 0);
		variable re : unsigned (4 downto 0);
		variable rv : unsigned (4 downto 0);
		variable a : integer;
		variable b : integer;
		variable result : FixedPoint;
		begin
			ae:=In_A.e;
			av:=In_A.v;
			be:=In_B.e;
			bv:=In_B.v;
			a:= to_integer(in_A.val(to_integer(ae+av) downto 0));
			b:= to_integer (in_B.val(to_integer(be+bv) downto 0));
			
			rv:= ( av)+( bv);
			re:= ( ae)+ (be);
			
		result.e:=re;
		result.v:=rv;
		result.val:=to_signed((a*b),32);
		return result;
		end function;
			
function greater (in_A : in FixedPoint ; in_B : in FixedPoint) return boolean	is
		variable ae : unsigned (4 downto 0);
		variable av : unsigned (4 downto 0);
		variable be : unsigned (4 downto 0);
		variable bv : unsigned (4 downto 0);
		variable re : unsigned (4 downto 0);
		variable rv : unsigned (4 downto 0);
		variable a : integer;
		variable b : integer;
		variable result : FixedPoint;
	begin
			ae:=In_A.e;
			av:=In_A.v;
			be:=In_B.e;
			bv:=In_B.v;
			a:= to_integer(in_A.val(to_integer(ae+av) downto 0));
			b:= to_integer (in_B.val(to_integer(be+bv) downto 0));
	if(av>bv) then 
		b:=b*(2**(to_integer(av-bv)));
	else
		a:=a*(2**(to_integer(bv-av)));
	end if;
	return a>b;
	
end function;
 
end alu;
