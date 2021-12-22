# Prolog

## control predicates

---

control predicates are predicates that control the flow of the program.

Prolog does not have `if`, `for` or `break` statements, for example, but we can control the flow of the program between predicates by using control predicates.

<!--vert-->

#### basic examples

reminder: 

the predicate `fail/0` will always fail (like `1 = 0`):
```prolog
X = 1, fail.
```


compare with
```prolog
X = 1.
```

similarly, the predicate `true/0` will always succeed (like `1 = 1`):
```prolog
X = 1 ; true.
```

NOTE: expected results - `false.`, `X = 1.`, `X = 1 ; true.`.

<!--vert-->

the predicate `repeat/0` will always succeed, and will repeat the body of the predicate until it fails:
```prolog
repeat, X = 1.
```

NOTE: expected result - `X = 1; X = 1; X = 1; ...`.

<!--vert-->

#### cuts

*cuts* are control predicates that also serve to solve another problem that we face in logic programming: automatic backtracking may cause inefficiency.

consider the following clause set for `f/2`:
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

we *did not* change the *declarative meaning* of the code - it still performs the same function. we have changed its *imperative meaning* - it now performs its search differently.

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

"Mary likes all animals but snakes"

```prolog
likes(mary, X) :- snake(X), !, fail.
likes(mary, X) :- animal(X).
```

this last example is an example of a common idiom in Prolog - negation. the cut prevents backtracking, and then we cause the goal to fail.

<!--vert-->

### negation

we define the `not/1` predicate:
```prolog
not(P) :- P, !, fail.
not(P).
```

the `not/1` predicate acts the same way as `\+` that we saw earlier - it is not negation but rather unprovability. 

this allows us to define predicates like `different/2` which succeeds only if two terms do not match to each other:

```prolog
different(X, Y) :- not(X = Y).
```

<!--vert-->

```prolog
r(a).
q(b).
p(X) :- not(r(X)).
```

can you tell what `q(X), p(X).` will print? what about `p(X), q(X).`?

NOTE: `X = b.`, `false.`


<!--vert-->

we can use cuts to specify mutually exclusive rules: if `cond` then `conclusion 1`, *otherwise* `conclusion 2`.

if there are no cuts in a program, we can change the order of the clauses and goals without changing the declarative meaning. we know this is not the case for programs that do have cuts.

<!--vert-->

### exercise

is this a green cut or a red cut?

```prolog
min(X, Y, X) :- X #=< Y, !.
min(X, Y, Y).
```

NOTE: red

<!--vert-->

### exercise

define the predicate `maybe_once/1` that accepts a predicate and succeeds at most once.

for example, for the dataset:
```prolog
ta(yair).
ta(itamar).
ta(nadav).
```
and for the goal `maybe_once(ta(X))`, we would expect to get `X = yair.`.

<!--vert-->

```prolog



```
<!-- .element: data-codeblock-editable data-language="text/x-prolog" -->

NOTE: `maybe_once(X) :- X, !.`

<!--vert-->

#### ->

The `->/2` predicate is used to commit to choices made at its left-hand side, similarly to cuts like we saw, but unlike cuts, it does not discard all other clauses.

we saw this example in the previous section:
```prolog
likes(mary, X) :- snake(X), !, fail.
likes(mary, X) :- animal(X).
```
it has semantics "Mary likes all animals, except for snakes (even if snakes are animals)"

<!--vert-->

what will happen now?
```prolog
likes(mary, X) :- snake(X) -> fail.
likes(mary, X) :- animal(X).
```

NOTE: Mary likes all animals and she doesn't like snakes, unless snakes are animals

<!--vert-->

for the datasets `animal(a), snake(a), animal(b)`, we get:

- the first program will have `likes(mary, b)` but not `likes(mary, a)` or `likes(mary, c)`.
- the second program will have `likes(mary, a)`, `likes(mary, b)` but not `likes(mary, c)`.

this is because `->/2` does not discard the second clause.

<!--vert-->

it is possible to define an "else" branch, for example:

```prolog
grade(X, Y) :- X #>= 100 -> Y = 100 ; Y = X.
```

NOTE: check `grade(101, Y).` gives `Y = 100.`, `grade(99, Y).` gives `Y = 99.`

<!--vert-->

#### exercise

redefine the predicate ``maybe_once/1`` from earlier using `->/2`.

```prolog


```
<!-- .element: data-codeblock-editable data-language="text/x-prolog" -->


NOTE: `maybe_once(P) :- P -> true.`
