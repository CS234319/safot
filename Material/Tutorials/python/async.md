# asynchronous programming in Python

---



### why do we need this?

let's run a request that will take a while, and in the meanwhile do another calculation we need:

```python
import requests
print(requests.get("https://eladkay.com/safot_async/").text)
print([i for i in range(10)])
```
<!-- .element: data-thebe-executable-python -->


<!--vert-->
programming languages typically run synchronously - commands are executed one after the other and not in the same time

we could benefit from a performance boost if we work asynchronously: we let the slow processes run while we do other things


<!--vert-->
#### asyncio
`asyncio` is a concurrency module added in Python 3.4

it adds the `await` and `async` keywords as we will see 

```python
import asyncio
```
<!-- .element: data-thebe-executable-python -->

<!--vert-->

we can declare a function with the `async` keyword:
```python
async def run_request():
    print(requests.get("https://eladkay.com/safot_async/").text)
run_request()
```
<!-- .element: data-thebe-executable-python -->

kind of similar to generators - an `async` function returns a coroutine object and is *not* executed when called

in other languages this may be called a *future* or a *promise*

<!--vert-->

we execute a single coroutine object with `asyncio.run`:

```python
asyncio.run(main())
```
this moves us from the *synchronous* world to the *asynchronous* world

NOTE: this does not work in the slides because jupyter has its own event loop. make a file out of it and run it manually.
