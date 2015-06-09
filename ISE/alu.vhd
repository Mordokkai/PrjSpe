library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

package alu is

	type FixedPoint is 
	record
		val: integer;
		e:  integer;
		v:  integer;
	end record;
	
	function "+" ( in_A : in FixedPoint ; in_B : in FixedPoint) return FixedPoint;
	function "*" (in_A : in FixedPoint ; in_B : in FixedPoint) return FixedPoint;
	function ">=" (in_A : in FixedPoint ; in_B : in FixedPoint) return boolean;
	function ">" (in_A : in FixedPoint ; in_B : in FixedPoint) return boolean;
	function minE (in_A : in integer) return integer;

end alu;

package body alu is

	function "+" (in_A : in FixedPoint ; in_B : in FixedPoint) return FixedPoint is
		variable ae : integer;
		variable av : integer;
		variable be : integer;
		variable bv : integer;
		variable re : integer;
		variable rv : integer;
		variable a : integer;
		variable b : integer;
		variable result : FixedPoint;
		begin
			ae:=In_A.e;
			av:=In_A.v;
			be:=In_B.e;
			bv:=In_B.v;
			a:= to_integer(to_signed (in_A.val, ae+av+1));
			b:= to_integer(to_signed (in_B.val, be+bv+1));
		if ae > be then
			re:=  ae;
		else
			re:= be;
		end if;

		if av > bv then
			rv :=av;
			b:=b*(2**(av-bv));
		else
			rv:=bv;
			a:=a*(2**(bv-av));
		end if;

		re:=re+1;
		result.e:=re;
		result.v:=rv;
		result.val:=(a+b);
		return result;
end function;
	
	
	function "*" (in_A : in FixedPoint ; in_B : in FixedPoint) return FixedPoint is

		variable ae : integer;
		variable av : integer;
		variable be : integer;
		variable bv : integer;
		variable re : integer;
		variable rv : integer;
		variable a : integer;
		variable b : integer;
		variable result : FixedPoint;
		begin
			ae:=In_A.e;
			av:=In_A.v;
			be:=In_B.e;
			bv:=In_B.v;
			a:= to_integer(to_signed (in_A.val, ae+av+1));
			b:= to_integer(to_signed (in_B.val, be+bv+1));
			
			rv:= ( av)+( bv);
			re:= ( ae)+ (be);
			
		result.e:=re;
		result.v:=rv;
		result.val:=a*b;
		return result;
		end function;
			
function ">=" (in_A : in FixedPoint ; in_B : in FixedPoint) return boolean	is
		variable ae : integer;
		variable av : integer;
		variable be : integer;
		variable bv : integer;
		variable re : integer;
		variable rv : integer;
		variable a : integer;
		variable b : integer;
		variable result : FixedPoint;
	begin
	

			ae:=In_A.e;
			av:=In_A.v;
			be:=In_B.e;
			bv:=In_B.v;
			a:= to_integer(to_signed (in_A.val, ae+av+1));
			b:= to_integer(to_signed (in_B.val, be+bv+1));
	if(av>bv) then 
		b:=b*(2**((av-bv)));
	else
		a:=a*(2**((bv-av)));
	end if;
	return a>=b;
	
end function;

function ">" (in_A : in FixedPoint ; in_B : in FixedPoint) return boolean	is
		variable ae : integer;
		variable av : integer;
		variable be : integer;
		variable bv : integer;
		variable re : integer;
		variable rv : integer;
		variable a : integer;
		variable b : integer;
		variable result : FixedPoint;
	begin
	

			ae:=In_A.e;
			av:=In_A.v;
			be:=In_B.e;
			bv:=In_B.v;
			a:= to_integer(to_signed (in_A.val, ae+av+1));
			b:= to_integer(to_signed (in_B.val, be+bv+1));
	if(av>bv) then 
		b:=b*(2**((av-bv)));
	else
		a:=a*(2**((bv-av)));
	end if;
	return a>b;
	
end function;

	
function minE (in_A : in integer) return integer is
	variable i: integer :=1;
	variable a :integer :=in_A;
begin
if (in_A <0) then
	a:=-in_A;
end if; 
	while (a>0) loop
		i:=i+1;
		a:=a/2;
	end loop;
return i;
end function;
 
end package body alu;
