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
```
<!-- .element: data-thebe-executable-python -->

<!--vert-->

a generator function returns a **generator object**

```python
g = fib()
```
<!-- .element: data-thebe-executable-python -->

<!--vert-->

to get the values that the generator yields use `next`

```python
next(g)
```
<!-- .element: data-thebe-executable-python -->

---

### how does it work?

---

