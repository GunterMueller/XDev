/* Ofront+ 1.0 -s3 -21 */

#ifndef CmdLine__h
#define CmdLine__h

#include "SYSTEM.h"

typedef
	CHAR CmdLine_String[1];




import void CmdLine_GetParam (SHORTINT n, CHAR *param, SHORTINT param__len);
import void *CmdLine__init(void);

#define CmdLine__init()	/*-noinit*/

#endif
