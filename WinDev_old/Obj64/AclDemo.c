/*  Ofront 1.2 -xtspkaem */
#include "SYSTEM.h"
#include "AclLib.h"
#include "Ignore.h"
#include "AclUtils.h"
#include "WinApi.h"

typedef
	struct AclDemo_TWnd1 { /* AclLib_TWinControl */
		char _prvt0[800];
		SYSTEM_PTR Brush;
		char _prvt1[8];
		SHORTINT Cursor;
		char _prvt2[148];
		INTEGER Color, TextColor;
		char _prvt3[4];
		SET Style, ExStyle;
		char _prvt4[4];
		INTEGER Left, Top, Width, Height;
		AclLib_PWinControl Parent;
		BOOLEAN AutoStop;
		char _prvt5[15];
		BOOLEAN Enabled, IsModal;
		char _prvt6[7];
		BOOLEAN Visible;
		AclLib_TLabel L1;
		AclLib_TListBox Lb1;
		AclLib_TCheckBox Ch1, Ch2, Ch3, Ch4;
		AclLib_TButton Btn1, Btn2;
		AclLib_TProgressBar Prg1;
	} AclDemo_TWnd1;

static void AclDemo_TWnd1_Btn1Click (AclDemo_TWnd1 *w, LONGINT *w__typ, AclLib_TObject sender);
static void AclDemo_TWnd1_Btn2Click (AclDemo_TWnd1 *w, LONGINT *w__typ, AclLib_TObject sender);
static void AclDemo_TWnd1_WndCreate (AclDemo_TWnd1 *w, LONGINT *w__typ, AclLib_TObject sender);
#define __AclDemo_TWnd1_Btn1Click(w, w__typ, sender) __SEND(w__typ, AclDemo_TWnd1_Btn1Click, 27, void(*)(AclDemo_TWnd1*, LONGINT *, AclLib_TObject), (w, w__typ, sender))
#define __AclDemo_TWnd1_Btn2Click(w, w__typ, sender) __SEND(w__typ, AclDemo_TWnd1_Btn2Click, 28, void(*)(AclDemo_TWnd1*, LONGINT *, AclLib_TObject), (w, w__typ, sender))
#define __AclDemo_TWnd1_WndCreate(w, w__typ, sender) __SEND(w__typ, AclDemo_TWnd1_WndCreate, 29, void(*)(AclDemo_TWnd1*, LONGINT *, AclLib_TObject), (w, w__typ, sender))


static AclDemo_TWnd1 AclDemo_Wnd1;
static CHAR AclDemo_s1[256], AclDemo_s2[256];
static BOOLEAN AclDemo_trig;

export LONGINT *AclDemo_TWnd1__typ;



/*============================================================================*/

static void AclDemo_TWnd1_WndCreate (AclDemo_TWnd1 *w, LONGINT *w__typ, AclLib_TObject sender)
{
	(*w).AutoStop = 1;
}

static void AclDemo_TWnd1_Btn1Click (AclDemo_TWnd1 *w, LONGINT *w__typ, AclLib_TObject sender)
{
}

static void AclDemo_TWnd1_Btn2Click (AclDemo_TWnd1 *w, LONGINT *w__typ, AclLib_TObject sender)
{
}

static void EnumPtrs(void (*P)(void*))
{
	__ENUMR(&AclDemo_Wnd1, AclDemo_TWnd1__typ, 10480, 1, P);
}

__TDESC(AclDemo_TWnd1__desc, 31, 90) = {__TDFLDS("TWnd1", 10480), {0, 8, 800, 808, 824, 832, 960, 1008, 1024, 1048, 1056, 1848, 1856, 1872, 1880, 2008, 
	2056, 2072, 2096, 2104, 2896, 2904, 2920, 2928, 3056, 3104, 3120, 3144, 3152, 3944, 3952, 3968, 
	3976, 4104, 4152, 4168, 4192, 4200, 4992, 5000, 5016, 5024, 5152, 5200, 5216, 5240, 5248, 6040, 
	6048, 6064, 6072, 6200, 6248, 6264, 6288, 6296, 7088, 7096, 7112, 7120, 7248, 7296, 7312, 7336, 
	7344, 8136, 8144, 8160, 8168, 8296, 8344, 8360, 8384, 8392, 9184, 9192, 9208, 9216, 9344, 9392, 
	9408, 9432, 9440, 10232, 10240, 10256, 10264, 10392, 10440, 10456, -728}};

export main(int argc, char **argv)
{
	__INIT(argc, argv);
	__IMPORT(AclLib__init);
	__IMPORT(Ignore__init);
	__IMPORT(AclUtils__init);
	__IMPORT(WinApi__init);
	__REGMAIN("AclDemo", EnumPtrs);
	__INITYP(AclDemo_TWnd1, AclLib_TWinControl, 1);
	__INITBP(AclDemo_TWnd1, AclDemo_TWnd1_Btn1Click, 27);
	__INITBP(AclDemo_TWnd1, AclDemo_TWnd1_Btn2Click, 28);
	__INITBP(AclDemo_TWnd1, AclDemo_TWnd1_WndCreate, 29);
/* BEGIN */
	__MOVE("Sorted ListBox Sample", AclDemo_s1, 22);
	__MOVE("SORTED LISTBOX SAMPLE", AclDemo_s2, 22);
	AclDemo_trig = 0;
	__AclLib_TWinControl_Create((void*)&AclDemo_Wnd1, AclDemo_TWnd1__typ, NIL, NIL);
	AclDemo_Wnd1.Style = 0xc80000;
	__AclLib_TWinControl_SetWidth((void*)&AclDemo_Wnd1, AclDemo_TWnd1__typ, 350);
	__AclLib_TWinControl_SetHeight((void*)&AclDemo_Wnd1, AclDemo_TWnd1__typ, 300);
	__AclLib_TWinControl_SetLeft((void*)&AclDemo_Wnd1, AclDemo_TWnd1__typ, __ASHR(WinApi_GetSystemMetrics(0) - AclDemo_Wnd1.Width, 1));
	__AclLib_TWinControl_SetTop((void*)&AclDemo_Wnd1, AclDemo_TWnd1__typ, __ASHR(WinApi_GetSystemMetrics(1) - AclDemo_Wnd1.Height, 1));
	__AclLib_TWinControl_SetColor((void*)&AclDemo_Wnd1, AclDemo_TWnd1__typ, AclUtils_RGB('3', 0x99, 0xff));
	__AclLib_TWinControl_SetCaption((void*)&AclDemo_Wnd1, AclDemo_TWnd1__typ, (void*)&"Win32 API Programming Sample", (LONGINT)29);
	__AclLib_TWinControl_CreateWnd((void*)&AclDemo_Wnd1, AclDemo_TWnd1__typ);
	__AclLib_TWinControl_SetVisible((void*)&AclDemo_Wnd1, AclDemo_TWnd1__typ, 1);
	Ignore_Int(__AclLib_TWinControl_ShowModal((void*)&AclDemo_Wnd1, AclDemo_TWnd1__typ));
	__FINI;
}
