# python

## introduction

(based on [the python tutorial](https://docs.python.org/3/tutorial/))

---

### comments

```python
# this is the first comment
spam = 1  # and this is the second comment
          # ... and now a third!
text = "# This is not a comment because it's inside quotes."
```
<!-- .element: data-thebe-executable-python data-language="text/x-python" -->

---

### numbers

```python
2 + 2
```
<!-- .element: data-thebe-executable-python data-language="text/x-python" -->

```python
50 - 5 * 6
```
<!-- .element: data-thebe-executable-python data-language="text/x-python" -->

```python
(50 - 5 * 6) / 4
```
<!-- .element: data-thebe-executable-python data-language="text/x-python" -->

```python
8 / 5  # division always returns a floating point number
```
<!-- .element: data-thebe-executable-python data-language="text/x-python" -->

```python
17 // 3  # floor division discards the fractional part
```
<!-- .element: data-thebe-executable-python data-language="text/x-python" -->

<!--vert-->

the function `type` returns the type of an object

```python
type(2)
```
<!-- .element: data-thebe-executable-python data-language="text/x-python" -->

```python
type(1.5)
```
<!-- .element: data-thebe-executable-python data-language="text/x-python" -->

```python
type(1 + 1j)  # complex numbers!
```
<!-- .element: data-thebe-executable-python data-language="text/x-python" -->

<!--vert-->

`=` is used for assignment

```python
width = 20
height = 45
width * height
```
<!-- .element: data-thebe-executable-python data-language="text/x-python" -->

---

### strings

```python
'spam eggs'  # single quotes
```
<!-- .element: data-thebe-executable-python data-language="text/x-python" -->

```python
'doesn\'t'  # use \' to escape the single quote...
```
<!-- .element: data-thebe-executable-python data-language="text/x-python" -->

```python
"doesn't"  # ...or use double quotes instead
```
<!-- .element: data-thebe-executable-python data-language="text/x-python" -->

```python
"""
a
multiline
string
"""
```
<!-- .element: data-thebe-executable-python data-language="text/x-python" -->

<!--vert-->

#### print

```python
print("a string")
```
<!-- .element: data-thebe-executable-python data-language="text/x-python" -->

```python
print(5)
```
<!-- .element: data-thebe-executable-python data-language="text/x-python" -->

<!--vert-->

#### string operations

```python
5 * "na " + "batman!"
```
<!-- .element: data-thebe-executable-python data-language="text/x-python" -->

```python
word = "Python"
word[4]
```
<!-- .element: data-thebe-executable-python data-language="text/x-python" -->

```python
word[2:5]
```
<!-- .element: data-thebe-executable-python data-language="text/x-python" -->

```python
len('supercalifragilisticexpialidocious')
```
<!-- .element: data-thebe-executable-python data-language="text/x-python" -->

<!--vert-->

strings are immutable

```python
word[0] = "J"
```
<!-- .element: data-thebe-executable-python data-language="text/x-python" -->

---

### lists

```python
squares = [1, 4, 9, 16, 25]
squares
```
<!-- .element: data-thebe-executable-python data-language="text/x-python" -->

<!--vert-->

```python
squares[0]
```
<!-- .element: data-thebe-executable-python data-language="text/x-python" -->

```python
squares[-1]  # negative indices
```
<!-- .element: data-thebe-executable-python data-language="text/x-python" -->

```python
squares[-3:]
```
<!-- .element: data-thebe-executable-python data-language="text/x-python" -->

<!--vert-->

```python
squares + [36, 49, 64]
```
<!-- .element: data-thebe-executable-python data-language="text/x-python" -->

<!--vert-->

```python
cubes = [1, 8, 27, 65, 125]  # something's wrong here
cubes[3] = 64  # replace the wrong value
cubes
```
<!-- .element: data-thebe-executable-python data-language="text/x-python" -->

<!--vert-->

```python
cubes.append(6**3)
cubes
```
<!-- .element: data-thebe-executable-python data-language="text/x-python" -->
