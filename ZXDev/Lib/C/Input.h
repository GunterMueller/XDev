#ifndef Input__h
#define Input__h

#include "XDevCfg.h"


extern unsigned char Input_Available_NoRepeat (void);
extern unsigned char Input_Available_RepeatBuf (void);
#  ifdef Input_KeyNoRepeat
#    define Input_Available Input_Available_NoRepeat
#  endif
#  ifdef Input_KeyRepeat
#    define Input_Available Input_Available_NoRepeat
#  endif
#  ifdef Input_KeyRepeatBuf
#    define Input_Available Input_Available_RepeatBuf
#  endif

extern CHAR Input_Read_NoRepeat (void);
extern CHAR Input_Read_Repeat (void);
extern CHAR Input_Read_RepeatBuf (void);
#  ifdef Input_KeyNoRepeat
#    define Input_Read Input_Read_NoRepeat
#  endif
#  ifdef Input_KeyRepeat
#    define Input_Read Input_Read_Repeat
#  endif
#  ifdef Input_KeyRepeatBuf
#    define Input_Read Input_Read_RepeatBuf
#  endif

extern void Input_RunMe50Hz (void);

#  ifdef Input_KeyRepeatCount
#    define Input__init() (*(unsigned char*) (0x5C09) = (Input_KeyRepeatCount))
#else
#    define Input__init()
#  endif


#endif

