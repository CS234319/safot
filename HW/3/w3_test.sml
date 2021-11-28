use "w4.sml";
use "utils.sml";

fun counter () = let
  val exec_count = ref 0;
  fun aux n = Cons (n, fn () => (
    exec_count := 1 + !exec_count;
    print ("exec: " ^ Int.toString (!exec_count) ^ "\n");
    aux (n + 1)
  ));
in
  W4.new (aux 0)
end;
