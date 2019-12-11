/* Ofront+ 1.0 -sx3 -21 */

#ifndef CalcZX__h
#define CalcZX__h

#include "SYSTEM.h"




import SHORTINT CalcZX_PopWordAsInt (void);
import void CalcZX__PushBYTE (BYTE b);
import void CalcZX__PushWORD (SHORTINT w);
import void *CalcZX__init (void);

#define CalcZX_Begin()	__asm rst 0x28 __endasm
#define CalcZX_End()	__asm .db 0x38 __endasm;
#define CalcZX_PopByteAsSInt()	__asm jp 0x2DA2 __endasm
#define CalcZX_Print_PopReal()	__asm call 0x2DE3 __endasm;
#define CalcZX_PushByte(b)	CalcZX__PushBYTE((unsigned char)(b))
#define CalcZX_PushWord(w)	CalcZX__PushWORD((unsigned int)(w))
#define CalcZX__0()	__asm .db 0xA0 __endasm
#define CalcZX__1()	__asm .db 0xA1 __endasm
#define CalcZX__1_div_2()	__asm .db 0xA2 __endasm
#define CalcZX__init()	/*noinit*/
#define CalcZX_abs()	__asm .db 0x2A __endasm
#define CalcZX_acs()	__asm .db 0x23 __endasm
#define CalcZX_add()	__asm .db 0x0F __endasm
#define CalcZX_asn()	__asm .db 0x22 __endasm
#define CalcZX_atn()	__asm .db 0x24 __endasm
#define CalcZX_cos()	__asm .db 0x20 __endasm
#define CalcZX_div()	__asm .db 0x05 __endasm
#define CalcZX_duplicate()	__asm .db 0x31 __endasm
#define CalcZX_exp()	__asm .db 0x26 __endasm
#define CalcZX_int()	__asm .db 0x27 __endasm
#define CalcZX_jump_true()	__asm .db 0x00 __endasm
#define CalcZX_ln()	__asm .db 0x25 __endasm
#define CalcZX_mult()	__asm .db 0x04 __endasm
#define CalcZX_not()	__asm .db 0x30 __endasm
#define CalcZX_or()	__asm .db 0x03 __endasm
#define CalcZX_peek()	__asm .db 0x2B __endasm
#define CalcZX_pi_div_2()	__asm .db 0xA3 __endasm
#define CalcZX_round()	__asm .db 0x2C __endasm
#define CalcZX_sgn()	__asm .db 0x29 __endasm
#define CalcZX_sin()	__asm .db 0x1F __endasm
#define CalcZX_sqr()	__asm .db 0x28 __endasm
#define CalcZX_subtract()	__asm .db 0x03 __endasm
#define CalcZX_tan()	__asm .db 0x21 __endasm
#define CalcZX_to_power()	__asm .db 0x06 __endasm
#define CalcZX_trunc()	__asm .db 0x2C __endasm

#endif
