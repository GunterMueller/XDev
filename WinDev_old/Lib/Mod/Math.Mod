MODULE Math;  (* jt, 10.1.95 *)

IMPORT SYSTEM;

CONST
  Pi* = 3.1415926535;
  E* = 2.7182818285;
  Modulo = 2147483647; (* =2^31-1 *)

VAR
  z: INTEGER;

PROCEDURE -includemath()	"#include <math.h>"; (* define the proper return types! *)
PROCEDURE -includewindows()	"#include <windows.h>";

PROCEDURE -sin (x: REAL): REAL	"(sin(x))";
PROCEDURE -cos (x: REAL): REAL	"(cos(x))";
PROCEDURE -arctan (x: REAL): REAL	"(atan(x))";
PROCEDURE -exp (x: REAL): REAL	"(exp(x))";
PROCEDURE -sqrt (x: REAL): REAL	"(sqrt(x))";
PROCEDURE -ln (x: REAL): REAL	"(log(x))";

PROCEDURE Sin* (x: REAL): REAL;
BEGIN RETURN sin(x)
END Sin;

PROCEDURE Cos* (x: REAL): REAL;
BEGIN RETURN cos(x)
END Cos;

PROCEDURE ArcTan* (x: REAL): REAL;
BEGIN RETURN arctan(x)
END ArcTan;

PROCEDURE Exp* (x: REAL): REAL;
BEGIN RETURN exp(x)
END Exp;

PROCEDURE Sqrt* (x: REAL): REAL;
BEGIN RETURN sqrt(x)
END Sqrt;

PROCEDURE Ln* (x: REAL): REAL;
BEGIN RETURN ln(x)
END Ln;

PROCEDURE -getTickCount (): INTEGER	"GetTickCount()";

(* 
For details on this random algorithm take a look at
  Park S.K. and Miller K.W. (1988). Random number generators, good ones are
  hard to find. Communications of the ACM, 31, 1192-1201.
*)
PROCEDURE PutSeed (seed: INTEGER);
(* Set 'seed' as the new seed value. Any values for 'seed' are allowed, but
   values beyond the intervall [1..2^31-2] will be mapped into this range *)
BEGIN
  seed := seed MOD Modulo;
  IF (seed = 0) THEN
    z := 1
  ELSE
    z := seed
  END;
END PutSeed;

PROCEDURE NextRnd;
CONST
  A = 16807;
  Q = 127773; (* m DIV a *)
  R = 2836; (* m MOD a *)
VAR
  lo, hi, test: INTEGER;
BEGIN
  hi := z DIV Q;
  lo := z MOD Q;
  test := A * lo - R * hi;
  IF (test > 0) THEN
    z := test;
  ELSE
    z := test + Modulo;
  END;
END NextRnd;

(* Returns a random number within the range rangeMin to rangeMax inclusively. *)
PROCEDURE RndRange* (rangeMin, rangeMax: INTEGER): INTEGER;
BEGIN
  ASSERT(rangeMin <= rangeMax);
  NextRnd; RETURN ((z + getTickCount()) MOD (rangeMax - rangeMin + 1)) + rangeMin
END RndRange;

PROCEDURE Randomize* ; (* Initialize random generator *)
BEGIN
  PutSeed(getTickCount());
END Randomize;

BEGIN
  z := 1; Randomize;
END Math.