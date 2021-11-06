# Prolog

## introduction

---

### basic constructs

<!--vert-->

the basic constructs of prolog are terms and statements

<!--vert-->

#### terms - atoms

the simplest term is an **atom**, the following are atoms:

```prolog
john
$<@
'an atom'
```

<!--vert-->

an **atom** is

* a string of letters, digits, and an underscore starting with a **lower-case letter**: `anna` `x_25` `nil`
* a string of special characters (`+ - * / < > = : . & _ ~`): `$<@` `<---->` `.:.`
* a string of characters enclosed in single quotes: `'Tom'` `'2A$'`

<!--vert-->

#### terms - numbers

* integers: `123` `-42`
* real numbers: `3.14` `-0.573` `2.4e3`

<!--vert-->

#### terms - variables

a **variable** is a string of letters, digits and an underscore starting with an upper-case letter or an underscore

```prolog
X_25
_result
```

<!--vert-->

#### compound terms

a **compound term** comprises a functor and arguments

```prolog
course(236319, pl)
```

a functor `f` of arity `n` is denoted `f/n`

<!--vert-->

#### terminology

* a term is **ground** (קונקרטי) if it contains no variables
* a **goal** is an atom or a compound term
* a **predicate** (פרדיקט) is a functor for which a list of clauses is defined
* a **clause** (פסוקית) is a fact or a rule

<!--vert-->

#### facts

a **fact** (עובדה) is a kind of statement

```prolog
eats(bear, honey).
```

this fact states that the **predicate** `eats` holds for the atoms `bear` and `honey`

<!--vert-->

facts can have any arity

```prolog
summer.
sad(john).
plus(2, 3, 5).
```

<!--vert-->

a finite set of facts constitutes a program

```prolog
mammal(rat).
mammal(bear).
fish(salmon).
eats(bear, honey).
eats(bear, salmon).
eats(rat, salmon).
eats(salmon, warm).
```

<!--vert-->

facts can contain variables

```prolog
likes(X, course236319).
```

variables are universally quantified

$$\forall X,likes(X, course236319)$$

<!--vert-->

#### queries

a **query** (שאילתה) is a conjunction of goals

```prolog
eats(X, salmon), eats(X, honey).
% X = bear.
```

variables are existentially quantified

$$\exists X,eats(X, salmon) \land eats(X, honey)$$

<!--vert-->

#### rules

a **rule** (חוק, כלל) is a statement which enables us to define new relationships in terms of existing ones

```prolog
predicate(term1, ..., termN) :- goal1, ..., goalN.
```

<!--vert-->

`Y` is a survival dependency of `X` if:

* `X` eats `Y`
* or `X` eats `Z` and `Y` is a survival dependency of `Z`

```prolog
survival_dependency(X, Y) :- eats(X, Y).
survival_dependency(X, Y) :-
    eats(X, Z), survival_dependency(Z, Y).
```

---

### writing Prolog programs

* create a file named `prog.pl`
* write clauses in `prog.pl`
* enter the prolog interpreter
* type `consult(prog.pl)`
* query the interpreter

<!--vert-->

#### dynamic clauses

you can add clauses dynamically

```prolog
assertz(eats(bear, tuna)).
assertz((
  mother(Child, Mother) :-
    parent(Child, Mother),
    female(Mother)
)).
```

`asserta` asserts the clause as first clause of the predicate while `assertz` asserts it as last clause

<!--vert-->

dynamically remove a clause using `retract/1`

```prolog
assertz(q(a)).
assertz((p(X) :- q(X))).
assertz(p(b)).
p(a).
% true.

retract(p(X) :- q(a)).
p(a).
% false.
```

<!--vert-->

dynamically remove clauses using `retractall/1`

```prolog
assertz(q(a)).
assertz((p(X) :- q(X))).
assertz(p(b)).
p(a), p(b).
% true.

retractall(p(_)).
p(a).
% false.
p(b).
% false.
```

<!--vert-->

dynamically remove a predicate using `abolish/1`

```prolog
assertz(p(a)).
assertz(p(b)).
p(a), p(b).
% true

abolish(p/1).
p(X).
% ERROR: Unknown procedure: p/1 (DWIM could not correct goal)
```

