/*  Ofront 1.2 -xtspkae */
#include "SYSTEM.h"

typedef
	struct Files_File {
		INTEGER handle, prevbyte;
		BOOLEAN end, error;
	} Files_File;

export void Files_File_Close (Files_File *file, LONGINT *file__typ);
typedef
	CHAR *Files_STRING;

export void Files_File_OpenToRead (Files_File *file, LONGINT *file__typ, CHAR *fname, LONGINT fname__len);
export void Files_File_OpenToWrite (Files_File *file, LONGINT *file__typ, CHAR *fname, LONGINT fname__len);
#define __Files_File_Close(file, file__typ) __SEND(file__typ, Files_File_Close, 0, void(*)(Files_File*, LONGINT *), (file, file__typ))
#define __Files_File_OpenToRead(file, file__typ, fname, fname__len) __SEND(file__typ, Files_File_OpenToRead, 1, void(*)(Files_File*, LONGINT *, CHAR*, LONGINT ), (file, file__typ, fname, fname__len))
#define __Files_File_OpenToWrite(file, file__typ, fname, fname__len) __SEND(file__typ, Files_File_OpenToWrite, 2, void(*)(Files_File*, LONGINT *, CHAR*, LONGINT ), (file, file__typ, fname, fname__len))

typedef
	struct Files_FileToRead { /* Files_File */
		INTEGER handle, prevbyte;
		BOOLEAN end, error;
	} Files_FileToRead;

export SYSTEM_BYTE Files_FileToRead_ReadByte (Files_FileToRead *fromfile, LONGINT *fromfile__typ);
#define __Files_FileToRead_ReadByte(fromfile, fromfile__typ) __SEND(fromfile__typ, Files_FileToRead_ReadByte, 3, SYSTEM_BYTE(*)(Files_FileToRead*, LONGINT *), (fromfile, fromfile__typ))

typedef
	struct Files_FileToWrite { /* Files_File */
		INTEGER handle, prevbyte;
		BOOLEAN end, error;
	} Files_FileToWrite;

export void Files_FileToWrite_WriteByte (Files_FileToWrite *tofile, LONGINT *tofile__typ, SYSTEM_BYTE byte);
export void Files_FileToWrite_WriteStr (Files_FileToWrite *tofile, LONGINT *tofile__typ, CHAR *str, LONGINT str__len);
#define __Files_FileToWrite_WriteByte(tofile, tofile__typ, byte) __SEND(tofile__typ, Files_FileToWrite_WriteByte, 3, void(*)(Files_FileToWrite*, LONGINT *, SYSTEM_BYTE), (tofile, tofile__typ, byte))
#define __Files_FileToWrite_WriteStr(tofile, tofile__typ, str, str__len) __SEND(tofile__typ, Files_FileToWrite_WriteStr, 4, void(*)(Files_FileToWrite*, LONGINT *, CHAR*, LONGINT ), (tofile, tofile__typ, str, str__len))

typedef
	CHAR *Files_PtrSTR;

export BOOLEAN Files_DeleteFile (CHAR *fname, LONGINT fname__len);
export BOOLEAN Files_ExistsFile (CHAR *fname, LONGINT fname__len);

#define Files_EOF()	EOF
#define Files_NULL() ((int)NULL)
#define Files_fclose(file)	fclose((FILE*)file)
#define Files_feof(file)	feof((FILE*)file)
#define Files_ferror(file)	ferror((FILE*)file)
#define Files_fgetc(file)	fgetc((FILE*)file)
#define Files_fopen(filename, filename__len, mode, mode__len)	(int)fopen((char*)filename, (char*)mode)
#define Files_fputc(c, file)	fputc(c, (FILE*)file)
#include <stdio.h>
#include <unistd.h>
#define Files_unlink(filename, filename__len)	unlink(filename)

extern LONGINT *Files_File__typ;
extern LONGINT *Files_FileToRead__typ;
extern LONGINT *Files_FileToWrite__typ;

/*================================== Header ==================================*/
export LONGINT *Files_File__typ;
/*--------------------------------- Cut here ---------------------------------*/
export LONGINT *Files_FileToRead__typ;
/*--------------------------------- Cut here ---------------------------------*/
export LONGINT *Files_FileToWrite__typ;

