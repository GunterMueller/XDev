#include "SYSTEM.h"

/*interface*/
export void Console_SetColors (SHORTINT attr);
export void Console_WriteCh_COMPACT (CHAR ch);
export void Console_WriteCh_FAST (CHAR ch);
export void Console_WriteCh_ROM (CHAR ch);
export void Console_WriteStr_C_COMPACT (void/*CHAR *str*/);
export void Console_WriteStr_C_FAST (void/*CHAR *str*/);
export void Console_WriteStr_C_ROM (void/*CHAR *str*/);
void Console_WriteCh_COMPACT_fastcall (void /* Register L */);
void Console_WriteCh_FAST_fastcall (void /* Register L */);

/*implementation*/

/* Set video attrib */
#define SETV_A$   0x5C8D
extern SYSTEM_BYTE __at(SETV_A$) Console_attrib;

/*================================== Header ==================================*/

/* Set video attrib */
export SYSTEM_BYTE __at(SETV_A$) Console_attrib;

/*
export void Console_SetColors (SHORTINT attr)
{
__asm
#ifdef __SDCC
  LD   HL,#2
  ADD  HL,SP
  LD   A,(HL)
#else
  LD   A,4(IX)
#endif
  LD   (#_Console_attrib),A
__endasm;
} //Console_SetColors
*/

/*--------------------------------- Cut here ---------------------------------*/

/* (Font_address - 256) */
#define CHAR_SET$ 0x5C36

void Console_WriteCh_COMPACT_fastcall (void /* Register L */)
{ // http://www.zxpress.ru/article.php?id=9493
__asm
; =====������ ������� 8�8 (fast) =====
                       ;in: L - ��� �������
  ADD  HL,HL           ;����������
  LD   H,#15           ;������ �������
  ADD  HL,HL           ; � ��� (AlCo)
  ADD  HL,HL
DF_CC_C$:
  LD   DE,#0x4000      ;DE = ����������
  LD   B,#7
PRLOOP$:
  LD   A,(HL)          ;����� ���� �� �����
  LD   (DE),A          ;� ������ � �����
  INC  HL              ;���������� fnt adr
  INC  D               ;���������� scr adr
  DJNZ PRLOOP$
  LD   A,(HL)          ;� ��� 8 ���
  LD   (DE),A
; =========scr adr -> attr adr========
; in: DE - screen adress
; out:DE - attr adress
  LD   A,D         ; 4
  RRCA             ; 4
  RRCA             ; 4
  RRCA             ; 4
  AND  #3          ; 7
  OR   #0x58       ; 7
  LD   D,A         ; 4 = 34
  LD   A,(SETV_A$)
  LD   (DE),A
;���������� ��������� ������ (� ���������)
  LD   HL,(DF_CC_C$+1)
  INC  L               ;���������� ���������
  JR   NZ,NONEXT_C$
  LD   A,H
  CP   A,#0x50
  JR   NZ,NOSCRL_C$
  LD   B,#23
  CALL 0xE00           ;����� CL_SCROLL
  LD   HL,#0x50E0
  JR   NONEXT_C$
NOSCRL_C$:
  ADD  A,#8
  LD   H,A
NONEXT_C$:
  LD   (DF_CC_C$+1),HL
__endasm;
} //Console_WriteCh_COMPACT_fastcall

/*--------------------------------- Cut here ---------------------------------*/
export void Console_WriteCh_COMPACT (CHAR ch)
{
__asm
#ifdef __SDCC
  LD   HL,#2
  ADD  HL,SP
  LD   L,(HL)
#else
  LD   L,4(IX)
#endif
__endasm;
  Console_WriteCh_COMPACT_fastcall();
} //Console_WriteCh_COMPACT
/*--------------------------------- Cut here ---------------------------------*/

/* (Font_address - 256) */
#define CHAR_SET$ 0x5C36

#define DUP_7 \
  LD   A,(HL) ;����� ���� �� ����� \
  LD   (DE),A ;� ������ � �����   \
  INC  HL     ;���������� fnt adr \
  INC  D      ;���������� scr adr

