@IF EXIST ..\C\%1.c GOTO clib

:olib
..\..\Bin\tcc64\tcc -c %1.c -I "." -I ..\C
@IF errorlevel 1 GOTO noinit
@GOTO exit

:noinit
..\..\..\Bin\smartlib %1.c -noinit -nocut
..\..\Bin\tcc64\tcc -c %1.c -I "." -I ..\C
@GOTO exit

:clib
..\..\Bin\tcc64\tcc -c ..\C\%1.c -I "." -I ..\C

:exit
@IF errorlevel 1 PAUSE