/*--------------------------------- Cut here ---------------------------------*/
void Files_File_OpenToRead (Files_File *file, LONGINT *file__typ, CHAR *fname, LONGINT fname__len)
{
	(*file).handle = Files_fopen(fname, fname__len, (CHAR*)"rb", (LONGINT)3);
	if ((*file).handle != Files_NULL()) {
		(*file).prevbyte = Files_fgetc((*file).handle);
		if ((*file).prevbyte != Files_EOF()) {
			(*file).end = 0;
			(*file).error = 0;
		} else {
			(*file).end = Files_feof((*file).handle) != 0;
			(*file).error = Files_ferror((*file).handle) != 0;
			if ((*file).error) {
				__Files_File_Close(&*file, file__typ);
			}
		}
	} else {
		(*file).end = 1;
		(*file).error = 1;
	}
}

/*--------------------------------- Cut here ---------------------------------*/
void Files_File_OpenToWrite (Files_File *file, LONGINT *file__typ, CHAR *fname, LONGINT fname__len)
{
	(*file).error = 0;
	(*file).handle = Files_fopen(fname, fname__len, (CHAR*)"wb", (LONGINT)3);
	if ((*file).handle == 0) {
		(*file).error = 1;
	}
}

/*--------------------------------- Cut here ---------------------------------*/
void Files_File_Close (Files_File *file, LONGINT *file__typ)
{
	if ((*file).handle != 0) {
		if (Files_fclose((*file).handle) != 0) {
			(*file).error = 1;
		}
		(*file).handle = 0;
	} else {
		(*file).error = 1;
	}
}

/*--------------------------------- Cut here ---------------------------------*/
SYSTEM_BYTE Files_FileToRead_ReadByte (Files_FileToRead *fromfile, LONGINT *fromfile__typ)
{
	INTEGER result;
	if ((*fromfile).end || (*fromfile).error) {
		return (int)Files_EOF();
	}
	result = (*fromfile).prevbyte;
	(*fromfile).prevbyte = Files_fgetc((*fromfile).handle);
	if ((*fromfile).prevbyte == Files_EOF()) {
		(*fromfile).end = Files_feof((*fromfile).handle) != 0;
		(*fromfile).error = Files_ferror((*fromfile).handle) != 0;
	}
	return (int)result;
}

/*--------------------------------- Cut here ---------------------------------*/
void Files_FileToWrite_WriteByte (Files_FileToWrite *tofile, LONGINT *tofile__typ, SYSTEM_BYTE byte)
{
	INTEGER exitcode;
	if ((*tofile).error) {
		return;
	}
	exitcode = Files_fputc((int)(__VAL(CHAR, byte)), (*tofile).handle);
	if (exitcode == Files_EOF()) {
		if (Files_feof((*tofile).handle) != 0) {
			(*tofile).end = 1;
		}
	}
}

/*--------------------------------- Cut here ---------------------------------*/
void Files_FileToWrite_WriteStr (Files_FileToWrite *tofile, LONGINT *tofile__typ, CHAR *str, LONGINT str__len)
{
	LONGINT n;
	n = 0;
	while (n < str__len && str[__X(n, str__len)] != 0x00) {
		__Files_FileToWrite_WriteByte(&*tofile, tofile__typ, str[__X(n, str__len)]);
		if ((*tofile).error) {
			return;
		}
		n += 1;
	}
}

/*--------------------------------- Cut here ---------------------------------*/
BOOLEAN Files_DeleteFile (CHAR *fname, LONGINT fname__len)
{
	return Files_unlink(fname, fname__len) == 0;
}

/*--------------------------------- Cut here ---------------------------------*/
BOOLEAN Files_ExistsFile (CHAR *fname, LONGINT fname__len)
{
	Files_FileToRead f;
	__Files_File_OpenToRead((void*)&f, Files_FileToRead__typ, fname, fname__len);
	__Files_File_Close((void*)&f, Files_FileToRead__typ);
	return !f.error;
}

/*--------------------------------- Cut here ---------------------------------*/
/*
__TDESC(Files_File, 4, 0) = {__TDFLDS("File", 8), {-4}};
__TDESC(Files_FileToRead, 5, 0) = {__TDFLDS("FileToRead", 8), {-4}};
__TDESC(Files_FileToWrite, 5, 0) = {__TDFLDS("FileToWrite", 8), {-4}};

export void *Files__init(void)
{
	__DEFMOD;
	__REGMOD("Files", 0);
	__INITYP(Files_File, Files_File, 0);
	__INITBP(Files_File, Files_File_Close, 0);
	__INITBP(Files_File, Files_File_OpenToRead, 1);
	__INITBP(Files_File, Files_File_OpenToWrite, 2);
	__INITYP(Files_FileToRead, Files_File, 1);
	__INITBP(Files_FileToRead, Files_FileToRead_ReadByte, 3);
	__INITYP(Files_FileToWrite, Files_File, 1);
	__INITBP(Files_FileToWrite, Files_FileToWrite_WriteByte, 3);

	__ENDMOD;
}
*/
