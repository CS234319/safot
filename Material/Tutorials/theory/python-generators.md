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
type(g)
```
<!-- .element: data-thebe-executable-python -->

<!--vert-->
to get the values that the generator yields use `next`

```python
print(next(g))
print(next(g))
print(next(g))
print(next(g))
print(next(g))
```
<!-- .element: data-thebe-executable-python -->
<!--vert-->

you can also define finite generators:
```python
def first_two_primes():
    yield 2
    yield 3
g = first_two_primes()
print(next(g))
print(next(g))
print(next(g))
```
<!-- .element: data-thebe-executable-python -->
exhausting a finite generator raises the `StopIteration` exception.

---

### how does it work?

---
generator functions are calculated *lazily*. the function is first executed after `next` is first applied on the 
generator object. `yield` is a **sequencer** - after a `yield` statement, execution jumps back to the statement after `next`.
<!--vert-->
Python creates a *closure* around generator functions - local variables and other storage cells used in the generator function are
saved and not deleted by the garbage collector until either the generator is exhausted, or all references to the generator
object have been deleted. 

---

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
next(g)
```
<!-- .element: data-thebe-executable-python -->

is -1, because it yields `last`, which is -1 to start.
<!--vert-->
now,
```python
g.send(5)
```
<!-- .element: data-thebe-executable-python -->
returns 10 - the value `5` is placed as the value of `yield last`, which is then multiplied by 2 and yielded in the next iteration.

`send` resumes execution of the function, placing the value sent to the function as the value of the `yield`
command expression, and running the function until the next `yield`, and so on.
<!--vert-->

another option for control flow with generators is `throw` - throw throws an exception stacktraced as if it was thrown
 in the last `yield` executed in the generators - it does not resume execution of the function. 
<!--vert-->
example:
```python
def thrower():
    while True:
        print("x")
        yield 5
thrower
```
<!-- .element: data-thebe-executable-python -->
<!--vert-->

as we saw before,
```python
g = thrower()
value = next(g)
```
<!-- .element: data-thebe-executable-python -->

places value 5 in `value` and prints `x`.
<!--vert-->
however,
```python
g.throw(ValueError())
```
<!-- .element: data-thebe-executable-python -->

causes a `ValueError` with a stacktrace that refers to the `yield` *that already occurred* without printing `x`!
<!--vert-->
if `next(g)` was never called before throwing, the exception will be stacktraced to line 1:
```python
g = thrower()
g.throw(ValueError())
```
<!-- .element: data-thebe-executable-python -->

---

### exercises

---
1. create a generator function returning all prime numbers.
<!--vert-->
solution:
```python
def primes():
    last = 1
    while True:
        last += 1
        flag = True
        for i in range(2, last):
            if last % i == 0:
                flag = False
        if flag:
                yield last
```
<!-- .element: data-thebe-executable-python -->
<!--vert-->
2. create a generator function for the Fibonacci sequence. the generator can receive a pair of integers,
and when it does, it restarts the sequence with the values as the new initial values. (example in next slide)
<!--vert-->
example:
```python
g = new_fib()
next(g) # returns 1
next(g) # returns 1
next(g) # returns 2
next(g) # returns 3
# ...
g.send((1, 2)) # returns 1
next(g) # returns 2
next(g) # returns 3
next(g) # returns 5
```
<!--vert-->
solution:
```python
def new_fib():
    a = 0
    b = 1
    while True:
        pair = yield b
        if pair != None:
            a, b = pair
            a, b = b - a, a
        else:
            a, b = b, a + b
```
