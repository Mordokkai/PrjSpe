package type is

Exemple
constant cdiff: integer;  -- deferred constant
subtype word is bit_vector(15 downto 0);
subtype address is bit_vector (24 downto 0);
type mem is array (0 to 31) of word;
function address2int (val : address) return integer;
function increment_word(val : word) return word;


type Rect is record
	P1:integer;
	P2:integer;
	P3:integer;
	P4:integer;
end record;

type Detector is record
	x:integer;
	y:integer;
end record;

constant W: integer:=128;
constant L: integer:=64;


type Mean is array (0 to 3) of integer;
type Var is array (0 to 3) of integer;
type R is array (0 to 3) of integer;
type Rects is array (0 to 3) of Rect;

variable Ns: INTEGER;
	variable Nf: INTEGER;





end type;

+*>
