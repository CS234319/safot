# Standard ML

## refs

---

### ref cells

use `ref` to create a single **mutable** cell

```sml
val x = ref 4;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

`ref` is a constructor and as such is also a function

```sml
ref;
(*val it = fn : 'a -> 'a ref*)
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

---

use `:=` to replace a cell's contents

```sml
val x = ref 0;
x := 15;
x;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

note that `:=` returns `()`

```sml
val := = fn : 'a ref * 'a -> unit
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

use `!` to get the the cell's contents

```sml
val x = ref 8;
!x;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

```sml
val ! = fn : 'a ref -> 'a
```

---

### sequencing with `;`

`;` is used to sequence expressions (with side-effects)

```sml
fun swap x y =
    (x := !x + !y ; y := !x - !y ; x := !x - !y);
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

an expression created by `;` evaluates to the value of the last expression

```sml
val x = ref 42;
(x := !x * !x; !x);
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

---

### memoization

```sml
type (''a, 'b) memoizer = {max_size: int, memory: (''a * 'b) list ref};

fun memoizer_put (memo: (''a, 'b) memoizer) x y = 
    #memory(memo) :=
        (if length (!(#memory memo)) < #max_size memo
        then !(#memory memo)
        else tl (!(#memory memo)))
        @ [(x, y)];

fun memoize (memo: (''a, 'b) memoizer) f x =
    case (List.find (fn t => x = #1 t) (!(#memory memo))) of
      SOME (_, y) => y
    | NONE => (
        let val y = f x in
            memoizer_put memo x y;
            y 
        end
    );
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

```sml
local
    val memo = {max_size=10, memory=ref []}
in
fun fib 0 = 0
  | fib 1 = 1
  | fib n = let
        val aux = memoize memo fib
    in
        (aux (n - 1)) + (aux (n - 2))
    end
end;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

let's compare

```sml
fib 43;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

```sml
fun fib_exp 0 = 0
  | fib_exp 1 = 1
  | fib_exp n = (fib_exp (n-1)) + (fib_exp (n-2));
fib_exp 43;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->
