library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.numeric_std.all;

package FACE_DETECTION_PCK is

constant IMG_WIDTH : integer := 128;
constant IMG_HEIGHT: integer :=64;

type STAGE_NF is array (0 to 37 ) of integer;
type FEATURE_NR  is array (0 to 2**12-1) of integer;

constant SNF : STAGE_NF := (others => 0); -- TODO:
constant FNR : FEATURE_NR := (others => 0); --TODO;

--constant SE : integer :=
--constant SV : integer :=
--constant FE : integer :=
--constant FV : integer :=
--constant GTE: integer :=
--constant GTV: integer :=
--constant LSE: integer :=
--constant LSV: integer :=
type Mean is array (0 to 3) of integer;
type Var is array (0 to 3) of integer;
type R is array (0 to 3) of integer;

type Rectangle is
record 
	x	: integer;
	y	: integer;
	w	: integer;
	h	: integer;
	weight : integer;
end record;

type Rectangles is array (0 to 2) of Rectangle;
type R_tab is array (0 to 2) of R;


type Feature is 
record
	--rects 		: Rectangles;
	threshold	: integer;
	nr				: integer; -- number of rectangles per feature
	greater		: integer;
	lower 		: integer; 
	ad_rectangle : integer;
end record;

--type Features is array (0 to 37) of Feature; --useless

--type Stage is
--record
	--feats			: Features;
	--threshold	: integer;
	--nf				: integer; --number of features per stage
--end record; 

type Stage is
record
	threshold : integer;
	ad_feature: integer;
	nf : integer;
end record;

type Detector is
record
	x	: integer;
	y 	: integer;
end record;

function StageEval (signal d: in Detector; signal stageAdress : in unsigned (5 downto 0)) return integer;  
function FeatureEval(signal r: in R; signal rect: in Rectangle) return integer;
function test_Feature( signal meanP : in Mean; signal varP : in Var; calcul : integer; signal f_q : in Feature) return boolean;

-- procedure <procedure_name> (<type_declaration> <constant_name>	: in <type_declaration>);
--

end FACE_DETECTION_PCK;

package body FACE_DETECTION_PCK is

function StageEval (signal d: in Detector; signal stageAdress : in unsigned (5 downto 0)) return integer is
begin
	--todo
	return 0;
end;

function FeatureEval(signal r_tab : in R_tab; signal rect : in Rectangle) return integer is
variable cont1 : integer;
variable cont2 : integer;
variable cont3 : integer;
variable sum: integer;

begin
	cont1 := r_tab(0)(3)+r_tab(0)(1)-r_tab(0)(2)-r_tab(0)(3);
	cont2 := r_tab(1)(3)+r_tab(1)(1)-r_tab(1)(2)-r_tab(1)(3);
	cont3 := r_tab(2)(3)+r_tab(2)(1)-r_tab(2)(2)-r_tab(2)(3);
	
	sum := cont1*rect(0).weight + cont2*rect(1).weight + cont3*rect(2).weight;
	
	return sum;
end;


function test_Feature( signal meanP : in Mean; signal varP : in Var; calcul : integer; signal f_q : in Feature) return boolean is
variable mean : integer;
variable sq_mean : integer;
variable var_sq : integer;
variable seuil : integer;
begin
mean := meanP(4)+meanP(1)-meanP(2)-meanP(3);
sq_mean := varP(4)+varP(1)-varP(2)-varP(3);
var_sq := sq_mean*24*24-mean*mean;

seuil:= f_q.threshold;
if(sumf_q*sumf_q>=seuil*seuil*var_sq) then
	return true;
else
	return false;
end if;
end;

---- Procedure Example
--  procedure <procedure_name>  (<type_declaration> <constant_name>  : in <type_declaration>) is
--    
--  begin
--    
--  end <procedure_name>;
 
end FACE_DETECTION_PCK;