---

### meaning of a prolog program

* declarative meaning
  * the inference algorithm is an implementation detail
  * not always easy to achieve
* procedural meaning
  * but thinking procedurally makes it harder to come up with an elegant solution
  * beats the purpose of the paradigm

---

### matching

two terms match if:

* they are identical
* the variables in both terms can be instantiated to make the terms identical

<!--vert-->

the operator `=` performs matching

```prolog
course(N, S, 95) = course(X, fall, G).
/*
N = X,
S = fall,
G = 95.
*/
```

<!--vert-->

```prolog
course(N, S, 95) = course(Y, M, 96).
% false.

course(X) = semester(Y).
% false.
```

<!--vert-->

#### matching rules

terms `S` and `T` match if:

* `S` and `T` are the same atom
* `S` and `T` are the same number
* if one is a variable it's instantiated to the other
* if `S` and `T` are compound terms, they match iff:
  * they have the same functor and arity
  * all their corresponding arguments match
  * the variable instantiations are compatible

<!--vert-->

#### geometric example

use compound terms to represent geometric shapes

```prolog
point(1, 1)
seg( point(1, 1), point(2, 3) )
triangle( point(4, 2), point(6, 4), point(7, 1) )
```

<!--vert-->

```prolog
triangle(point(1, 1), A, point(2, 3))
=
triangle(X, point(4, Y), point(2, Z)).
/*
A = point(4, Y),
X = point(1, 1),
Z = 3.
*/
```

<!--vert-->

#### matching as means of computation

facts:

```prolog
vertical(seg(
    point(X, Y1),
    point(X, Y2)
)).
```

queries:

```prolog
vertical(seg(point(1, 1), point(1, 2))).
% true.

vertical(seg(point(1, 1), point(2, Y))).
% false.

vertical(seg(point(2,3), P)).
% P = point(2, _17044).
```

---

### arithmetic

* the operators `+ - * / div mod` are (infix) binary relations
* but they are arithmetic operators after the operator `is`

```prolog
X = 1 + 2.
% X = 1+2.

X is 1 + 2.
% X = 3.
```

<!--vert-->

#### comparison operators

```prolog
X > Y
X < Y
X >= Y
X =< Y
X =:= Y  % equal
X =\= Y  % not equal
```

<!--vert-->

the comparison operators also force evaluation

```prolog
11 * 6 = 66.
% false.

11 * 6 =:= 66.
% true.
```

<!--vert-->

#### `=` VS. `=:=`

* `=` is used for matching and may instantiate variables
* `=:=` causes an arithmetic evaluation of its operands and cannot instantiate variables

```prolog
1 + X = Y + 2.
% X = 2, Y = 1.

1 + X =:= Y + 2.
% ERROR: =:=/2: Arguments are not sufficiently instantiated
```

<!--vert-->

#### GCD

```prolog
gcd(X, X, X).
gcd(X, Y, D) :-
    X < Y,
    Y1 is Y - X,
    gcd(X, Y1, D).
gcd(X, Y, D) :-
    Y < X,
    gcd(Y, X, D).
```

---

### builtin control predicates

<!--vert-->

#### conjunction `,/2`

the goal `(G1, G2)` succeeds if `G1` and `G2` succeed

<!--vert-->

#### disjunction `;/2`

the goal `(G1 ; G2)` succeeds if `G1` or `G2` succeed

defined as follows:

```prolog
(G1 ; G2) :- G1.
(G1 ; G2) :- G2.
```

<!--vert-->

#### true

the predicate `true/0` always succeeds

<!--vert-->

#### false

the predicates `false/0` and `fail/0` always fail

<!--vert-->

#### negation as failure

* the negation predicate is `\+/1`
* for known predicates, prolog works under a closed world assumption - if something can't be proved then it is false
* it is not logical negation!

<!--vert-->

```prolog
assertz(person(jimmy)).
assertz(person(cindy)).

person(rick).
% false.

\+ person(rick).
% true.
```

<!--vert-->

it might not work like you'd expect

```prolog
person(X).
% X = jimmy ; X = cindy.

\+ person(X).
% false.
```

