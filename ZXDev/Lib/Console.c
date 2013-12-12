#include "SYSTEM.h"

/*interface*/
export void Console_At_ROM (SHORTINT x, SHORTINT y);
export void Console_At_COMPACT (SHORTINT x, SHORTINT y);
export void Console_At_FAST (SHORTINT x, SHORTINT y);
export void Console_SetColors (SHORTINT attr);
export void Console_WriteCh_COMPACT (CHAR ch);
export void Console_WriteCh_FAST (CHAR ch);
export void Console_WriteCh_ROM (CHAR ch);
export void Console_WriteInt_ROM (INTEGER i);
export void Console_WriteInt_COMPACT (INTEGER i);
export void Console_WriteInt_FAST (INTEGER i);
export void Console_WriteLn_ROM (void);
export void Console_WriteLn_COMPACT (void);
export void Console_WriteLn_FAST (void);
export void Console_WriteStr_C_COMPACT (void/*CHAR *str*/);
export void Console_WriteStr_C_FAST (void/*CHAR *str*/);
export void Console_WriteStr_C_ROM (void/*CHAR *str*/);
export void Console_Clear_ROM (SHORTCARD attr);
export void Console_Clear_FAST (SHORTCARD attr);
export void Console_Clear_COMPACT (SHORTCARD attr);

void Console_WriteCh_COMPACT_fastcall (void /* Register A */);
void Console_WriteCh_FAST_fastcall (void /* Register A */);

/*implementation*/

/* Set video attrib */
#define SETV_A$   0x5C8D
extern SYSTEM_BYTE __at(SETV_A$) Console_attrib;

/*================================== Header ==================================*/

/* Set video attrib */
SYSTEM_BYTE __at(SETV_A$) Console_attrib;

/*--------------------------------- Cut here ---------------------------------*/
void Console_At_ROM (SHORTINT x, SHORTINT y)
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
  LD   A,5(IX) // y
  RST  16
  LD   A,4(IX) // x
  RST  16
#ifdef __SDCC
  POP  IX
#endif
__endasm;
} //Console_At_ROM

/*--------------------------------- Cut here ---------------------------------*/

void Console_At_COMPACT (SHORTINT x, SHORTINT y)
{
__asm
#ifdef __SDCC
  LD   HL,#2
  ADD  HL,SP
  LD   E,(HL)
  INC  HL
  LD   D,(HL)
#else
  LD   E,4(IX)
  LD   D,5(IX)
#endif
;��������� ������� ������ ��������� �� ���������
; (c) �.��������, �.�����, 1996.
; http://zxpress.ru/book_articles.php?id=633
;������ ������� (E = X; D = Y; 12B; 61T):
  LD   A,D         ; 4
  ADD  A,A         ; 4
  ADD  A,A         ; 4
  ADD  A,A         ; 4
  LD   L,A         ; 4
  LD   H,#0x16     ; 7
  ADD  HL,HL       ;11
  ADD  HL,HL       ;11
  LD   A,L         ; 4
  OR   E           ; 4
  LD   L,A         ; 4
/*
;������ ������� (H = X; L = Y; 10B; 74T):
  LD   A,H         ; 4
  ADD  HL,HL       ;11
  ADD  HL,HL       ;11
  ADD  HL,HL       ;11
  LD   H,#0x16     ; 7
  ADD  HL,HL       ;11
  ADD  HL,HL       ;11
  ADD  A,L         ; 4
  LD   L,A         ; 4
*/
;�� ������ ����� �������� � HL - ����� ����� ���������.
  DEC  HL
  LD   (_ATTR_ADR_C+1),HL
__endasm;
} //Console_At_COMPACT

