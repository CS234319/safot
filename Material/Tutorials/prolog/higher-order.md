# Prolog

## higher order programming

---

### meta-call predicates

meta-call predicates are used to call terms constructed at run time

<!--vert-->

#### call/1

`call/1` is used to call a term

```prolog
call(person(N, doe) = person(john, L)).
% N = john, L = doe.
```

<!--vert-->

#### call/\[2..\]

`call/[2..]` appends arguments to the predicate's argument list and calls the result

```prolog
plus(X, Y, R) :- X + Y #= R.

call(plus(X), 3, 7). % effectively calls `plus(X, 3, 7)`
% X = 4.
```

<!--vert-->

#### append/2

`append/2` appends a **list** of arguments to the argument list and calls the result

```prolog
append(plus(X), [3, 7]).
% X = 4.
```

* used when the number of arguments isn't fixed

---

