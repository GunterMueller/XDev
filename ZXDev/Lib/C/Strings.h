#ifndef Strings__h
#define Strings__h


extern unsigned int Strings_LengthEx (unsigned int len, unsigned char *str) __z88dk_callee __preserves_regs(iyl,iyh);
#define Strings_Length(str, len) Strings_LengthEx(len, str)
extern unsigned char Strings_IntToStr (int n, unsigned char *str, unsigned int len) __z88dk_callee __preserves_regs(iyl,iyh);
extern unsigned char Strings_UIntToStr (unsigned int n, unsigned char *str, unsigned int len) __z88dk_callee __preserves_regs(iyl,iyh);
extern unsigned char Strings_StrToInt (unsigned char *str, unsigned int len, unsigned int *result);
#define Strings__init()


#endif
