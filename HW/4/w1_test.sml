use "w1.sml";
use "utils.sml";

open W1;

val d = insert empty 2 #"b";
val d = insert d 1 #"a";
val d = insert d 3 #"c";

assert ((noexcept (fn () => find d 2)) = #"b");

except (fn () => find d 4);

except (fn () => remove empty "s");
