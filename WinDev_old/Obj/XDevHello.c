/*  Ofront 1.2 -xtspkaem */
#include "SYSTEM.h"
#include "Console.h"







export main(int argc, char **argv)
{
	__INIT(argc, argv);
	__IMPORT(Console__init);
	__REGMAIN("XDevHello", 0);
/* BEGIN */
	Console_SetColors(Console_LCyanOnBlue);
	Console_WriteStr((CHAR*)"Hello Cross-platform World", (LONGINT)27);
	Console_SetColors(Console_WhiteOnBlack);
	__FINI;
}
