# types

## type constructors

---

### Types

> A type is defined as a set of values.

We will want to expand our possibilities by creating new types with existing ones. Which is why we will learn on Type Constructors.

---

### what are type constructors?

> type constructors are operators that take a type and return a new type

---

### power set

```pascal
type Alphabets = set of 'A' .. 'Z';
```

---

### product

* notation: $T_1\times \cdots \times T_n$
* composition: $\langle\cdot,\ldots,\cdot\rangle$
* decomposition: $i(\cdot)$

<!--vert-->

in SML:

```sml
type product = int * real * string;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

#### properties of cartesian products

* commutativity - never!
* associativity - depending on the PL semantics.
* for example $ R\times S \times T$ and $R\times (S \times T)$ and $(R\times S) \times T$
  * structural ✅
  * nominal ❌

---

### integral exponentiation

* integral exponentiation makes homogenous tuples
* notation: $T^n = T \times \overset{\text{n times}}{\cdots} \times T$

---

### unit type

a type with only one value

(similar to `void` but not really)

<!--vert-->

in SML:

* is either
    * empty record `{}`
    * empty tuple `()`
* Predefined name: `Unit`
* Only value: `()`

---

### branding

* notation: $l(T)$
* composition $l(\cdot)$
* decomposition: $l(\cdot)$

<!--vert-->

in SML:

```sml
datatype X = X of int;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

note that `type` creates an alias, it doesn't brand

```sml
type X = int;
fun (x: X): int = x; (*OK*)
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

---

### records

* notation: $\{ l_1: T_1,\ldots,l_n: T_n \}$
* composition: $\{ l_1=\cdot,\ldots,l_n=\cdot \}$
* decomposition: $l_i(\cdot)$

<!--vert-->

in SML:

```sml
type record = {x: int, y: real};
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

---

### disjoint union

* notation: $l_1(T_1)\cup\cdots\cup l_n(T_n)$
* composition: $l_i(\cdot)$

<!--vert-->

in SML:

```sml
datatype ('a, 'b) union = A of 'a | B of b;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

an enum can be thought of as a disjoint union of branded unit types

$$(l_1, \ldots, l_n) = l_1(Unit) + \ldots + l_n(Unit)$$

---

### The empty/null/bottom type

usually by disjoint sum of a list of zero types

<!--vert-->

#### Not in SML!

* a datatype can never be empty
* best approximation for a function that never returns:
  * Return type is `Unit`
  * Function always throws an exception

---

### the Any/all/top type

a type that contains **all** values in the language

---

### mapping and partial mapping

* notation: $S\rightarrow T$

<!--vert-->

in SML:

```sml
type ('a, 'b) F = 'a -> 'b;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

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
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

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
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->
