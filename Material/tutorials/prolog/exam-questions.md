# prolog

## exam questions

---

### question 1

<!--vert-->

#### question 1.1

write rules for the predicate `interleave/2` such that `interleave(L, R)` is true iff `L` is a list of lists and `R` is the lists in `L` interleaved.

* you may assume that `L` is a concrete list of lists
* example: `interleave([[p,l],[r,o],[o,g]], [p,r,o,l,o,g])`

<!--vert-->

```prolog
interleave([], []).
interleave([[]|X], R) :- interleave(X, R).
interleave([[X|Xs]|Ys], [X|R]) :-
    append(Ys, [Xs], Z),
    interleave(Z, R).
```

<!--vert-->

#### question 1.2

the predicates `cond1/1` and `cond2/1` take a concrete integer. implement `filter/2` such that `filter(Xs, Ys)` is true iff `Xs` is a list of integers and `Ys` is a list of all integers from `Xs` for which `cond1` is true and `cond2` is false.

* you may assume `Xs` is a concrete list of integers

<!--vert-->

```prolog
filter([], []).
filter([X|Xs], [X|R]) :-
    cond1(X), \+ cond2(X), filter(Xs, R), !.
filter([X|Xs], R) :- filter(Xs, R).
```
