# python

## generators

---

a function that contains a yield statement is called a **generator function**

```python
def fib():
    a, b = 0, 1
    while True:
        yield b
        a, b = b, a + b
fib
```
<!-- .element: data-thebe-executable-python -->

<!--vert-->

a generator function returns a **generator object**

```python
g = fib()
```
<!-- .element: data-thebe-executable-python -->


such that 
```python
type(g)
```
<!-- .element: data-thebe-executable-python -->

would return `<class 'generator'>`.
<!--vert-->
to get the values that the generator yields use `next`

```python
next(g)
```
<!-- .element: data-thebe-executable-python -->
<!--vert-->

you can also define finite generators:
```python
def first_three_primes():
    yield 2
    yield 3
    yield 5
```
<!-- .element: data-thebe-executable-python -->
exhausting a finite generator raises the `StopIteration` exception.
<!--vert-->

---

### how does it work?

---
generator functions are calculated *lazily*. the function is first executed after `next` is first applied on the 
generator object. `yield` is a **sequencer** - after a `yield` statement, execution jumps back to the statement after `next`.

Python creates a *closure* around generator functions - local variables and other storage cells used in the generator function are
saved and not deleted by the garbage collector until either the generator is exhausted, or all references to the generator
object have been deleted. 

---
<!--vert-->
### send and throw

---
in fact, `yield` is a *command expression*. in addition to its role as a sequencer, it can also be used to receive
values from outside the generator using `send`
```python
def echoer():
    last = -1
    while True:
        last = (yield last) * 2

g = echoer()
value = next(g)
```
<!-- .element: data-thebe-executable-python -->

places -1 in `value` (because it yields `last`, which is -1 to start). now,
```python
g.send(5)
```
<!-- .element: data-thebe-executable-python -->
returns 10 - the value `5` is placed as the value of `yield last`, which is then multiplied by 2 and yielded in the next iteration.

`send` resumes execution of the function, placing the value sent to the function as the value of the `yield`
command expression, and running the function until the next `yield`, and so on.
<!--vert-->

another option for control flow with generators is `throw` - throw throws an exception stacktraced as if it was thrown
 in the last `yield` executed in the generators - it does not resume execution of the function. here is a demonstrative example:
```python
def thrower():
    while True:
        print("x")
        yield 5
```
<!-- .element: data-thebe-executable-python -->
<!--vert-->

as we saw before,
```python
g = thrower()
value = next(g)
```
<!-- .element: data-thebe-executable-python -->

places value 5 in `value` and prints `x`. however,
```python
g.throw(ValueError())
```
<!-- .element: data-thebe-executable-python -->

causes a `ValueError` with a stacktrace that refers to the `yield` *that already occurred*:
```
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
  File "<stdin>", line 4, in thrower
ValueError
```
without printing `x`! if `next(g)` was never called before throwing, the exception will be stacktraced to line 1:
```
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
  File "<stdin>", line 1, in thrower
ValueError
```
