@CD ..\..
Bin\7z.exe u -tzip -ssc -x@XDev\Bin\ZXDev-.lst ZXDev @XDev\Bin\ZXDev+.lst
@IF errorlevel 1 PAUSE
