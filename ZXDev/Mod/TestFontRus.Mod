(*$MAIN*) MODULE TestFontRus; (*$866*)
IMPORT b := Basic, GrFonts, io := Console;

BEGIN
  b.Init; io.Clear(io.Black); io.SetColors(io.YellowOnGreen);
  b.FONT(GrFonts.MsDosCgaRus8x8);
  io.WriteStr("旼컴컴컴컴컴컴컴컴컴컴커"); io.WriteLn;
  io.WriteStr("남굅뤲Ðβ, 몺´エ�!갚껙"); io.WriteLn;
  io.WriteStr("읕컴컴컴컴컴컴컴컴컴컴켸"); io.WriteLn;
  io.SetColors(io.CyanOnBlue);
  io.At(2, 4); io.WriteStr("�袴袴袴袴袴袴袴袴袴袴袴�");
  io.At(2, 5); io.WriteStr("�   뤲Ðβ, 몺´エ�!   �");
  io.At(2, 6); io.WriteStr("훤袴袴袴袴袴袴袴袴袴袴暠");
  io.SetColors(io.RedOnYellow);
  io.At(5, 8); io.WriteStr("靈컴컴컴컴컴컴컴컴컴컴캠");
  io.At(5, 9); io.WriteStr("�   뤲Ðβ, 몺´エ�!   �");
  io.At(5,10); io.WriteStr("聃컴컴컴컴컴컴컴컴컴컴캭");
  io.SetColors(io.GreenOnBlack);
  io.At(8,12); io.WriteStr("郞袴袴袴袴袴袴袴袴袴袴拷");
  io.At(8,13); io.WriteStr("�   뤲Ðβ, 몺´エ�!   �");
  io.At(8,14); io.WriteStr("突袴袴袴袴袴袴袴袴袴袴槁");
  b.PAUSE(0);
  b.Quit
END TestFontRus.
