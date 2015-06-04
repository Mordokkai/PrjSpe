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

type Feature is 
record
	--rects 		: Rectangles;
	threshold	: integer;
	nr				: integer; -- number of rectangles per feature
	greater		: integer;
	lesser 		: integer; 
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
function FeatureEval(signal d: in Detector; signal FeatureAdress : in unsigned (11 downto 0)) return integer;
function RectangleEval(signal d: in Detector; signal RectangleAdress : in unsigned (12 downto 0)) return integer;

-- procedure <procedure_name> (<type_declaration> <constant_name>	: in <type_declaration>);
--

end FACE_DETECTION_PCK;

package body FACE_DETECTION_PCK is

function StageEval (signal d: in Detector; signal stageAdress : in unsigned (5 downto 0)) return integer is
begin
	--todo
	return 0;
end;

function FeatureEval(signal d: in Detector; signal FeatureAdress : in unsigned (11 downto 0)) return integer is
begin
	--todo
	return 0;
end;

function RectangleEval(signal d: in Detector; signal RectangleAdress : in unsigned (12 downto 0)) return integer is
begin
	--todo
	return 0;
end;


---- Procedure Example
--  procedure <procedure_name>  (<type_declaration> <constant_name>  : in <type_declaration>) is
--    
--  begin
--    
--  end <procedure_name>;
 
end FACE_DETECTION_PCK;
