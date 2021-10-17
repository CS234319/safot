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
<!-- .element: data-thebe-executable-sml -->

ML evaluates `E` in `Cons(x,E)`, so to obtain laziness we must write `Cons(x, fn()=>E)`

---

### examples of sequences

```sml
fun from k = Cons (k, fn() => from (k+1));

from 1;
```
<!-- .element: data-thebe-executable-sml -->

```
tail it;
```
<!-- .element: data-thebe-executable-sml -->

<!--vert-->

```sml
fun squares Nil = Nil
  | squares (Cons (x, xf)) =
        Cons (x*x, fn() => squares (xf()));
```
<!-- .element: data-thebe-executable-sml -->

```sml
squares (from 1);
```
<!-- .element: data-thebe-executable-sml -->

```sml
head (tail (tail (tail (tail it))));
```
<!-- .element: data-thebe-executable-sml -->

---

### elementary sequence processing

<!--vert-->

#### `addq`

implement `addq` that takes two integer sequences and adds them element-wise

```sml
...
(*val addq = fn : int seq * int seq -> int seq*)
```
<!-- .element: data-thebe-executable-sml -->

<!--vert-->

```sml
fun addq (Cons (x, xf), Cons (y, yf)) =
        Cons (x+y, fn() => addq (xf(), yf()))
  | addq _ = Nil;
```
<!-- .element: data-thebe-executable-sml -->

<!--vert-->

#### `appendq`

implement `appendq` that appends two sequences

```sml
...
(*val appendq = fn : 'a seq * 'a seq -> 'a seq*)
```
<!-- .element: data-thebe-executable-sml -->

<!--vert-->

```sml
fun appendq (Nil, yq) = yq
  | appendq (Cons(x, xf), yq) =
        Cons (x, fn() => appendq (xf(), yq));
```
<!-- .element: data-thebe-executable-sml -->

what would `appendq(xq,yq)` be if `xq` is infinite?

<!--vert-->

#### `mapq`

implement `mapq` that applies a function on the elements of a sequence

```sml
...
(*val mapq = fn : ('a -> 'b) -> 'a seq -> 'b seq*)
```
<!-- .element: data-thebe-executable-sml -->

<!--vert-->

```sml
fun mapq f Nil           = Nil
  | mapq f (Cons (x,xf)) =
        Cons (f(x), fn()=>mapq f (xf()));
```
<!-- .element: data-thebe-executable-sml -->

<!--vert-->

#### `filterq`

implement `filterq` that filters a sequence based on a predicate

```sml
...
(*val filterq = fn : ('a -> bool) -> 'a seq -> 'a seq*)
```
<!-- .element: data-thebe-executable-sml -->

<!--vert-->

```sml
fun filterq pred Nil = Nil
  | filterq pred (Cons (x,xf)) =
        if pred x
        then Cons (x, fn()=>filterq pred (xf()))
        else filterq pred (xf());
```
<!-- .element: data-thebe-executable-sml -->

<!--vert-->

#### `interleaveq`

implement `interleaveq` that interleaves two sequences

```sml
...
(*val interleaveq = fn : 'a seq * 'a seq -> 'a seq*)
```
<!-- .element: data-thebe-executable-sml -->

<!--vert-->

```sml
fun interleaving (Nil, yq)       = yq
  | interleaving (Cons(x,xf),yq) =
        Cons (x, fn()=>interleaving (yq, xf()));
```
<!-- .element: data-thebe-executable-sml -->
