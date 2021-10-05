# Prolog

## CLP(FD)

---

### intro

* `CLP(FD)` is a library
* CLP = **C**onstraint **L**ogic **P**rogramming
* FD = **F**inite **D**omains, namely integers
* use it to solve a set of constraints over integers

---vert---

write in the interpreter:

```prolog
use_module(library(clpfd)).
```

or write the following at the top of a file:

```prolog
:- use_module(library(clpfd)).
```

---

### arithmetic constraints

---vert---

#### comparison operators

the comparison operators are almost the same but prefixed by `#`

```prolog
X #> Y.
X #< Y.
X #>= Y.
X #=< Y.
X #= Y.
X #\= Y.
```

---vert---

`X` and `Y` can be any arithmetic expression:

* an integer value
* a variable
* `-Expr`
* `Expr1 @ Expr2` where `@` is replaced by `+` `*` `-` `^` `//` `div` `mod` `rem`
* `abs(Expr)`
* `min(Expr1,Expr2)`
* `max(Expr1,Expr2)`

---vert---

how are these different from the regular comparison operators?

```prolog
X + 2 =:= Y + X.
% ERROR: Arguments are not sufficiently instantiated

X + 2 #= Y + X.
% Y = 2, X in inf..sup.
```

the `#`-operators don't require that any of the variables are instantiated

---

### domains

`CLP(FD)` can give a domain as a solution

```prolog
0 #< X, X #< 5.
% X in 1..4.
```

---vert---

in a domain `sup` is for supremum and `inf` is for infimum

```prolog
0 #< X.
% X in 1..sup.

X #< 5
% X in inf..4.
```

---vert---

we can use the `in` operator in out code

```prolog
X in 1..5.
% X in 1..5.
```

---vert---

`\/` is used for domains union

```prolog
X in 1..5, X #\= 2.
% X in 1\/3..5.

X in 1\/2\/3.
% X in 1..3.
```

---vert---

#### labeling

`indomain(X)` is used to successively bind `X` to all integers of its domain

```prolog
X in 1..3, indomain(X).
% X = 1 ; X = 2 ; X = 3.
```

---vert---

`indomain` must always terminate

```prolog
X in 0..sup, indomain(X).
% ERROR: Arguments are not sufficiently instantiated
```
