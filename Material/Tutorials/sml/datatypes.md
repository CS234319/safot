# Standard ML

## datatypes 

- Created: using the `datatype` keyword
- Realize: the theoretical type constructor of disjoing union
- Generalize
  - the `null` pointer of C, Pascal, Java
  - enumerated types, as found in Pascal, C, and Java, e.g., `enum  { };
  - union types, as found in Pascal variant records and union in C
  - branding, as done by Pascal's TYPE, but difficult to achieve in Java and C.

- Essential: you cannot do lists, trees, etc., without it.
  - Reason: lists must support the distinction between an empty and an non-empty lists, and function next is not type-safe

---

### concrete datatypes
dattatype are a SML type constructor:
  - Given: a list of types and list of tags
  - Produce: a new type out of these
`datatype` creates new types
* these datatypes are **concrete** (not abstract)
* concrete datatypes can be inspected - constructed and taken apart
* ML's datatypes have two kinds of values: **atomic** and **composite**

---

### enumeration types

```sml
datatype single = only;

only;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

`only` denotes the only value of type `single` (isomorphic to `unit`)

<!--vert-->

order doesn't matter

```sml
datatype bool = true | false;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

allows pattern matching

```sml
datatype piece = king | queen | rook | bishop | knight | pawn;

fun value king = Real.posInf (*infinity*)
  | value queen = 9.0
  | value rook = 5.0
  | value (bishop | knight) = 3.0
  | value pawn = 1.0;

value bishop;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

---

### branding

Newton's second law

```sml
fun a m f = f/m;

val (body, engine) = (0.0122, 50.0);

a engine body; (* oops *)
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

type aliasing doesn't help

```sml
type mass = real and force = real and acceleration = real;

fun a (m:mass) (f:force) : acceleration = f/m;

a engine body; (* still oops *)
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

simulate branding using `datatype`

```sml
datatype mass = Kg of real;
datatype force = Newton of real;
datatype acceleration = m_s'2 of real;

fun a (Kg m) (Newton f) = m_s'2 (f / m);

val body = Kg 2.0;
val engine = Newton 50.0;

a body engine; (*OK*)

a engine body; (*Error*)
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

---

### constructors

constructors are functions

```sml
datatype mass = Kg of real;
datatype force = Newton of real;
datatype acceleration = m_s'2 of real;

Kg;

Newton;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

---

### variant types

```sml
datatype shape =
    point
  | Line of real
  | Circle of real
  | Rectangle of real*real;

fun area (point | Line _) = 0.0
  | area (Circle r) = Math.pi*r*r
  | area (Rectangle (w, h)) = w * h;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

---

### pattern matching

```sml
val line = Line 5.3;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

```sml
val Line length = line;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

```sml
val Circle radius = line;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

⚠️ constructors cannot be rebound by `val`

```sml
val point = point; (*OK*)
val point = 5.3
(*Error: pattern and expression in val dec do not agree
[tycon mismatch]*)
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

---

### recursive datatypes

🛈 every list is either `nil` or `head::tail`

```sml
datatype intlist =
    nil
  | :: of int * intlist;

fun length nil     = 0
  | length (x::xs) = 1 + length xs;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

---

### polymorphic datatypes

```sml
datatype 'a list =
    nil
  | :: of 'a * ('a list);
```

```sml
"hello" :: "world" :: nil;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

```sml
datatype 'a option = NONE | SOME of 'a;

fun head []     = NONE
  | head (x::_) = SOME x;

head [1, 2, 3];

head (tl [1]);
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

```sml
datatype ('a, 'b) union = type1 of 'a
  | type2 of 'b;

val five = type1 5;

val hello = type2 "hello";

val five_or_hello = if true then five else hello;

val int_char_list = [type1 5, type2 #"a"];
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

---

### trees

```sml
datatype 'a tree =
    Nil
  | Br of 'a * ('a tree) * ('a tree);

fun Leaf x = Br (x, Nil, Nil);

val tree2 = Br (2, Leaf 1, Leaf 3);
val tree5 = Br (5, Leaf 6, Leaf 7);
val tree4 = Br (4, tree2, tree5);
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

```sml
fun size Nil = 0
  | size (Br (v,t1,t2)) = 1 + size t1 + size t2;

size tree4;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

---

### binary search trees

* implement an associative array using trees
* the keys are `int`s
* values may be anything
* assumption: the tree is sorted

<!--vert-->

```sml
val cmp = Int.compare;

fun get (Br ((node_k, v), left, right)) k = 
  case cmp (node_k, k) of
    EQUAL   => v
  | GREATER => get right k
  | LESS    => get left k
;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->

<!--vert-->

```sml
local
   fun compare (k1,_) (k2,_) = cmp (k1, k2)
in
    fun insert Nil item = Br (item, Nil, Nil)
      | insert (Br (node, left, right)) item = 
        case compare node item of 
          EQUAL   => Br (item, left, right)
        | GREATER => Br (node, left, insert right item)
        | LESS    => Br (node, insert left item, right)
end;
```
<!-- .element: data-thebe-executable-sml data-language="text/x-ocaml" -->
