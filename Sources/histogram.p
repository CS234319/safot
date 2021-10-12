Program Reverse;
TYPE
  lower = 'a'..'z';
VAR
  c: char;
  Counts: Array[lower] of Integer;

Function ToLower(c:Char): Char;
Begin
  If (c >= 'A') and (c <= 'Z') then 
    ToLower := chr(ord(c) - ord('A') + ord('a'))
  else
    ToLower := c 
End;

Function ToUpper(c:Char): Char;
Begin
  If (c >= 'a') and (c <= 'z') then 
    ToUpper := chr(ord(c) - ord('a') + ord('A'))
  else
    ToUpper := c 
End;

Begin
    For c := 'a' to 'z' do 
      Counts[c] := 0;
    While not EOF do
      Begin
        Read(c);
        c := ToLower(c);
        If (c >= 'a') and (c <= 'z') then 
          Counts[c] := Counts[c] + 1
      end;

    For c := 'a' to 'z' do 
      If Counts[c] <> 0 then
         WriteLn(c,'/', ToUpper(c), '   ',Counts[c]);  
end.
