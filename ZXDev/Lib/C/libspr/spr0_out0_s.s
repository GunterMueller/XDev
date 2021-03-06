;-------------------------------------------------
;.include "spr_const.h"
;-------------------------------------------------
; ����������� ����� 256x192, ����������,
; �������� �����������
; ����� ������� ��� ����� � ��� ���������!
;-------------------------------------------------
; ������ �������:
;    IX+0,1    - ���������� ���� � ������� SSZ, ������� ����� ���������.
;        SSZ = W*H*8 + 5 ����
;    IX+2    - ������ ������� W (����������)
;    IX+3    - ������ ������� H (����������)
;    IX+4    - W*H*8 ���� - ������ ������� ���������
;
;    - ������ ������������� ��������� -
;
;    0 ...... W-1    ;
;    0 ...... W-1    ;
;      ......    ; H �����
;    0 ...... W-1    ;
;-------------------------------------------------
    .globl sprXYtoHL
    .globl sprXYtoHLattr

        .module spr0_out0_s
    .area    _CODE
;-------------------------------------------------
; ��������� ������ ������� ��� ���������. ������� 
; ����:
;    L=x, H=y
;    IX - ����� �������
;-------------------------------------------------
.globl spr0_out0
spr0_out0:
    ; ���������� ����� � �������� �������
    call    sprXYtoHL

    ; DE - ������ �������
    push    ix
    ld    de,#4
    add    ix,de
    push    ix
    pop    de
    pop    ix

    ; ������ �������
    ld    b,3(ix)
spr0_out0_hline:    ; ������ ����� �� �������
    push    bc

    ; ������ ���������� (������)
    ld    c,#8
    push    hl

    ; ������� 8 ����� (���� ������)
spr0_out0_line8:
    ld    b,2(ix)

    ; ������� w ���� (���� �����)
    push    hl
spr0_out0_line:
    ld    a,(de)
    ; ������ nop ����� �������� xor (hl), and (hl) ��� or (hl)
spr0_out0_opt:
    nop
    ;
    ld    (hl),a
    inc    hl
    inc    de
    djnz   spr0_out0_line
    pop    hl

    ; ��������� ����� ������
    inc    h
    dec    c
    jr nz,    spr0_out0_line8
    pop    hl

    ; ��������� ������
    ld    a,#0x20
    add    a,l
    ld    l,a

    ; ���� ��� ������� - �� ������� � ����. ����� ������
    jr    nc, continue_1_3

    ; ��������� ����� ������
    ld    a,#0x08
    add    a,h
    ld    h,a        ; hl = hl + 0x0800

continue_1_3:
    ; ����� � �� �� ����� ������
    pop    bc
    djnz    spr0_out0_hline    ; ����� ����� �� ������� (�� �� �����)
    ; �����, ���� ��
    ret
;-------------------------------------------------
; ����� ��� �������� (��������� � ����������)
;-------------------------------------------------
.globl _spr0_out0_setopt_nop
_spr0_out0_setopt_nop:
    ld a,#0x00
    jr spr0_out0_setopt_ep
;-------------------------------------------------
; ����� AND
;-------------------------------------------------
.globl _spr0_out0_setopt_and
_spr0_out0_setopt_and:
    ld a,#0xA6    ; and (hl)
    jr spr0_out0_setopt_ep
;-------------------------------------------------
; ����� OR
;-------------------------------------------------
.globl _spr0_out0_setopt_or
_spr0_out0_setopt_or:
    ld a,#0xB6    ; or (hl)
    jr spr0_out0_setopt_ep
;-------------------------------------------------
; ����� XOR
;-------------------------------------------------
.globl _spr0_out0_setopt_xor
_spr0_out0_setopt_xor:
    ld a,#0xAE    ; xor (hl)
    jr spr0_out0_setopt_ep
;-------------------------------------------------
spr0_out0_setopt_ep:
    ld (spr0_out0_opt),a
    ret
;-------------------------------------------------
; ����� ��������� �������
; ����:
;    IX - ����� �������
;    L=x, H=y
;    DE - ����� ���������
spr0_outattr0:
    call    sprXYtoHLattr
    ; ������ �������
    ld    b,3(ix)
    ld    c,2(ix)
spr0_outattr0_hline:    ; ������ ����� �� �������
    ; �����
    push    bc
    push    hl

spr0_outattr0_line:
    ld    a,(de)
    ld    (hl),a
    inc    de
    inc    l
    dec    c
    jr nz, spr0_outattr0_line

    pop    hl
    ld    bc,#0x0020
    add    hl,bc
    pop    bc
    djnz    spr0_outattr0_hline
    ;
    ret
;-------------------------------------------------
; ��������� ������ ������� � ����������
; ����:
;    L=x, H=y
;    IX - ����� �������
;-------------------------------------------------
.globl spr0_out0_attr
spr0_out0_attr:
    push    hl
    call    spr0_out0
    pop    hl
    jp    spr0_outattr0
;-------------------------------------------------
