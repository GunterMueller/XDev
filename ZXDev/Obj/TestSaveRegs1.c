/* Ofront+ 0.9 -xtspkaem */
#include "SYSTEM.h"
#include "Basic.h"
#include "Debug.h"






/*============================================================================*/


int main(int argc, char **argv)
{
	__INIT(argc, argv);
	__IMPORT(Basic__init);
	__IMPORT(Debug__init);
	__REGMAIN("TestSaveRegs1", 0);
/* BEGIN */
	Basic_Init();
	Basic_CLS();
	Basic_AT(0, 0);
	Basic_COLOR(6);
	Basic_PRSTR((CHAR*)"AT_ROM_callee ", 15);
	Debug_SaveRegsDef();
	Basic_AT(0, 14);
	Debug_CheckRegs();
	Basic_COLOR(6);
	Basic_PRSTR((CHAR*)"ATTR_callee ", 13);
	Debug_SaveRegsDef();
	if (Basic_ATTR(1, 15) == 0) {
	}
	Debug_CheckRegs();
	Basic_COLOR(6);
	Basic_PRSTR((CHAR*)"BEEP_DI ", 9);
	Debug_SaveRegsDef();
	Basic_BEEP(10, 1);
	Debug_CheckRegs();
	Basic_COLOR(6);
	Basic_PRSTR((CHAR*)"BORDER_fastcall ", 17);
	Debug_SaveRegsDef();
	Basic_BORDER(3);
	Debug_CheckRegs();
	Basic_COLOR(6);
	Basic_PRSTR((CHAR*)"BRIGHT ", 8);
	Debug_SaveRegsDef();
	Basic_BRIGHT(1);
	Debug_CheckRegs();
	Basic_COLOR(6);
	Basic_PRSTR((CHAR*)"CIRCLE ", 8);
	Debug_SaveRegsDef();
	Basic_CIRCLE(250, 170, 3);
	Debug_CheckRegs();
	Basic_COLOR(6);
	Basic_PRSTR((CHAR*)"CIRCLEROM ", 11);
	Debug_SaveRegsDef();
	Basic_CIRCLEROM(240, 170, 3);
	Debug_CheckRegs();
	Basic_COLOR(6);
	Basic_PRSTR((CHAR*)"CIRCLEW_DI ", 12);
	Debug_SaveRegsDef();
	Basic_CIRCLEW(250, 170, 5);
	Debug_CheckRegs();
	Basic_COLOR(6);
	Basic_PRSTR((CHAR*)"PLOT_callee ", 13);
	Debug_SaveRegsDef();
	Basic_PLOT(255, 175);
	Debug_CheckRegs();
	Basic_COLOR(6);
	Basic_PRSTR((CHAR*)"PORTIN ", 8);
	Debug_SaveRegsDef();
	if (Basic_PORTIN(254) == 0) {
	}
	Debug_CheckRegs();
	Basic_COLOR(6);
	Basic_PRSTR((CHAR*)"PORTOUT ", 9);
	Debug_SaveRegsDef();
	Basic_PORTOUT(254, 0);
	Debug_CheckRegs();
	Basic_Quit();
	__FINI;
}
