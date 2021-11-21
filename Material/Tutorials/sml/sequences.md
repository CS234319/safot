# Standard ML

## sequences

---

### lazy lists

* elements are not evaluated until their values are required
* **may** be infinite
* example: a sequence of all even integers `$0, 2, -2, 4, \ldots$`

<!--vert-->

### lazy lists in ML

```sml
datatype 'a seq = Nil
    | Cons of 'a * (unit -> 'a seq);

fun head (Cons (x, _)) = x;

fun tail (Cons (_, xf)) = xf();
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

ML evaluates `E` in `Cons(x,E)`, so to obtain laziness we must write `Cons(x, fn()=>E)`

---

### examples of sequences

```sml
fun from k = Cons (k, fn() => from (k+1));

from 1;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

```sml
tail it;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

```sml
fun squares Nil = Nil
  | squares (Cons (x, xf)) =
        Cons (x*x, fn() => squares (xf()));
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

```sml
squares (from 1);
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

```sml
head (tail (tail (tail (tail it))));
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

---

### elementary sequence processing

<!--vert-->

#### `addq`

implement `addq` that takes two integer sequences and adds them element-wise

```sml
...
(*val addq = fn : int seq * int seq -> int seq*)
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

```sml
fun addq (Cons (x, xf), Cons (y, yf)) =
        Cons (x+y, fn() => addq (xf(), yf()))
  | addq _ = Nil;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

#### `appendq`

implement `appendq` that appends two sequences

```sml
...
(*val appendq = fn : 'a seq * 'a seq -> 'a seq*)
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

```sml
fun appendq (Nil, yq) = yq
  | appendq (Cons(x, xf), yq) =
        Cons (x, fn() => appendq (xf(), yq));
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

what would `appendq(xq,yq)` be if `xq` is infinite?

<!--vert-->

#### `mapq`

implement `mapq` that applies a function on the elements of a sequence

```sml
...
(*val mapq = fn : ('a -> 'b) -> 'a seq -> 'b seq*)
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

```sml
fun mapq f Nil           = Nil
  | mapq f (Cons (x,xf)) =
        Cons (f(x), fn()=>mapq f (xf()));
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

#### `filterq`

implement `filterq` that filters a sequence based on a predicate

```sml
...
(*val filterq = fn : ('a -> bool) -> 'a seq -> 'a seq*)
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

```sml
fun filterq pred Nil = Nil
  | filterq pred (Cons (x,xf)) =
        if pred x
        then Cons (x, fn()=>filterq pred (xf()))
        else filterq pred (xf());
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

#### `interleaveq`

implement `interleaveq` that interleaves two sequences

```sml
...
(*val interleaveq = fn : 'a seq * 'a seq -> 'a seq*)
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

```sml
fun interleaveq (Nil, yq)       = yq
  | interleaveq (Cons(x,xf),yq) =
        Cons (x, fn()=>interleaveq (yq, xf()));
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

```sml
...
(*val dropq = fn: 'a seq -> int -> 'a seq*)
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

```sml
fun dropq _ 0 = Nil
  | dropq Nil _ = Nil
  | dropq (Cons(x, xf)) n = dropq (xf()) (n - 1);
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

```sml
...
(*val seqToList = fn: 'a seq -> 'a list*)
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

```sml
fun seqToList Nil = []
  | seqToList (Cons(x, xf)) = x::(seqToList (xf()));
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

```sml
...
(*val listToSeq = fn: 'a list -> 'a seq*)
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

```sml
fun listToSeq [] = Nil
  | listToSeq (x::xs) = Cons (x, fn () => listToSeq xs);
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

![q1](../material/Tutorials/imgs/q1.png)

<!--vert-->

```sml
...
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

![q2](../material/Tutorials/imgs/q2.png)

<!--vert-->

```sml
...
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->
