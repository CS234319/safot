use "w1.sml";
use "utils.sml";

open W1;

fun parse_btree s =
    let
        fun aux ("_"::xs)= (empty, xs)
            | aux (x::xs) =
                let
                    val (a, xs) = aux xs
                    val (b, xs) = aux xs
                in
                    (btree(x, a, b), xs)
                end
        val (tr, []) = aux (String.fields (fn c => c = #"-") s)
    in
        tr
    end;

val t = parse_btree "a-b-_-_-c-d-_-_-e-_-_";

val t' = parse_btree "aa-bb-_-_-cc-dd-_-_-ee-_-_";

assert (map (fn x => x ^ x) t = t');

assert (flatten t = ["a", "b", "c", "d", "e"]);
