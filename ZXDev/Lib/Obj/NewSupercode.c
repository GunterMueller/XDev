/*  Ofront 1.2 -xtspkae */
#include "SYSTEM.h"




export void NewSupercode_DZWIEK_1 (void);
export void NewSupercode_DZWIEK_2 (void);
export void NewSupercode_DZWIEK_3 (void);
export void NewSupercode_EKRAN1 (LONGINT adr);
export void NewSupercode_EKRAN2 (LONGINT adr);
export void NewSupercode_EKRAN3 (LONGINT adr);
export void NewSupercode_EKRAN4 (LONGINT adr);
export void NewSupercode_EKRAN_1 (INTEGER x);
export void NewSupercode_EKRAN_2 (INTEGER x);
export void NewSupercode_LITERY (INTEGER x, INTEGER y, INTEGER xs, INTEGER ys, INTEGER wdth, CHAR *str, LONGINT str__len);
export void NewSupercode_SIATKA (INTEGER x, INTEGER y, LONGINT ramtop);
export void NewSupercode__2WIERSZE (LONGINT adr);


/*============================================================================*/

void NewSupercode__2WIERSZE (LONGINT adr)
{
}

/*----------------------------------------------------------------------------*/
void NewSupercode_EKRAN1 (LONGINT adr)
{
}

/*----------------------------------------------------------------------------*/
void NewSupercode_EKRAN2 (LONGINT adr)
{
}

/*----------------------------------------------------------------------------*/
void NewSupercode_EKRAN3 (LONGINT adr)
{
}

/*----------------------------------------------------------------------------*/
void NewSupercode_EKRAN4 (LONGINT adr)
{
}

/*----------------------------------------------------------------------------*/
void NewSupercode_SIATKA (INTEGER x, INTEGER y, LONGINT ramtop)
{
}

/*----------------------------------------------------------------------------*/
void NewSupercode_EKRAN_1 (INTEGER x)
{
}

/*----------------------------------------------------------------------------*/
void NewSupercode_EKRAN_2 (INTEGER x)
{
}

/*----------------------------------------------------------------------------*/
void NewSupercode_LITERY (INTEGER x, INTEGER y, INTEGER xs, INTEGER ys, INTEGER wdth, CHAR *str, LONGINT str__len)
{
}

/*----------------------------------------------------------------------------*/
void NewSupercode_DZWIEK_1 (void)
{
}

/*----------------------------------------------------------------------------*/
void NewSupercode_DZWIEK_2 (void)
{
}

/*----------------------------------------------------------------------------*/
void NewSupercode_DZWIEK_3 (void)
{
}

/*----------------------------------------------------------------------------*/

export void *NewSupercode__init(void)
{
	__DEFMOD;
	__REGMOD("NewSupercode", 0);
	__REGCMD("DZWIEK_1", NewSupercode_DZWIEK_1);
	__REGCMD("DZWIEK_2", NewSupercode_DZWIEK_2);
	__REGCMD("DZWIEK_3", NewSupercode_DZWIEK_3);
/* BEGIN */
	__ENDMOD;
}