why doesn't prolog answer with `X = rick` or simply with `true`?

<!--vert-->

`person(X)` succeeds so its negation fails

* if `G` fails `\+ G` succeeds
* if `G` succeeds `\+ G` fails

<!--vert-->

`\+/1` allows for non-monotonic reasoning - a fact can become false by adding clauses to the database

```prolog
assertz(illegal(murder)).
assertz((legal(X) :- \+ illegal(X))).

legal(theft).
% true.

assertz(illegal(theft)).
legal(theft).
% false.
```

---

### exercise - family tree

you have a database with the following predicate

```prolog
parent(X, Y).  % X is Y's parent

% examples:
parent(adam, cain).
parent(eve, cain).
parent(cain, enoch).
```

define a predicate `grandparent(X)` that holds when `X` is a grandparent

<!--vert-->

```prolog
...
```
<!-- .element: data-codeblock-editable data-language="text/x-prolog" -->

<!--vert-->

```prolog
grandparent(X) :- parent(X, Y), parent(Y, _).
```

<!--vert-->

define a predicate `nuclear(X, Y)` that holds when `X` and `Y` are in the same nuclear family

a nuclear family consists of 2 parents and their common children

<!--vert-->

```prolog
...
```
<!-- .element: data-codeblock-editable data-language="text/x-prolog" -->

<!--vert-->

```prolog
nuclear(X, Y) :-  % siblings
    parent(P1, X), parent(P2, X)
    parent(P1, Y), parent(P2, Y),
    \+(P1 = P2).  % alternatively: `P1 \= P2`

nuclear(X, Y) :-
    parent(X, C), parent(Y, C).
```

---

### exercise - binary trees

we represent binary trees as terms:

* `nil` is the empty tree
* `node(N, Tl, Tr)` is a tree node where `N` is some number and `Tl` and `Tr` are binary trees

define a predicate `tree_size(T, S)` such that `T` is a binary tree and `S` is its size

<!--vert-->

```prolog
...
```
<!-- .element: data-codeblock-editable data-language="text/x-prolog" -->

<!--vert-->

```prolog
tree_size(nil, 0).
tree_size(node(_, Tl, Tr), S) :-
    tree_size(Tl, Sl),
    tree_size(Tr, Sr),
    S is Sl + Sr + 1.
```

<!--vert-->

define a predicate `tree_max(T, M)` such that `T` is a binary tree and `M` is the max of the values of `T`'s nodes

you may use the arithmetic function `max/2`

```prolog
...
```
<!-- .element: data-codeblock-editable data-language="text/x-prolog" -->

<!--vert-->

```prolog
tree_max(node(N, nil, nil), N).
tree_max(node(N, nil, Tr), M) :-
    tree_max(Tr, Mr), M is max(N, Mr).
tree_max(node(N, Tl, nil), M) :-
    tree_max(Tl, Ml), M is max(N, Ml).
tree_max(node(N, Tl, Tr), M) :-
    tree_max(Tl, Ml),
    tree_max(Tr, Mr),
    M is max(N, Ml, Mr).
```

<!--vert-->

define a predicate `perfect_tree(T, H)` such that `T` is a perfect binary tree and `H` is its height

a node's value should be its height

a perfect binary tree is a binary tree in which all interior nodes have two children and all leaves have the same depth

<!--vert-->

```prolog
...
```
<!-- .element: data-codeblock-editable data-language="text/x-prolog" -->

<!--vert-->

```prolog
perfect_tree(nil, 0).
perfect_tree(node(H, Tl, Tl), H) :-
    H > 0,
    H1 is H - 1,
    perfect_tree(Tl, H1).
```

---

### cuts

<!--vert-->

automatic backtracking may cause inefficiency.

consider the following rule set:
```prolog
f(X, 0) :- X #< 3.
f(X, 2) :- 3 #=< X, X #< 6.
f(X, 4) :- 6 #=< X. 
```
and the goal
```prolog
f(1, Y), 2 #< Y.
```

<!--vert-->

we notice the goal fails: the only option for `Y #>= 4` is `Y = 6` but that requires `X #>= 6` to succeed. therefore, this goal fails.

