@REM Build the library XDev
@REM ======================

@IF EXIST ..\WinDev.a ..\DEL WinDev.a
@CALL ..\Bin\build-xdev.bat SYSTEM
@CALL ..\Bin\build-xdev.bat Platform
@CALL ..\Bin\build-xdev.bat Strings
@CALL ..\Bin\build-xdev.bat CmdLine
@CALL ..\Bin\build-xdev.bat Console
@CALL ..\Bin\build-xdev.bat Math
@CALL ..\Bin\build-xdev.bat Files