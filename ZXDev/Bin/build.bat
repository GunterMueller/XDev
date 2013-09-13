@SET CodeAddr=45056
@SET DataAddr=63488
@SET Bin=..\Bin
@SET Lib=..\Lib

%Bin%\sdcc %1.c -mz80 --code-loc %CodeAddr% --data-loc %DataAddr% --opt-code-size --disable-warning 85 -I "." -I %Lib% XDev.lib Graph.lib Basic.lib Laser.lib Mega.lib Best40.lib trdos.lib
@IF errorlevel 1 PAUSE

%Bin%\hex2bin %1.ihx
%Bin%\bin2data.exe -rem -org %CodeAddr% %1.bin ..\%1.tap %1
@START ..\%1.tap