/*--------------------------------- Cut here ---------------------------------*/
void Console_At_FAST (SHORTINT x, SHORTINT y)
{
__asm
#ifdef __SDCC
  LD   HL,#2
  ADD  HL,SP
  LD   E,(HL)
  INC  HL
  LD   D,(HL)
#else
  LD   E,4(IX)
  LD   D,5(IX)
#endif
;��������� ������� ������ ��������� �� ���������
; (c) �.��������, �.�����, 1996.
; http://zxpress.ru/book_articles.php?id=633
;������ ������� (E = X; D = Y; 12B; 61T):
  LD   A,D         ; 4
  ADD  A,A         ; 4
  ADD  A,A         ; 4
  ADD  A,A         ; 4
  LD   L,A         ; 4
  LD   H,#0x16     ; 7
  ADD  HL,HL       ;11
  ADD  HL,HL       ;11
  LD   A,L         ; 4
  OR   E           ; 4
  LD   L,A         ; 4
/*
;������ ������� (H = X; L = Y; 10B; 74T):
  LD   A,H         ; 4
  ADD  HL,HL       ;11
  ADD  HL,HL       ;11
  ADD  HL,HL       ;11
  LD   H,#0x16     ; 7
  ADD  HL,HL       ;11
  ADD  HL,HL       ;11
  ADD  A,L         ; 4
  LD   L,A         ; 4
*/
;�� ������ ����� �������� � HL - ����� ����� ���������.
  DEC  HL
  LD   (_ATTR_ADR_F+1),HL
__endasm;
} //Console_At_FAST

/*--------------------------------- Cut here ---------------------------------*/

/* (Font_address - 256) */
#define CHAR_SET$ 0x5C36

void Console_WriteCh_COMPACT_fastcall (void /* Register A */)
{ // http://www.zxpress.ru/article.php?id=9493
__asm
.globl _ATTR_ADR_C
  LD   (_CHAR_CODE_C$+1),A
  LD   HL,#_ATTR_ADR_C+1
  INC  (HL)
  CALL Z, _INC_HBYTE_C
_ATTR_ADR_C:
  LD   DE,#0x5800-1    ;DE = �������� �����
  LD   A,(SETV_A$)     ;��������� ���� �������
  LD   (DE),A
;������ ��������� ������ �� ������ ���������
; (c) �.��������, �.�����, 1996.
; http://zxpress.ru/book_articles.php?id=633
;����: DE = ����� ���������
  LD   A,D             ; 4
  ADD  A,A             ; 4
  ADD  A,A             ; 4
  ADD  A,A             ; 4
  AND  #0x7F           ; 7
  LD   D,A             ; 4 = 27T
;�����: DE = �������� �����
; =====������ ������� 8�8 (compact) =====
_CHAR_CODE_C$:         ;in: L - ��� �������
  LD   HL,#0           ;���������� ������ �������
  ADD  HL,HL
  ADD  HL,HL
  ADD  HL,HL
  LD   BC,(0x5C36)
  ADD  HL,BC
  LD   B,#7
PRLOOP$:
  LD   A,(HL)          ;����� ���� �� �����
  LD   (DE),A          ;� ������ � �����
  INC  HL              ;���������� fnt adr
  INC  D               ;���������� scr adr
  DJNZ PRLOOP$
  LD   A,(HL)          ;� ��� 8 ���
  LD   (DE),A
__endasm;
} //Console_WriteCh_COMPACT_fastcall

