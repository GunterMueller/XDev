#include "SYSTEM.h"
#include "Settings.h"
#include "Basic.h"

interface
export void Basic_Init (void);
export void Basic_BORDER (SHORTINT color);
export void Basic_INK (SHORTINT color);
export void Basic_PAPER (SHORTINT color);
export void Basic_FLASH (SHORTINT mode);
export void Basic_BRIGHT (SHORTINT mode);
export void Basic_INVERSE (SHORTINT mode);
export void Basic_OVER (SHORTINT mode);
export void Basic_AT (SHORTINT y, SHORTINT x);
export void Basic_CLS (void);
export void Basic_PRSTR_C (CHAR *str);
export void Basic_PRCHAR (CHAR ch);
export void Basic_PLOT (SHORTINT x, SHORTINT y);
export SYSTEM_BYTE Basic_POINT (SHORTINT x, SHORTINT y);
export SYSTEM_BYTE Basic_ATTR (SHORTINT y, SHORTINT x);
export void Basic_DRAW (SHORTINT x, SHORTINT y);
export void Basic_CIRCLE (SHORTINT cx, SHORTINT cy, SHORTINT radius);
export void Basic_SlowCircle (SHORTINT cx, SHORTINT cy, SHORTINT radius);
/*export SYSTEM_BYTE Basic_PEEK (SYSTEM_ADDRESS addr);
export void Basic_POKE (SYSTEM_ADDRESS addr, SYSTEM_BYTE value);*/
export SYSTEM_BYTE Basic_PORTIN (SYSTEM_ADDRESS port);
export void Basic_PORTOUT (SYSTEM_ADDRESS port, SYSTEM_BYTE value);
export void Basic_PRINT (INTEGER i);
export void Basic_PRWORD (CARDINAL n);
export BOOLEAN Basic_KeyPressed (void);
export void Basic_PAUSE (CARDINAL ticks);
export void Basic_RANDOMIZE (CARDINAL seed);
#ifndef Basic_RND_SHORTCARD
  export CARDINAL Basic_RND (CARDINAL min, CARDINAL max);
#else
  export SHORTCARD Basic_RND (SHORTCARD min, SHORTCARD max);
#endif
export SHORTINT Basic_SGN (SHORTINT x);
export void Basic_BEEP (CARDINAL ms, SHORTINT freq);
export void Basic_FONT (SYSTEM_ADDRESS addr);
export void Basic_Reset (void);
export void Basic_Quit (void);

implementation

/* Video temp attrib */
#define ATTR_T$ 0x5C8F
/* Set video attrib */
#define SETV_A$ 0x5C8D
/* (Font_address - 256) */
#define CHAR_SET$ 0x5C36

/*================================== Header ==================================*/

void Basic_Init (void)
{
  __asm
  DI /* Turn off 128K mode (This code is written by Wlodek Black */
  LD   IY,#0x5C3A
  //LD   SP,(#23613)
  //POP  HL
  //LD   HL,#4867 /* ERR_SP FOR 48-BASIC */
  //PUSH HL
  //LD   HL,#7030 /* CONTINUE INTERPRETATOR 48-BASIC */
  //PUSH HL
  RES  4,1(IY) /* RESET OF 128K FLAG */
  //LD   DE,#5566 /* INFORMATION FOR STREAMS */
  //LD   HL,(#23631) /* CHANS */
  //LD   BC,#15
  //ADD  HL,BC
  //EX   DE,HL /* DE=ADDR.FOR STREAMS/CHANNELS, HL=5556 */
  //LD   C,#4 /* BC=4 FOR LDIR */
  //LDIR
  //EI
  //RET /* now it is Basic-48. */
  __endasm;
} //Basic_Init

/*--------------------------------- Cut here ---------------------------------*/
void Basic_BORDER (SHORTINT color)
{
__asm
#ifdef __SDCC
  LD   HL,#2
  ADD  HL,SP
  LD   A,(HL)
#else
  LD   A,4(IX)
#endif
  CALL 0x229B // IX-safe
__endasm;
} //Basic_BORDER

