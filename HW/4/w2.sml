use "w2_def.sml";

structure W2: S2 = struct
  datatype error = Undefined | NotAPair | WrongNumberOfArguments | NotAFunction
  exception Error of error
  val NIL = S_Expression.Atom "NIL"
  val T = S_Expression.Atom "T"
  val is_primitive = fn "QUOTE" => true | "ATOM" => true | "EQ" => true | "EVAL" => true | "CAR" => true | "CDR" => true | "CONS" => true | _ => false
  fun eval a_list = fn
        AST.Atom a => (if is_primitive a then S_Expression.Atom a else case A_List.find a_list a of
            SOME v => v
          | NONE => raise (Error Undefined)
        )
      | (*TODO*)
end;
