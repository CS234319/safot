# automatic memory management

---

## reference counting

---vert---

### reference counting

* every variable has a reference-count(RC) field
* RC is the number of references to the variable
* when RC reaches 0 the variable is deallocated

```java
Object a = new Object(); // let's call it A
// RC(A) = 1
Object b = new Object(); // let's call it B
// RC(B) = 1
b = a;
// RC(A) = 2
// RC(B) = 0 -> B is deallocated
```

---vert---

### pros

* predictable performance
* smooth execution without interruptions
* implementable in:
  * manual memory management system
  * automatic memory management system
* cost is proportional to actual computation

---vert---

### cons

* cannot deal with circular structures
* is generally slow incurring a huge "write barrier"

---

## garbage collection

---vert---

### garbage collection

deallocation is the responsibility of the language runtime system, not the programmer's

* programmer never deallocates memory
* a GC procedure collects unused variables from time to time
* GC is found in: Java, Python, ML, Lisp, ...

---vert---

### mark & sweep

* **mark** mark all cells as unused
* **sweep** unmark all cells in use (stack, global variables), and cells which can be accessed (directly or indirectly) from these
* **release** release all marked cells

