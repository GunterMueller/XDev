(* ������� ��������� ����� 1000 ��� � ������� ������� �������,
   � ������� ���������� ������� ��� ������ ������ �����.
   ���������: ��� ���������, 14 ���, ������������, �������.
*)

MODULE Kubik; (*$MAIN*)
IMPORT Console, Math;

CONST
	HowManyTimes = 1000;
VAR
	(* ������� 6 ���������� (�� ���������� ������ ������). *)
	one, two, three, four, five, six, n, number: INTEGER;
BEGIN
	Math.Randomize;
	(* �������� ���� �������� ������ ������. *)
	one := 0; two := 0; three := 0; four := 0; five := 0; six := 0;
	(* ��������� 1000 ��� ������������ ������. *)
	FOR n := 1 TO HowManyTimes DO
		(* � ��������� ������� ��� ������ ������ �����. *)
		number := Math.RndRange(1, 6);
		IF number = 1 THEN one := one + 1 END;
		IF number = 2 THEN two := two + 1 END;
		IF number = 3 THEN three := three + 1 END;
		IF number = 4 THEN four := four + 1 END;
		IF number = 5 THEN five := five + 1 END;
		IF number = 6 THEN six := six + 1 END;
	END;

	(* ���������� ������� �������. *)
	Console.SetColors(Console.CyanOnBlack);
	Console.WriteStr("+---+------------+"); Console.WriteLn;
	Console.WriteStr("| "); Console.SetColors(Console.RedOnBlack); Console.WriteInt(1);
		Console.SetColors(Console.CyanOnBlack); Console.WriteStr(" |            |"); Console.WriteLn;
	Console.WriteStr("+---+------------+"); Console.WriteLn;
	Console.WriteStr("| "); Console.SetColors(Console.YellowOnBlack); Console.WriteInt(2);
		Console.SetColors(Console.CyanOnBlack); Console.WriteStr(" |            |"); Console.WriteLn;
	Console.WriteStr("+---+------------+"); Console.WriteLn;
	Console.WriteStr("| "); Console.SetColors(Console.GreenOnBlack); Console.WriteInt(3);
		Console.SetColors(Console.CyanOnBlack); Console.WriteStr(" |            |"); Console.WriteLn;
	Console.WriteStr("+---+------------+"); Console.WriteLn;
	Console.WriteStr("| "); Console.SetColors(Console.MagentaOnBlack); Console.WriteInt(4);
		Console.SetColors(Console.CyanOnBlack); Console.WriteStr(" |            |"); Console.WriteLn;
	Console.WriteStr("+---+------------+"); Console.WriteLn;
	Console.WriteStr("| "); Console.SetColors(Console.BlueOnBlack); Console.WriteInt(5);
		Console.SetColors(Console.CyanOnBlack); Console.WriteStr(" |            |"); Console.WriteLn;
	Console.WriteStr("+---+------------+"); Console.WriteLn;
	Console.WriteStr("| "); Console.SetColors(Console.WhiteOnBlack); Console.WriteInt(6);
		Console.SetColors(Console.CyanOnBlack); Console.WriteStr(" |            |"); Console.WriteLn;
	Console.WriteStr("+---+------------+");
	(* � ������� ����������. *)
	Console.At(10, 1); Console.SetColors(Console.RedOnBlack); Console.WriteInt(one);
	Console.At(10, 3); Console.SetColors(Console.YellowOnBlack); Console.WriteInt(two);
	Console.At(10, 5); Console.SetColors(Console.GreenOnBlack); Console.WriteInt(three);
	Console.At(10, 7); Console.SetColors(Console.MagentaOnBlack); Console.WriteInt(four);
	Console.At(10, 9); Console.SetColors(Console.BlueOnBlack); Console.WriteInt(five);
	Console.At(10, 11); Console.SetColors(Console.WhiteOnBlack); Console.WriteInt(six);
  Console.WriteLn;
  Console.WriteLn;
  Console.WriteLn;
END Kubik.
