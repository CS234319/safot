use "w1.sml";

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

fun eval x = SOME (W1.eval (A_List.make ()) x) handle W1.Error => NONE;

val test_1 = eval ($[CONS, `A, `B]) = SOME (!"A" + !"B");
val test_2 = eval ($[CONS, `A, $[ATOM, `B]]) = SOME (!"A" + !"T");