/*--------------------------------- Cut here ---------------------------------*/
void Console_WriteCh_COMPACT (CHAR ch)
{
__asm
#ifdef __SDCC
  LD   HL,#2
  ADD  HL,SP
  LD   A,(HL)
#else
  LD   A,4(IX)
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

void Console_WriteCh_FAST_fastcall (void /* Register A */)
{ // http://www.zxpress.ru/article.php?id=9493
__asm
.globl _ATTR_ADR_F
  LD   (_CHAR_CODE_F$+1),A
  LD   HL,#_ATTR_ADR_F+1
  INC  (HL)
  CALL Z, _INC_HBYTE_F
_ATTR_ADR_F:
  LD   DE,#0x5800-1    ;DE = �������� �����
  LD   A,(SETV_A$)     ;��������� ���� �������
  LD   (DE),A
;������ ��������� ������ �� ������ ���������
; (c) �.��������, �.�����, 1996.
; http://zxpress.ru/book_articles.php?id=633
;����: DE = ����� ���������
  LD   A,D             ; 4
  ADD  A,A             ; 4
  ADD  A,A             ; 4
  ADD  A,A             ; 4
  AND  #0x7F           ; 7
  LD   D,A             ; 4 = 27T
;�����: DE = �������� �����
; =====������ ������� 8�8 (compact) =====
_CHAR_CODE_F$:         ;in: L - ��� �������
  LD   HL,#0           ;���������� ������ �������
  ADD  HL,HL
  ADD  HL,HL
  ADD  HL,HL
  LD   BC,(0x5C36)
  ADD  HL,BC
  DUP_7                ;� ��� 8 ���
  DUP_7
  DUP_7
  DUP_7
  DUP_7
  DUP_7
  DUP_7
  LD   A,(HL)
  LD   (DE),A
__endasm;
} //Console_WriteCh_FAST_fastcall

/*--------------------------------- Cut here ---------------------------------*/
void Console_WriteCh_FAST (CHAR ch)
{
__asm
#ifdef __SDCC
  LD   HL,#2
  ADD  HL,SP
  LD   A,(HL)
#else
  LD   A,4(IX)
#endif
__endasm;
  Console_WriteCh_FAST_fastcall();
} //Console_WriteCh_FAST

/*--------------------------------- Cut here ---------------------------------*/
void Console_WriteCh_ROM (CHAR ch)
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
void Console_WriteLn_ROM (void)
{
__asm
  LD   A,#0x0D
  RST  16
__endasm;
} //Console_WriteLn_ROM

/*--------------------------------- Cut here ---------------------------------*/
void Console_WriteLn_COMPACT (void)
{
__asm
.globl _INC_HBYTE_C
  LD   HL,#_ATTR_ADR_C+1
  LD   A,(HL)
  OR   #0x1F
  CP   (HL)
  LD   (HL),A
  RET  NZ
  ADD  A,#0x20
  LD   (HL),A
  RET  NC
_INC_HBYTE_C:
  INC  HL              ;���������� ��������
  INC  (HL)            ;������ ��������� (� ���������)
  LD   A,(HL)
  CP   #0x5B
  RET  C
  LD   HL,#0x5AE0-1
  LD   (_ATTR_ADR_C+1),HL
  LD   B,#23
  JP   0xE00           ;����� CL_SCROLL
__endasm;
} //Console_WriteLn_COMPACT

/*--------------------------------- Cut here ---------------------------------*/
void Console_WriteLn_FAST (void)
{
__asm
.globl _INC_HBYTE_F
  LD   HL,#_ATTR_ADR_F+1
  LD   A,(HL)
  OR   #0x1F
  CP   (HL)
  LD   (HL),A
  RET  NZ
  ADD  A,#0x20
  LD   (HL),A
  RET  NC
_INC_HBYTE_F:
  INC  HL              ;���������� ��������
  INC  (HL)            ;������ ��������� (� ���������)
  LD   A,(HL)
  CP   #0x5B
  RET  C
  LD   HL,#0x5AE0-1
  LD   (_ATTR_ADR_F+1),HL
  LD   B,#23
  JP   0xE00           ;����� CL_SCROLL
__endasm;
} //Console_WriteLn_FAST

/*--------------------------------- Cut here ---------------------------------*/
void Console_WriteStr_C_COMPACT (void/*CHAR *str*/)
{
__asm
  LD   HL,(_SYSTEM_str_par)
WRSTR_C$:
  LD   A,(HL)
  OR   A
  RET  Z
  PUSH HL
  CALL _Console_WriteCh_COMPACT_fastcall
  POP  HL
  INC  HL
  JR   WRSTR_C$
__endasm;
} //Console_WriteStr_C_COMPACT

/*--------------------------------- Cut here ---------------------------------*/
void Console_WriteStr_C_FAST (void/*CHAR *str*/)
{
__asm
  LD   HL,(_SYSTEM_str_par)
WRSTR_F$:
  LD   A,(HL)
  OR   A
  RET  Z
  PUSH HL
  CALL _Console_WriteCh_FAST_fastcall
  POP  HL
  INC  HL
  JR   WRSTR_F$
__endasm;
} //Console_WriteStr_C_FAST

/*--------------------------------- Cut here ---------------------------------*/
void Console_WriteStr_C_ROM (void/*CHAR *str*/)
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
void Console_WriteInt_ROM (INTEGER i)
{
  CHAR b[6], *prt;
  INTEGER j;
  j = 5;
  b[5] = 0x00;
  do {
    if (i < 0) {
      Console_WriteCh_ROM('-');
      if (i == -32768) {
        SYSTEM_str_par = (CHAR*)"32768"; Console_WriteStr_C_ROM();
        return;
      }
      i = -i;
    }
    j -= 1;
    b[j] = (CHAR)((int)__MOD(i, 10) + 48);
    i = __DIV(i, 10);
  } while (!(j == 0));
  for(prt = b; prt<b+4; prt++) {if(*prt!='0') break;}
  SYSTEM_str_par = (CHAR*)prt; Console_WriteStr_C_ROM();

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
} //Console_WriteInt_ROM

/*--------------------------------- Cut here ---------------------------------*/
void Console_WriteInt_COMPACT (INTEGER i)
{
  CHAR b[6], *prt;
  INTEGER j;
  j = 5;
  b[5] = 0x00;
  do {
    if (i < 0) {
      Console_WriteCh_COMPACT('-');
      if (i == -32768) {
        SYSTEM_str_par = (CHAR*)"32768"; Console_WriteStr_C_COMPACT();
        return;
      }
      i = -i;
    }
    j -= 1;
    b[j] = (CHAR)((int)__MOD(i, 10) + 48);
    i = __DIV(i, 10);
  } while (!(j == 0));
  for(prt = b; prt<b+4; prt++) {if(*prt!='0') break;}
  SYSTEM_str_par = (CHAR*)prt; Console_WriteStr_C_COMPACT();
} //Console_WriteInt_COMPACT

/*--------------------------------- Cut here ---------------------------------*/

void Console_WriteInt_FAST (INTEGER i)
{
  CHAR b[6], *prt;
  INTEGER j;
  j = 5;
  b[5] = 0x00;
  do {
    if (i < 0) {
      Console_WriteCh_FAST('-');
      if (i == -32768) {
        SYSTEM_str_par = (CHAR*)"32768"; Console_WriteStr_C_FAST();
        return;
      }
      i = -i;
    }
    j -= 1;
    b[j] = (CHAR)((int)__MOD(i, 10) + 48);
    i = __DIV(i, 10);
  } while (!(j == 0));
  for(prt = b; prt<b+4; prt++) {if(*prt!='0') break;}
  SYSTEM_str_par = (CHAR*)prt; Console_WriteStr_C_FAST();
} //Console_WriteInt_FAST
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

/*--------------------------------- Cut here ---------------------------------*/
void Console_Clear_ROM (SHORTCARD attr)
{
__asm
  LD   IY,#0x5C3A
#ifdef __SDCC
  LD   HL,#2
  ADD  HL,SP
  LD   A,(HL)
#else
  LD   A,4(IX)
#endif
  LD   (_Console_attrib),A
  RRCA
  RRCA
  RRCA
  CALL 0x229B
  CALL 0xD6B // IX-safe
__endasm;
} //Console_Clear_ROM

/*--------------------------------- Cut here ---------------------------------*/
void Console_Clear_FAST (SHORTCARD attr)
{
__asm
  LD   IY,#0x5C3A
  LD   HL,#0x5800-1
  LD   (_ATTR_ADR_F+1),HL
#ifdef __SDCC
  LD   HL,#2
  ADD  HL,SP
  LD   A,(HL)
#else
  LD   A,4(IX)
#endif
  LD   (_Console_attrib),A
  RRCA
  RRCA
  RRCA
  CALL 0x229B
  CALL 0xD6B // IX-safe
__endasm;
} //Console_Clear_FAST

/*--------------------------------- Cut here ---------------------------------*/
void Console_Clear_COMPACT (SHORTCARD attr)
{
__asm
  LD   IY,#0x5C3A
  LD   HL,#0x5800-1
  LD   (_ATTR_ADR_C+1),HL
#ifdef __SDCC
  LD   HL,#2
  ADD  HL,SP
  LD   A,(HL)
#else
  LD   A,4(IX)
#endif
  LD   (_Console_attrib),A
  RRCA
  RRCA
  RRCA
  CALL 0x229B
  CALL 0xD6B // IX-safe
__endasm;
} //Console_Clear_COMPACT

