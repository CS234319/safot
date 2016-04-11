Program p;
  Function f: Character; 
    forward; (* Declaration of Function f *)
  Function g: Character; 
    Begin (* Definition of Function g *)
      g := f (* Using Function f in Function g *)
    end; 
  Function f: Character; (* Definition of Function f *)
    Begin
      f := g (* Using Function g in function f *)
    end;
Begin
  (* Body of program p *)
end.
