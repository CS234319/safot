# Standard ML

## datatypes

---

### concrete datatypes

* `datatype` creates new types
* these datatypes are **concrete** (not abstract)
* concrete datatypes can be inspected - constructed and taken apart
* ML's datatypes have two kinds of values: **atomic** and **composite**

---

### enumeration types

```sml
datatype single = only;

only;
(*val it = only : single*)
```

* `only` denotes the only value in the type `single`
* isomorphic to `unit`

---vert---

order doesn't matter

```sml
datatype bool = true | false;
(*datatype bool = false | true*)

true;
(*val it = true : bool*)
```

---vert---

allows pattern matching

```sml
datatype piece = king | queen | rook | bishop | knight | pawn;
(*datatype piece = bishop | king | knight | pawn | queen | rook*)

fun value king = Real.posInf (*infinity*)
  | value queen = 9.0
  | value rook = 5.0
  | value (bishop | knight) = 3.0
  | value pawn = 1.0;
(*val value = fn: piece -> real*)

value bishop;
(*val it = 3.0 : int*)
```

---

### branding

Newton's second law

```sml
fun a m f = f/m;
(*val a = fn : real -> real -> real*)

val (body, engine) = (0.0122, 50.0);

a engine body; (* oops *)
(*val it = 4098.36065574 : real*)
```

---vert---

type aliasing doesn't help

```sml
type mass = real and force = real and acceleration = real;

fun a (m:mass) (f:force) : acceleration = f/m;
(*val a = fn : mass -> force -> acceleration*)

a engine body; (* still oops *)
(*val it = 4098.36065574 : acceleration*)
```

---vert---

simulate branding using `datatype`

```sml
datatype mass = Kg of real;
datatype force = Newton of real;
datatype acceleration = m_s'2 of real;

fun a (Kg m) (Newton f) = m_s'2 (f / m);
(*val a = fn : mass -> force -> acceleration*)

val body = Kg 2.0;
val engine = Newton 50.0;

a body engine;
(*val it = m_s'2 25.0 : acceleration*)

a engine body;
(*Error: operator and operand don't agree [tycon mismatch]*)
```

---

### constructors

constructors are functions

```sml
datatype mass = Kg of real;
datatype force = Newton of real;
datatype acceleration = m_s'2 of real;

Kg;
(*val it = fn : real -> mass*)

Newton;
(*val it = fn : real -> force*)
```

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
(*val area = fn : shape -> real*)
```

---

### pattern matching

```sml
val line = Line 5.3;
(*val line = Line 5.3 : shape*)

val Line length = line;
(*val length = 5.3 : real*)

val Circle radius = line;
(*uncaught exception Bind [nonexhaustive binding failure]*)
```

---vert---

⚠️ constructors cannot be rebound by `val`

```sml
val point = point; (*OK*)
val point = 5.3
(*Error: pattern and expression in val dec don't agree
[tycon mismatch]*)
```

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

---

### polymorphic datatypes

```sml
datatype 'a list =
    nil
  | :: of 'a * ('a list);

"hello" :: "world" :: nil;
(*val it = "hello" :: "world" :: nil : string list*)
```

---vert---

```sml
datatype 'a option = NONE | SOME of 'a;

fun head []     = NONE
  | head (x::_) = SOME x;
(*val head = fn : 'a list -> 'a option*)

head [1, 2, 3];
(*val it = SOME 1 : int option*)

head (tl [1]);
(*val it = NONE : int option*)
```

---vert---

```sml
datatype ('a, 'b) union = type1 of 'a
  | type2 of 'b;

val five = type1 5;
(*val five = type1 5 : (int,'a) union*)

val hello = type2 "hello";
(*val hello = type2 "hello" : ('a,string) union*)

val five_or_hello = if true then five else hello;
(*val five_or_hello = type1 5 : (int,string) union*)

val int_char_list = [type1 5, type2 #"a"];
(*val five_or_hello = [type1 5, type2 #"a"] : (int,char) union list*)
```

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
(*val tree4 = Br (4,Br (2,Br #,Br #),Br (5,Br #,Br #)) : int tree*)

fun size Nil = 0
  | size (Br (v,t1,t2)) = 1 + size t1 + size t2;
(*val size = fn : 'a tree -> int*)
```

---

### binary search trees

* implement an associative array using trees
* the keys are `int`s
* values may be anything
* assumption: the tree is sorted

---vert---

```sml
val cmp = Int.compare;

fun get (Br ((node_k, v), left, right)) k = 
  case cmp (node_k, k) of
    EQUAL   => v
  | GREATER => get right k
  | LESS    => get left k
;
(*stdIn:22.28-22.164 Warning: match nonexhaustive ...*)
(*val get = fn : (int * 'a) tree -> int -> 'a*)
```

---vert---

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
(*val insert = fn : (int * 'a) tree -> int * 'a -> (int * 'a) tree*)
```
