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
(*val head = fn : 'a seq -> 'a*)

fun tail (Cons (_, xf)) = xf();
(*val tail = fn : 'a seq -> 'a seq*)
```
<!-- .element: data-thebe-executable-sml -->

ML evaluates `E` in `Cons(x,E)`, so to obtain laziness we must write `Cons(x, fn()=>E)`

---

### examples of sequences

```sml
fun from k = Cons (k, fn() => from (k+1));
(*val from = fn : int -> int seq*)

from 1;
(*val it = Cons (1,fn) : int seq*)

tail it;
(*val it = Cons (2,fn) : int seq*)
```
<!-- .element: data-thebe-executable-sml -->

<!--vert-->

```sml
fun squares Nil = Nil
  | squares (Cons (x, xf)) =
        Cons (x*x, fn() => squares (xf()));
(*val squares = fn : int seq -> int seq*)

squares (from 1);
(*val it = Cons (1,fn) : int seq*)

head (tail (tail (tail (tail it))));
(*val it = 25 : int*)
```
<!-- .element: data-thebe-executable-sml -->

---

### elementary sequence processing

adding two sequences

```sml
fun addq (Cons (x, xf), Cons (y, yf)) =
        Cons (x+y, fn() => addq (xf(), yf()))
  | addq _ = Nil;
(*val addq = fn : int seq * int seq -> int seq*)
```
<!-- .element: data-thebe-executable-sml -->

<!--vert-->

<!-- .slide: data-background-iframe="http://localhost:8888/notebooks/tut9-sequence-functions.ipynb" data-background-interactive -->

<!--vert-->

appending two sequences

```sml
fun appendq (Nil, yq) = yq
  | appendq (Cons(x, xf), yq) =
        Cons (x, fn() => appendq (xf(), yq));
(*val appendq = fn : 'a seq * 'a seq -> 'a seq*)
```
<!-- .element: data-thebe-executable-sml -->

what would `appendq(xq,yq)` be if `xq` is infinite?

<!--vert-->

interleaving two sequences

```sml
fun interleaving (Nil, yq)       = yq
  | interleaving (Cons(x,xf),yq) =
        Cons (x, fn()=>interleaving (yq, xf()));
(*val interleaving = fn : 'a seq * 'a seq -> 'a seq*)
```
<!-- .element: data-thebe-executable-sml -->

<!--vert-->

### `mapq`

```sml
fun mapq f Nil           = Nil
  | mapq f (Cons (x,xf)) =
        Cons (f(x), fn()=>mapq f (xf()));
(*val mapq = fn : ('a -> 'b) -> 'a seq -> 'b seq*)
```
<!-- .element: data-thebe-executable-sml -->

<!--vert-->

### `filterq`

```sml
fun filterq pred Nil = Nil
  | filterq pred (Cons (x,xf)) =
        if pred x
        then Cons (x, fn()=>filterq pred (xf()))
        else filterq pred (xf());
(*val filterq = fn : ('a -> bool) -> 'a seq -> 'a seq*)
```
<!-- .element: data-thebe-executable-sml -->

---

### example - prime numbers

![sieve gif](./imgs/tut9-sieve.gif)

<!--vert-->

<!-- .slide: data-background-iframe="http://localhost:8888/notebooks/tut9-primes.ipynb" data-background-interactive -->

---

### exam questions

<!--vert-->

<!-- .slide: data-background-iframe="http://localhost:8888/notebooks/tut9-exam-question-1.ipynb" data-background-interactive -->

<!--vert-->

<!-- .slide: data-background-iframe="http://localhost:8888/notebooks/tut9-exam-question-2.ipynb" data-background-interactive -->

<!--vert-->

<!-- .slide: data-background-iframe="http://localhost:8888/notebooks/tut9-exam-question-3.ipynb" data-background-interactive -->