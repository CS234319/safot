# Prolog

## lists

---

a **list** is a sequence of any number of terms

```prolog
[1, 2, 3]
[a, b, c, d]
[a, [1, 2, 3], tom, 15, date(1, may, 1995)]
```

<!--vert-->

a list is actually a pair of a head and a tail

```prolog
[Head | Tail]
[A, B, C] = [A | [B | [C | []]]] = [A, B | [C]]
```

---

### length/2

```prolog
length([], 0).
length([_|Tail], N) :-
    length(Tail, N1),
    N is 1 + N1.
```

```prolog
length([a, b, [c, d], e], N).
% N = 4.

length(L, 4).
% L = [_10798, _10804, _10810, _10816].
```

<!--vert-->

### length with CLP(FD)

```prolog
length([], 0).
length([_|Tail], N) :-
    N #= N1 + 1,
    length(Tail, N1).
```

---

### TODO: CLP(FD) with lists

---

### list predicates

<!--vert-->

#### is_list/1 (predefined)

```prolog
is_list([]).
is_list([X|Xs]) :- is_list(Xs).
```

<!--vert-->

#### member/2 (predefined)

```prolog
member(X, [X|Xs]).
member(X, [Y|Ys]) :- member(X, Ys).
```

<!--vert-->

#### prefix/2

```prolog
prefix([], L).
prefix([X|Xs], [X|Ys]) :- prefix(Xs, Ys).
```

<!--vert-->

#### suffix/2

```prolog
suffix(Xs, Xs).
suffix(Xs, [Y|Ys]) :- suffix(Xs, Ys).
```

<!--vert-->

#### del/3

```prolog
del(X, L, R)
```

`R` is `L` without one of the occurrences of `X`

```prolog
del(X, [X|Xs], Xs).
del(X, [Y|Ys], [Y,Zs]) :- del(X, Ys, Zs).
```

<!--vert-->

#### insert/3

```prolog
insert(X, L, R) :- del(X, R, L).
```

<!--vert-->

#### append/3

```prolog
append([], Ys, Ys).
append([X|Xs], Ys, [X|Zs]) :- append(Xs, Ys, Zs).
```

<!--vert-->

#### define member/2 using append/3

```prolog
member(X, Xs) :- append(_, [X|_], Xs).
```

<!--vert-->

#### sublist/2

```prolog
sublist(Xs, Ys) :-
    append(As, Bs, Ys),
    append(Xs, Cs, Bs).
```

<!--vert-->

```prolog
prefix(Xs, Ys) :- append(Xs, _, Ys).

suffix(Xs, Ys) :- append(_, Xs, Ys).

sublist(Xs, Ys) :-
    prefix(Ps, Ys),
    suffix(Xs, Ps).
```

<!--vert-->

#### permutation/2

```prolog
permutation([], []).
permutation([X|L], P) :-
    permutation(L, L1),
    insert(X, L1, P).
```
