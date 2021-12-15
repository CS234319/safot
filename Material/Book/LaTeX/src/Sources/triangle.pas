
Program h;
VAR a,b,c,p: real;
Begin
  readln(a,b,c);
  p := (a+b+c)/2;
  writeln(sqrt(p*(p-a)*(p-b)*(p-c)))
end.
