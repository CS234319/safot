# Ocaml

## imperative programming

---

### mutable fields

ocaml records are immutable by default but you can declare record fields as mutable

```ocaml
type point = { mutable x_coord: float; mutable y_coord: float }

let p = { x_coord=0.; y_coord=0.};;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

`<-` is used for setting a mutable field

```ocaml
let () = p.x_coord <- 5.;;
p;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### ref cells

the builtin `ref` type represents a single mutable cell

```ocaml
type 'a ref = { mutable contents: 'a };;
```

<!--vert-->

use `ref` to create a single mutable cell

```ocaml
let x = ref 4;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

implementation:

```ocaml
let ref x = { contents = x };;
```

<!--vert-->

use `:=` to replace the cell's contents

```ocaml
x := 15;;
x;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

implementation:

```ocaml
let ( := ) r v = r.contents <- v;;
```

<!--vert-->

use `!` to get the the cell's contents

```ocaml
!x;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

implementation:

```ocaml
let ( ! ) r = r.contents;;
```

---

### sequencing with `;`

`;` is used to sequence expressions with side-effects

```ocaml
let swap x y =
    x := !x lxor !y ;
    y := !y lxor !x ;
    x := !y lxor !x;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

an expression created by `;` evaluates to the value of the last expression

```ocaml
let x = ref 42;;
x := !x * !x; !x
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

all non-final expressions should be of type `unit` otherwise you'd get a warning

```ocaml
123; 456;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

---

### loops

<!--vert-->

#### while loops

```ocaml
while condition do
    statement
done
```

<!--vert-->

```ocaml
let counter = ref 0 in

while Random.int 1000 > 10 do
    counter := !counter + 1
done;

!counter;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->

<!--vert-->

#### for loops

```ocaml
for variable = start_v to end_v do
    statement
done
  
for variable = start_v downto end_v do
    statement
done
```

<!--vert-->

```ocaml
let fib n = let a, b = ref 0, ref 1 in
    for i = 2 to n do
        let b' = !b in
        b := !a + !b;
        a := b'
    done;
    !b
;;

fib 7;;
```
<!-- .element: data-thebe-executable-ocaml data-language="text/x-ocaml" -->
