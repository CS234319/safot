use "w1.sml";

exception AssertError;

fun noexcept f = f () handle _ => raise AssertError;

fun except f = (f (); raise AssertError) handle ItemNotPresent => ();

fun assert b = if b then () else raise AssertError;

val d = insert dictionary_empty 2 #"b";
val d = insert d 1 #"a";
val d = insert d 3 #"c";

assert ((noexcept (fn () => find d 2)) = #"b");

except (fn () => find d 4);

except (fn () => remove dictionary_empty "s");
