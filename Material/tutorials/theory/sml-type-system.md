# standard ML

## type system

---

### records

* notation: $\{ l_1: T_1,\ldots,l_n: T_n \}$
* composition: $\{ l_1=\cdot,\ldots,l_n=\cdot \}$
* decomposition: $\#l_i(\cdot)$

<!--vert-->

in SML:

```sml
type record = {x: int, y: real};
```
<!-- .element: data-thebe-executable-sml -->

---

### product

* notation: $T_1\times \cdots \times T_n$
* composition: $\langle\cdot,\ldots,\cdot\rangle$
* decomposition: $\#_i(\cdot)$

<!--vert-->

in SML:

```sml
type product = int * real * string;
```
<!-- .element: data-thebe-executable-sml -->

---

### disjoint union

* notation: $l_1(T_1)\cup\cdots\cup l_n(T_n)$
* composition: $l_i(\cdot)$
* decomposition: $$

<!--vert-->

in SML:

```sml
datatype ('a, 'b) union = A of 'a | B of b;
```
<!-- .element: data-thebe-executable-sml -->

---

### branding

* notation: $l(T)$
* composition $l(\cdot)$
* decomposition: $\#l(\cdot)$

<!--vert-->

in SML:

```sml
datatype X = X of int;
```
<!-- .element: data-thebe-executable-sml -->

<!--vert-->

note that `type` creates an alias, it doesn't brand

```sml
type X = int;
fun (x: X): int = x; (*OK*)
```
<!-- .element: data-thebe-executable-sml -->

---

### mapping

* notation: $S\rightarrow T$

<!--vert-->

in SML:

```sml
type ('a, 'b) F = 'a -> 'b;
```
<!-- .element: data-thebe-executable-sml -->

---

### simple recursive

* notation: $\tau = E(\tau,T_1,\ldots,T_n)$

<!--vert-->

in SML:

```sml
datatype 'a list =
    nil
  | :: of 'a * 'a list;
```
<!-- .element: data-thebe-executable-sml -->

---

### multiple recursive

* notation:

    $$\tau_1 = E(T_1,\ldots,T_m, \tau_1,\ldots,\tau_n)$$
    $$\tau_n = E(T_1,\ldots,T_m, \tau_1,\ldots,\tau_n)$$

<!--vert-->

in SML:

```sml
datatype 'a foo = Foo of ('a * 'a bar)
and 'a bar = Bar of 'a foo | None;

Foo (1, Bar (Foo (2, None)));
```
<!-- .element: data-thebe-executable-sml -->
