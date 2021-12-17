use "w2.sml";

open AST;

val ~ = Atom;
val $ = List;
fun ` x = List [~"QUOTE", x]
fun (x + y) = S_Expression.Cons (x, y);
val ! = S_Expression.Atom;

val QUOTE = ~"QUOTE";
val CONS = ~"CONS";
val ATOM = ~"ATOM";
val EQ = ~"EQ";
val NIL = ~"NIL";
val T = ~"T";
val A = ~"A";
val B = ~"B";

datatype result = Ok of S_Expression.t | Error of W2.error;

fun eval x = Ok (W2.eval (A_List.make ()) x) handle W2.Error error => Error error;

val test_1 = eval ($[CONS, `A, `B]) = Ok(!"A" + !"B");
val test_2 = eval ($[CONS, `A, $[ATOM, `B]]) = Ok(!"A" + !"T");