these rules are disjoint - at most one of them will succeed. if a goal matches one of the rules and fails, there's no use in trying the rest of the rules.

how can we prevent this?

<!--vert-->

*cuts* prevent backtracking from some point on.

cuts are denoted by the subgoal `!` which will always succeed, but will then prevent further backtracking
the last example can be rewritten like this:

```prolog
f(X, 0) :- X #< 3, !.
f(X, 2) :- 3 #=< X, X #< 6, !.
f(X, 4) :- 6 #=< X. 
```

whenever the goal `f(X, Y)` is encountered, we will only test the first rule that matches. if we perform the query again, we will get the same result, but only the first rule will be attempted.

<!--vert-->

we *did not* change the *declarative meaning* of the code - it still performs the same function. we have changes its *imperative meaning* - it now performs its search differently.

we used cuts to make the code more efficient. can we go further?

if we got to the second rule in our example, surely it isn't the case that `X #< 3`, otherwise, we would have reached the cut and stopped backtracking.

we can really just remove the extra checks. 

<!--vert-->

```prolog
f(X, 0) :- X #< 3, !.
f(X, 2) :- X #< 6, !.
f(X, 4). 
```

- now, the cuts *do* affect the declarative meaning - removing the cuts will result in a different result
- we also notice that in this situation, the order of the clauses does matter for the result (and not just for efficiency)
- this motivates us to discuss *green* and *red* cuts

<!--vert-->

**green cuts** - cuts that when removed, lead to the same declarative result. they do not have an effect on the *declarative meaning*.

when reading a program, we can ignore green cuts.

**red cuts** - cuts that do effect the declarative meaning of the program. these cuts make programs difficult to understand and should be used with care.
  
<!--vert-->

when the cut is encountered, it does succeed immediately, but it commits the algorithm to every choice it has made up until reaching the cut.

```prolog
H :- A1, A2, .... Am, !, B1, B2, ..., Bn.
```

when Prolog encounters the cut, the solution to `A1, ..., Am` is frozen and *all other possible solutions are discarded*.

in addition, the parent goal `H` cannot be matched to any other rule.

<!--vert-->

we consider the following program:

```prolog
C :- P, Q, R, !, S, T, U.
C :- V.
A :- B, C, D.
```

and the goal `A`. 

- backtracking is possible within `P`, `Q`, `R`
- when the cut is reached, the current solution for `P`, `Q`, `R` is chosen and all other solutions are dumped
- the alternative clause `C :- V` is also dumped
- backtracking **is** still possible in `S`, `T`, `U`, and also in `B`, `C`, `D`

<!--vert-->

### examples with cuts

adding to a list without duplicates:

```prolog
add(X, L, L) :- member(X, L), !.
add(X, L, [X|L]) :- !.
```

"Mary likes all elements but snakes"

```prolog
likes(mary, X) :- snake(X), !, 1 = 0.
likes(mary, X) :- animal(X).
```

this last example is an example of a common idiom in Prolog - negation. the cut prevents backtracking, and then we cause the goal to fail.

<!--vert-->

### negation

the special goal `fail` always fails - it's like `1 = 0`. the special goal `true` always succeeds - it's like `1 = 1`.

we define the `not` predicate:
```prolog
not(P) :- P, !, fail.
not(P).
```

this allows us to define predicates like `different` which succeeds only if two terms do not match to each other:

```prolog
different(X, Y) :- not(X = Y).
```

<!--vert-->

it is important to note that `not(P)` does not mean that `P` has to be false - it means that `P` cannot be proven.

```prolog
r(a).
q(b).
p(X) :- not(r(X)).
```

can you tell what `q(X), p(X).` will print? what about `p(X), q(X).`?

NOTE: `X = b.`, `false.`


<!--vert-->

we use cuts to specify mutually exclusive rules: if `cond` then `conclusion 1`, *otherwise* `conclusion 2`.

if there are no cuts in a program, we can change the order of the clauses and goals without changing the declarative meaning. we know this is not the case for programs that do have cuts.

<!--vert-->
 
### exercise

is this a green cut or a red cut?

```prolog
min(X, Y, X) :- X #=< Y, !.
min(X, Y, Y).
```

NOTE: red