void Console_WriteCh_FAST_fastcall (void /* Register L */)
{ // http://www.zxpress.ru/article.php?id=9493
__asm
; =====������ ������� 8�8 (fast) =====
                       ;in: L - ��� �������
  ADD  HL,HL           ;����������
  LD   H,#15           ;������ �������
  ADD  HL,HL           ; � ��� (AlCo)
  ADD  HL,HL
DF_CC_F$:
  LD   DE,#0x4000      ;DE = ����������
  DUP_7                ;� ��� 8 ���
  DUP_7
  DUP_7
  DUP_7
  DUP_7
  DUP_7
  DUP_7
  LD   A,(HL)
  LD   (DE),A
; =========scr adr -> attr adr========
; in: DE - screen adress
; out:DE - attr adress
  LD   A,D         ; 4
  RRCA             ; 4
  RRCA             ; 4
  RRCA             ; 4
  AND  #3          ; 7
  OR   #0x58       ; 7
  LD   D,A         ; 4 = 34
  LD   A,(SETV_A$)
  LD   (DE),A
;���������� ��������� ������ (� ���������)
  LD   HL,(DF_CC_F$+1)
  INC  L               ;���������� ���������
  JR   NZ,NONEXT_F$
  LD   A,H
  CP   A,#0x50
  JR   NZ,NOSCRL_F$
  LD   B,#23
  CALL 0xE00           ;����� CL_SCROLL
  LD   HL,#0x50E0
  JR   NONEXT_F$
NOSCRL_F$:
  ADD  A,#8
  LD   H,A
NONEXT_F$:
  LD   (DF_CC_F$+1),HL
__endasm;
} //Console_WriteCh_FAST_fastcall

/*--------------------------------- Cut here ---------------------------------*/
export void Console_WriteCh_FAST (CHAR ch)
{
__asm
#ifdef __SDCC
  LD   HL,#2
  ADD  HL,SP
  LD   L,(HL)
#else
  LD   L,4(IX)
#endif
__endasm;
  Console_WriteCh_FAST_fastcall();
} //Console_WriteCh_FAST

/*--------------------------------- Cut here ---------------------------------*/
export void Console_WriteCh_ROM (CHAR ch)
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
} //Console_WriteCh_ROM

/*--------------------------------- Cut here ---------------------------------*/
export void Console_WriteStr_C_COMPACT (void/*CHAR *str*/)
{
__asm
  LD   HL,(_SYSTEM_str_par)
WRSTR_C$:
  LD   A,(HL)
  OR   A
  RET  Z
  PUSH HL
  LD   L,A
  CALL _Console_WriteCh_COMPACT_fastcall
  POP  HL
  INC  HL
  JR   WRSTR_C$
__endasm;
} //Console_WriteStr_C_COMPACT

/*--------------------------------- Cut here ---------------------------------*/
export void Console_WriteStr_C_FAST (void/*CHAR *str*/)
{
__asm
  LD   BC,(_SYSTEM_str_par)
WRSTRF$:
  LD   A,(BC)
  OR   A
  RET  Z
  LD   L,A
  CALL _WR_CHAR_F
  INC  BC
  JR   WRSTRF$
__endasm;
} //Console_WriteStr_C_FAST

/*--------------------------------- Cut here ---------------------------------*/
export void Console_WriteStr_C_ROM (void/*CHAR *str*/)
{
__asm
  LD   IY,#0x5C3A
  LD   A,#2
  CALL #0x1601
  LD   BC,(_SYSTEM_str_par)
WRSTR_R$:
  LD   A,(BC)
  OR   A
  RET  Z
  RST  16
  INC  BC
  JR   WRSTR_R$
__endasm;
} //Console_WriteStr_C_ROM

/*--------------------------------- Cut here ---------------------------------*/
export void Console_WriteInt (INTEGER i)
{
/*
// http://www.zxpress.ru/article.php?id=1692
PDEC_W$:  ;������ ����������� ����� � HL3 (00000..65535)
  PUSH    HL            ;�������� ���������� ����� �� ����
  LD      HL,DECTB_W    ;����� ������� �������� �������
  LD      B,#05         ;����. ��������� ���������� ����
LP_PDW1$:
  LD      E,(HL)        ;����� ������� �������
  INC     HL            ; ������� �� �������
  LD      D,(HL)        ; � ��������� � DE
  INC     HL            ;������� � ����. �������� �������
  EX      (SP),HL       ;����� ��-�� <-> ���������� �����
  XOR     A             ;�������� ������� � ���� C ��� SBC
LP_PDW2$:
  INC     A             ;����������� �������
  SBC     HL,DE         ;�������� ������� ������� �������
  JR      NC,LP_PDW2    ;��������� ���� HL>=0
  ADD     HL,DE         ;HL=HL mod DE; A=HL div DE
  ADD     A,"0"-1       ;������� A � ASCII-��� ("0".."9")
  RST     #10           ;������ ���������� �����
  EX      (SP),HL       ;HL=����� ��-��, ����� -> �� ����
  DJNZ    LP_PDW1       ;���� �� ������
  POP     HL            ;������ ���������� ���� �� �����
  ;RET                   ;����� �� ���������
*/
} //Console_WriteInt

/*
;=========���������� -> scr adr========
;in: D - Y ����������, E - X ����������
;out:DE - screen adress
        LD A,D
        AND 7
        RRCA
        RRCA
        RRCA
        OR E
        LD E,A
        LD A,D
        AND 24
        OR 64
        LD D,A
*/