/*--------------------------------- Cut here ---------------------------------*/
void Basic_INK (SHORTINT color)
{
__asm
#ifdef __SDCC
  LD   HL,#2
  ADD  HL,SP
  LD   C,(HL)
#else
  LD   C,4(IX)
#endif
  LD   A,(#ATTR_T$)
  AND  #0xF8
  OR   C
  LD   (#SETV_A$),A
  LD   (#ATTR_T$),A
__endasm;
} //Basic_INK

/*--------------------------------- Cut here ---------------------------------*/
void Basic_PAPER (SHORTINT color)
{
__asm
#ifdef __SDCC
  LD   HL,#2
  ADD  HL,SP
  LD   C,(HL)
#else
  LD   C,4(IX)
#endif
  LD   A,(#ATTR_T$)
  AND  #0xC7
  SLA  C
  SLA  C
  SLA  C
  OR   C
  LD   (#SETV_A$),A
  LD   (#ATTR_T$),A
__endasm;
} //Basic_PAPER

/*--------------------------------- Cut here ---------------------------------*/
void Basic_FLASH (SHORTINT mode)
{
__asm
#ifdef __SDCC
  PUSH IX
  LD   IX,#0
  ADD  IX,SP
#endif
  LD   IY,#0x5C3A
  LD   A,#18
  RST  16 // IX-safe
  LD   A,4(IX)
  RST  16
  LD   A,(#ATTR_T$)
  LD   (#SETV_A$),A
#ifdef __SDCC
  POP  IX
#endif
__endasm;
} //Basic_FLASH

/*--------------------------------- Cut here ---------------------------------*/
void Basic_BRIGHT (SHORTINT mode)
{
__asm
#ifdef __SDCC
  PUSH IX
  LD   IX,#0
  ADD  IX,SP
#endif
  LD   IY,#0x5C3A
  LD   A,#19
  RST  16
  LD   A,4(IX)
  RST  16
  LD   A,(#ATTR_T$)
  LD   (#SETV_A$),A
#ifdef __SDCC
  POP  IX
#endif
__endasm;
} //Basic_BRIGHT

/*--------------------------------- Cut here ---------------------------------*/
void Basic_INVERSE (SHORTINT mode)
{
__asm
#ifdef __SDCC
  PUSH IX
  LD   IX,#0
  ADD  IX,SP
#endif
  LD   IY,#0x5C3A
  LD   A,4(IX)
  OR   A
  JR   Z,SetInvers$ /* If INVERSE 0 then poke NOP */
  LD   A,#0x2F      /*              else poke CPL */
SetInvers$:
  LD   (#INV_MODE$),A
  LD   A,#20
  RST  16
  LD   A,4(IX)
  RST  16
#ifdef __SDCC
  POP  IX
#endif
__endasm;
} //Basic_INVERSE

/*--------------------------------- Cut here ---------------------------------*/
void Basic_OVER (SHORTINT mode)
{ // !!! NEED to be checked to IX-safety
__asm
#ifdef __SDCC
  PUSH IX
  LD   IX,#0
  ADD  IX,SP
#endif
  LD   IY,#0x5C3A
  LD   A,4(IX)
  OR   A
  JR   Z,SetOver$ /* If OVER 0 then poke NOP      */
  LD   A,#0xAE    /*           else poke XOR (HL) */
SetOver$:
  LD   (#OVER_MODE$),A
  LD   A,#21
  RST  16
  LD   A,4(IX)
  RST  16
#ifdef __SDCC
  POP  IX
#endif
__endasm;
} //Basic_OVER

/*--------------------------------- Cut here ---------------------------------*/
#ifdef Basic_ROM_OUTPUT
void Basic_AT (SHORTINT y, SHORTINT x)
{
__asm
#ifdef __SDCC
  PUSH IX
  LD   IX,#0
  ADD  IX,SP
#endif
  LD   IY,#0x5C3A
  LD   A,#2
  CALL #0x1601 // IX-safe
  LD   A,#22
  RST  16
  LD   A,4(IX) // y
  RST  16
  LD   A,5(IX) // x
  RST  16
#ifdef __SDCC
  POP  IX
#endif
__endasm;
} //Basic_AT
#endif //Basic_ROM_OUTPUT

#ifndef Basic_ROM_OUTPUT
void Basic_AT (SHORTINT y, SHORTINT x)
{
__asm
#ifdef __SDCC
  PUSH IX
  LD   IX,#0
  ADD  IX,SP
#endif
  LD   A,4(IX)
  CALL #3742
  LD   A,5(IX)
  ADD  A,L
  LD   L,A
  LD   (#23684),HL
#ifdef __SDCC
  POP  IX
#endif
__endasm;
} //Basic_AT
#endif //Basic_ROM_OUTPUT

/*--------------------------------- Cut here ---------------------------------*/
void Basic_CLS (void)
{
__asm
  LD   IY,#0x5C3A
  LD   A,(#ATTR_T$)
  PUSH AF
  CALL 0xD6B // IX-safe
  POP  AF
  LD   (#ATTR_T$),A
__endasm;
} //Basic_CLS

/*--------------------------------- Cut here ---------------------------------*/
void Basic_FONT (SYSTEM_ADDRESS addr)
{
__asm
#ifdef __SDCC
  PUSH IX
  LD   IX,#0
  ADD  IX,SP
#endif
  LD   L,4(IX)
  LD   H,5(IX)
  DEC  H
  LD   (CHAR_SET$),HL
#ifdef __SDCC
  POP  IX
#endif
__endasm;
} //Basic_FONT

/*--------------------------------- Cut here ---------------------------------*/
#ifdef Basic_ROM_OUTPUT
void Basic_PRSTR_C (CHAR *str)
{
/*
	INTEGER i;
	i = 0;
	while (str[i] != 0x00) {
		PRCHAR(str[i]);
		i += 1;
	}
*/
__asm
  LD   IY,#0x5C3A
  LD   A,#2
  CALL #0x1601
#ifdef __SDCC
  LD   HL,#2
  ADD  HL,SP
  LD   C,(HL)
  INC  HL
  LD   B,(HL)
#else
  LD   C,4(IX)
  LD   B,5(IX)
  POP  AF
#endif
PRSTR$:
  LD   A,(BC)
  OR   A
  RET  Z
  RST  16
  INC  BC
  JR   PRSTR$
__endasm;
} //Basic_PRSTR_C
#endif //Basic_ROM_OUTPUT

#ifndef Basic_ROM_OUTPUT
void Basic_PRSTR_C (CHAR *str)
{
__asm
#ifdef __SDCC
  PUSH IX
  LD   IX,#0
  ADD  IX,SP
#endif
  LD   L,4(IX)
  LD   H,5(IX)
pr_sta$:
  LD   A,(HL)
  OR   A
  JR   Z,pr_end$
  PUSH HL
  LD   L,A
  BIT  7,A
  JR   NZ,PO_GR$
  LD   H,#0
  ADD  HL,HL
  ADD  HL,HL
  ADD  HL,HL
  LD   DE,(#CHAR_SET$)
  ADD  HL,DE
  JR   USER_FONT$
PO_GR_BUF$:
  .DB  #0,#0,#0,#0,#0,#0,#0,#0
PO_GR$:
  LD   B,A
  LD   HL,#PO_GR_BUF$
  PUSH HL
  CALL #0xB3E /* Generate po_gr char to buffer */
  CALL #0xB3E
  POP  HL
USER_FONT$:
  LD   DE,(#23684)
  EX   DE,HL
  PUSH HL
  LD   B,#8
p_Sy1$:
  LD   A,(DE)
INV_MODE$:
  NOP
OVER_MODE$:
  NOP
  LD   (HL),A
  INC  DE
  INC  H
  DJNZ p_Sy1$
  POP  HL
  PUSH HL
  LD   A,H
  AND  #0x18
  RRCA
  RRCA
  RRCA
  ADD  A,#0x58
  LD   H,A
  LD   A,(#ATTR_T$)
  LD   (HL),A
  POP  HL
  INC  L
  JR   NZ,p_Sy2$
  LD   A,H
  ADD  A,#8
  LD   H,A
  CP   #0x58
  JR   C,p_Sy2$
  LD   H,#0x40
p_Sy2$:
  LD   (#23684),HL
  POP  HL
  INC  HL
  JR   pr_sta$
pr_end$:
#ifdef __SDCC
  POP  IX
#endif
__endasm;
} //Basic_PRSTR_C
#endif //Basic_ROM_OUTPUT

/*--------------------------------- Cut here ---------------------------------*/
#ifdef Basic_ROM_OUTPUT
void Basic_PRCHAR (CHAR ch)
{
__asm
  LD   IY,#0x5C3A
  LD   A,#2
  CALL #0x1601
#ifdef __SDCC
  LD   HL,#2
  ADD  HL,SP
  LD   A,(HL)
#else
  LD   A,4(IX)
#endif
  RST  16
__endasm;
} //Basic_PRCHAR
#endif //Basic_ROM_OUTPUT

#ifndef Basic_ROM_OUTPUT
void Basic_PRCHAR (CHAR ch)
{
  CHAR str[2];
  str[0] = ch; str[1] = '\x0'; Basic_PRSTR_C(str);
} //Basic_PRCHAR
#endif //Basic_ROM_OUTPUT

/*--------------------------------- Cut here ---------------------------------*/
void Basic_PLOT (SHORTINT x, SHORTINT y)
{
__asm
#ifdef __SDCC
  PUSH IX
  LD   IX,#0
  ADD  IX,SP
#endif
  LD   IY,#0x5C3A
  LD   C,4(IX)
  LD   B,5(IX)
  CALL #0x22E5
#ifdef __SDCC
  POP  IX
#endif
__endasm;
} //Basic_PLOT

/*--------------------------------- Cut here ---------------------------------*/
SYSTEM_BYTE Basic_POINT (SHORTINT x, SHORTINT y)
{
__asm
#ifdef __SDCC
  PUSH IX
  LD   IX,#0
  ADD  IX,SP
#endif
  LD   IY,#0x5C3A
  LD   C,4(IX)
  LD   B,5(IX)
  CALL #0x22CE
  CALL #0x2DD5
  LD   L,A
#ifdef __SDCC
  POP  IX
#endif
__endasm;
} //Basic_POINT

/*--------------------------------- Cut here ---------------------------------*/
SYSTEM_BYTE Basic_ATTR (SHORTINT y, SHORTINT x)
{
__asm
#ifdef __SDCC
  PUSH IX
  LD   IX,#0
  ADD  IX,SP
#endif
  LD   IY,#0x5C3A
  LD   C,4(IX)
  LD   B,5(IX)
  CALL #0x2583
  CALL #0x2DD5
  LD   L,A
#ifdef __SDCC
  POP  IX
#endif
__endasm;
} //Basic_ATTR

/*--------------------------------- Cut here ---------------------------------*/
void Basic_DRAW (SHORTINT x, SHORTINT y)
{
__asm
#ifdef __SDCC
  PUSH IX
  LD   IX,#0
  ADD  IX,SP
#endif
  LD   IY,#0x5C3A
  LD   C,4(IX)
  LD   B,5(IX)
  LD   HL,(#0x5C7D)
  LD   DE,#0x0101
  LD   A,C
  ADD  L
  JR   NC,PositiveX$
  LD   A,C
  NEG
  LD   C,A
  LD   E,#0xFF
PositiveX$:
  LD   A,B
  ADD  H
  JR   NC,PositiveY$
  LD   A,B
  NEG
  LD   B,A
  LD   D,#0xFF
PositiveY$:
  CALL #0x24BA
#ifdef __SDCC
  POP  IX
#endif
__endasm;
} //Basic_DRAW

/*--------------------------------- Cut here ---------------------------------*/
void Basic_CIRCLE (SHORTINT cx, SHORTINT cy, SHORTINT radius)
{
  SHORTINT x, y;
  INTEGER rr, xx, yy;
  x = radius; y = 0; rr = x*x; xx = rr-x; yy = 0;
  do {
    PLOT(cx+x, cy+y); PLOT(cx-x, cy+y);
    PLOT(cx+x, cy-y); PLOT(cx-x, cy-y);
    PLOT(cx+y, cy+x); PLOT(cx-y, cy+x);
    PLOT(cx+y, cy-x); PLOT(cx-y, cy-x);
    yy += y+y+1; y++;
    if (xx > (rr-yy)) {
      xx += 1-x-x; x--;
      PLOT(cx+x, cy+y); PLOT(cx-x, cy+y);
      PLOT(cx+x, cy-y); PLOT(cx-x, cy-y);
      PLOT(cx+y, cy+x); PLOT(cx-y, cy+x);
      PLOT(cx+y, cy-x); PLOT(cx-y, cy-x);
    }
  } while (x >= y);
} //Basic_CIRCLE

/*--------------------------------- Cut here ---------------------------------*/
void Basic_SlowCircle (SHORTINT cx, SHORTINT cy, SHORTINT radius)
{
__asm
#ifdef __SDCC
  PUSH IX
  LD   IX,#0
  ADD  IX,SP
#endif
  LD    A,4(IX) /* cx */
  CALL  0x2D28
  LD    A,5(IX) /* cy */
  CALL  0x2D28
  LD    A,6(IX) /* radius */
  CALL  0x2D28
  CALL  0x232D
#ifdef __SDCC
  POP  IX
#endif
__endasm;
} //Basic_SlowCircle

/*
SYSTEM_BYTE Basic_PEEK (SYSTEM_ADDRESS addr)
{
__asm
#ifdef __SDCC
  PUSH IX
  LD   IX,#0
  ADD  IX,SP
#endif
  LD   L,4(IX)
  LD   H,5(IX)
  LD   L,(HL)
#ifdef __SDCC
  POP  IX
#endif
__endasm;
} //Basic_PEEK

void Basic_POKE (SYSTEM_ADDRESS addr, SYSTEM_BYTE value)
{
__asm
#ifdef __SDCC
  PUSH IX
  LD   IX,#0
  ADD  IX,SP
#endif
  LD   L,4(IX)
  LD   H,5(IX)
  LD   A,6(IX)
  LD   (HL),A
#ifdef __SDCC
  POP  IX
#endif
__endasm;
} //Basic_POKE
*/

/*--------------------------------- Cut here ---------------------------------*/
SYSTEM_BYTE Basic_PORTIN (SYSTEM_ADDRESS port)
{
__asm
#ifdef __SDCC
  PUSH IX
  LD   IX,#0
  ADD  IX,SP
#endif
  LD   C,4(IX)
  LD   B,5(IX)
  IN   L,(C)
#ifdef __SDCC
  POP  IX
#endif
__endasm;
} //Basic_PORTIN

/*--------------------------------- Cut here ---------------------------------*/
void Basic_PORTOUT (SYSTEM_ADDRESS port, SYSTEM_BYTE value)
{
__asm
#ifdef __SDCC
  PUSH IX
  LD   IX,#0
  ADD  IX,SP
#endif
  LD   C,4(IX)
  LD   B,5(IX)
  LD   A,6(IX)
  OUT  (C),A
#ifdef __SDCC
  POP  IX
#endif
__endasm;
} //Basic_PORTOUT

/*--------------------------------- Cut here ---------------------------------*/
void Basic_PRINT (INTEGER i)
{
  CHAR b[6], *prt;
  INTEGER j;
  j = 5;
  b[5] = 0x00;
  do {
    if (i < 0) {
      Basic_PRSTR_C("-");
      if (i == -32768) {
        Basic_PRSTR_C("32768");
        return;
      }
      i = -i;
    }
    j -= 1;
    b[j] = (CHAR)((int)__MOD(i, 10) + 48);
    i = __DIV(i, 10);
  } while (!(j == 0));
  for(prt = b; prt<b+4; prt++) {if(*prt!='0') break;}
  Basic_PRSTR_C(prt);
} //Basic_PRINT
/*
{
__asm
#ifdef __SDCC
  PUSH IX
  LD   IX,#0
  ADD  IX,SP
#endif
  LD   C,4(IX)
  LD   B,5(IX)
  CALL #0x2D2B // BC-TO-FP
  BIT  7,5(IX)
  JR   Z,Positive$
Negative$:
  LD   BC,#0xFFFF
  RST  0x28  // FP_CALC
  .DB  #0xA1 // 1
  .DB  #0x0F // ADD
  .DB  #0x1B // NEG
  .DB  #0x03 // SUB
  .DB  #38   // end-calc
Positive$:
  LD   A,#2
  CALL #0x1601
  CALL #0x2DE3 // PRINT-FP
#ifdef __SDCC
  POP  IX
#endif
__endasm;
}
*/

/*--------------------------------- Cut here ---------------------------------*/
void Basic_PRWORD (CARDINAL n)
{
  CHAR b[6], *prt;
  CARDINAL j;
  j = 5;
  b[5] = 0x00;
  do {
    j -= 1;
    b[j] = (CHAR)((unsigned int)__MOD(n, 10) + 48);
    n = n / 10;
  } while (!(j == 0));
  for(prt = b; prt<b+4; prt++) {if(*prt!='0') break;}
  Basic_PRSTR_C(prt);
} //Basic_PRWORD

/*--------------------------------- Cut here ---------------------------------*/
BOOLEAN Basic_KeyPressed (void)
{ // Check to IX-safety
__asm
    CALL  #0x28E /* Scan keys */
    LD    L,#0   /* FALSE */
    INC   DE
    LD    A,E
    OR    D
    RET   Z
    INC   L      /* TRUE */
__endasm;
} //Basic_KeyPressed

/*--------------------------------- Cut here ---------------------------------*/
void Basic_PAUSE (CARDINAL ticks)
{
__asm
#ifdef __SDCC
  PUSH IX
  LD   IX,#0
  ADD  IX,SP
#endif
  LD   C,4(IX)
  LD   B,5(IX)
  LD   IY,#0x5C3A
  EI
  LD   A,C
  OR   B
  JR   NZ,Pause$
  CALL #0x1F3D
  JR   EndPause$
Pause$:
  HALT
  DEC  BC
  LD   A,C
  OR   B
  JR   NZ,Pause$
EndPause$:
  DI
#ifdef __SDCC
  POP  IX
#endif
__endasm;
} //Basic_PAUSE

/*--------------------------------- Cut here ---------------------------------*/
void Basic_RANDOMIZE (CARDINAL seed)
{
__asm
#ifdef __SDCC
  PUSH IX
  LD   IX,#0
  ADD  IX,SP
#endif
  LD   A,R
  ADC  4(IX)
  LD   C,A
  LD   B,5(IX)
  CALL #0x1E52
#ifdef __SDCC
  POP  IX
#endif
__endasm;
} //Basic_RANDOMIZE

/*--------------------------------- Cut here ---------------------------------*/
/* SEED_RND address */
#define SF_RND$ 0x5C76

static CARDINAL RandBB (void) /* Ripped from Beta Basic */
{
__asm
  LD   D,#0
  LD   BC,(#SF_RND$)
  LD   H,C
  LD   L,#0xFD
  LD   A,B
  OR   A
  SBC  HL,BC
  SBC  A,D
  SBC  HL,BC
  SBC  A,D
  LD   E,A
  SBC  HL,DE
  JR   NC,R1$
  INC  HL
R1$:
  LD  (#SF_RND$),HL
__endasm;
} //RandBB

#ifndef Basic_RND_SHORTCARD
CARDINAL Basic_RND (CARDINAL min, CARDINAL max)
{
  RETURN RandBB()%(max-min+1) + min;
} //Basic_RND
#else
SHORTCARD Basic_RND (SHORTCARD min, SHORTCARD max)
{
  RETURN RandBB()%(max-min+1) + min;
} //Basic_RND
#endif

/*--------------------------------- Cut here ---------------------------------*/
SHORTINT Basic_SGN (SHORTINT x)
{
  if(x <0) return -1;
  if(x==0) return 0;
  return 1;
} //Basic_SGN

/*--------------------------------- Cut here ---------------------------------*/
void Basic_BEEP (CARDINAL ms, SHORTINT freq)
/* Uses Spectrum ROM calculator */
{
__asm
#ifdef __SDCC
  PUSH IX
  LD   IX,#0
  ADD  IX,SP
#endif
  LD   C,4(IX)
  LD   B,5(IX) /* BC = ms */
  LD   A,6(IX) /* A = freq */
  LD   IY,#0x5C3A
  PUSH AF
  CALL 0x2D2B /* Put ms into stack */
  LD   BC,#1000
  CALL 0x2D2B /* Put 1000 into stack */
  RST  40
  .DB  5,56   /* Divide */
  POP  AF
  AND  A
  JP   M,BEPER1$ /* If freq < 0 then goto BEPER1$ */
  CALL #0x2D28 /* Put positive freq into stack */
  JR   DO_BEEP$
BEPER1$:
  NEG         /* Make absolute value */
  CALL #0x2D28 /* and put it into stack */
  RST  40
  .DB  27,56  /* Do it negative */
DO_BEEP$:
  CALL #0x3F8
  DI
#ifdef __SDCC
  POP  IX
#endif
__endasm;
} //Basic_BEEP

/*--------------------------------- Cut here ---------------------------------*/
void Basic_Reset (void)
{
__asm
  RST  0
__endasm;
} //Basic_Reset

/*--------------------------------- Cut here ---------------------------------*/
void Basic_Quit (void)
{
__asm
  LD   HL,#0x2758
  EXX
  LD   IY,#0x5C3A
  EI
__endasm;
} //Basic_Quit

