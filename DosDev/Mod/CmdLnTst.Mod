MODULE CmdLnTst;

IMPORT CmdLine, IO := Console, Str := Strings;

VAR
  i, n: INTEGER; param: CmdLine.String;

BEGIN (*$MAIN*)
  IO.WriteInt(CmdLine.paramCount); IO.WriteLn;
  FOR n := 1 TO CmdLine.paramCount DO
    CmdLine.GetParam(n, param);
    IO.WriteInt(n); IO.WriteStr(":"); IO.WriteStrLn(param);
    FOR i := 0 TO SHORT(Str.Length(param)) - 1 DO
      IO.WriteInt(ORD(param[i])); IO.WriteStr(",");
    END;
    IO.WriteLn;
  END;

END CmdLnTst.
