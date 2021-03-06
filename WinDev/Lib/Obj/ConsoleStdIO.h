/* Ofront+ 1.0 -sxt3 -48 */

#ifndef ConsoleStdIO__h
#define ConsoleStdIO__h

#include "SYSTEM.h"




import void ConsoleStdIO_WriteCh (CHAR ch);
import void ConsoleStdIO_WriteInt (INTEGER n);
import void ConsoleStdIO_WriteLn (void);
import void ConsoleStdIO_WriteLong (LONGINT n);
import void ConsoleStdIO_WriteReal (REAL x);
import void ConsoleStdIO_WriteRealFix (REAL x, INTEGER n);
import void ConsoleStdIO_WriteStr (CHAR *str, INTEGER str__len);
import void *ConsoleStdIO__init(void);


#endif
