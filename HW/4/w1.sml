use "w1_def.sml";

structure W1: S1 = struct
  exception Error
  val NIL = S_Expression.Atom "NIL"
  val T = S_Expression.Atom "T"
  val is_primitive = fn "QUOTE" => true | "ATOM" => true | "EQ" => true | "EVAL" => true | "CAR" => true | "CDR" => true | "CONS" => true | _ => false
  fun eval a_list = fn
        AST.Atom a => (
          if is_primitive a
            then S_Expression.Atom a
            else A_List.find a_list a
        )
      | (*TODO*)
end;
