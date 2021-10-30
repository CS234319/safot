# Mini-LISP

<!--vert-->

## Lisp: The Mother of Functional Programming

* designed in 1958 (!) but remains influential and in use
* the second programming language ever (preceded only by FORTRAN)
* the first example of the *functional programming paradigm*:
  * no variables, no assigment
  * no statements nor sequential computation
  * no loops

<!--vert-->

* conisdered a classic of programming and computer science; every one should know
  * what is an S-expression and how to implement one
  * what are `CAR`, `CDR`, and `CONS`, and how they appear in their favorite language
  * what is `LAMBDA`, and whether and how it appears in their favorite programming language
* standarized implementation: The Huge Common Lisp (CL) Standard
  * GNU Lisp manual spans over 1,200 pages

<!--vert-->

influential and used to this very day:

* used for a zillion AI/other applications: the first symbolic math program, Grammarly, Google's flight search, OpusModus
* used for quick programming of complex algorithms, e.g., algorithmic trading
  * influenced many other languages such as
  * functional paradigm: Standard ML, Haskell, Scheme, Clojure, Racket, ...
  * famous, but not functional: JavaScript, R, Perl, Swift, Logo, Ruby, Python, Scala, Julia,  Lua
  * less famous: Forth, Nim, Dylan, Rebol, Tcl, Io,  ...

---

### Min-Lisp = Cherry Picking of Lisp

*Design Objective*: maximize value/price ratio

Mini-LISP is a programming language designed for students of programming languages:

* Quick to learn and master. Inappropriate for any serious programming.
* Captures the essence of Lisp
* Meticiuluously, purges, eliminates, and/or ignores, anything else!

<!--vert-->

the language is small; its capabilities are huge:

* as capable as any other langauge (Turing comlete)
* capable of meta programming; it should be easy to write in Mini-Lisp tools for
  * profiling Mini-Lisp
  * debugging Mini-Lisp
  * program transformation
  * executing programs in Mini-Lisp

<!--vert-->

## Value = Expected Lessons

expose students to important concepts:

1. taste of functional programming paradigm
2. symbolic computation
3. list processing
4. recursion
5. dynamic binding
6. REPL
7. evaluation
8. homoiconicity
9. The Church Rosser property
10. Turing completeness

<!--vert-->

## Price: Learning and Programming

miniscule language learning effort

1. syntaxt: trivial
2. design: slim! only one simple structure
3. featrues: very few
4. IDE: basic, but can run locally on your browser
5. tiny library: 8 functions
6. minimal builtins: 8 in total

<!--vert-->

programming in the small:

1. useless for large programs
2. no debugger, profiler, etc.
3. no support of integers, reals, strings, files, graphics, ...
4. not very fast (it is an interpreted language)
5. reference implementation (in C/C++/Chic) will crash on (not too) large programs

---

## Lesson 1: Symbolic Computation

<!--vert-->

* numeric computation is computation with numbers
* numbers are manipulated with the four basic arithmeitcal operations, comparison, etc.
* symbolic computation is about symbols:
  * examples of symbols: `a`, `+`, ...
  * symbols have no intrinsic meaning
  * meaning of symbols is determined by program
* allowed operations on symbols:
  * comparison for equality
  * assigning meeaning/binding/setting
  * finding meaning/dereferencing/interpreting
* but, symbols can be organized in data structures...

<!--vert-->

### Data Structrues of Symbols

LISP == LISt Processing, is all about lists:

* lists of symbols
* lists of lists of symbols
* lists of mixed kind: symbols and lists of symbols
* lists of items, each being either a list, or a list of items.

<!--vert-->

more generally, symbolic computation is also about data structrues containg symbols, e.g.,

* binary trees whose leaves/nodes/both are symbols
* trees of any degree whose leaves/nodes/both are symbols
* graphs whose nodes/edges/both are either symbols or similar graphs
* ...

<!--vert-->

## Lists in Lisp

empty list:

```lisp
()
```

singleton list containing the empty list:

```lisp
( () )
```

list containing two empty lists:

```lisp
( () () )
```

more lists:

```lisp
( (()) ())
((() ()) ())
( () ( (()) ()) ((() ()) ()))
```

<!--vert-->

## Atoms in Mini-Lisp

examples:

```lisp
November/2nd <^V>v ? 2x B4 && FOO ! 12 +
```

other Lisp dialects are not as permissive

<!--vert-->

upper/lower case:

* atoms are case insensitive; `a` is the same as `A`
* internal representation is always upper case
* convention:
  * input in lower case
  * output/internal representation: UPPER CASE

```lisp
t
; T
```

<!--vert-->

lists may contain atoms or lists:

```lisp
(A) ; a list containing one atom
(+ 12); a list containing two atoms
(A (B1 () ) ); a list with an atom and a list with an atom and the empty list.
```

the atom `NIL` is synonymous to the empty list `()`

---

## The S-Expression Data Structure

<!--vert-->

### Intution

s-Expression is short for *symbolic expression*

* can represent symbols, lists of symbols, lists of lists, etc.
* easy to manipulate: three elementary operations
* essentially, a binary tree in which all leaves are symbols

(other languages for symbolic compuations rely on other data structures, e.g., general trees or strings)

<!--vert-->

### Definition

* **given**: an alphabet, finite or infinite, of symbols
* **define**: set of *s-expression* over the alphabet has two kinds of elements
  1. *atomic s-expressions (atoms)*: every symbol in the alphabet is an s-expression
  2. *compound s-expressions (concstructed s-expressions)*: if 'S1' and 'S2' are s-expressions then, the *dottet pair* of 'S1' and 'S2', written '[S1.S2]' is also an s-Epxression
  3. nothing else is an s-expression

<!--vert-->

### Examples over finite alphabet '{a,b,c}'

```lisp
a, b, [a.b], [a.[b.c]], [[a.b].c], [c.[[a.b].[b.a]]]
```

---

## Lesson 2: Homoiconicity

<!--vert-->

### Etymology

* homo="the same"
* icon="representation"
* homoiconicity = "the same represenetation"

> a programming langauge P is homoiconic if a program p1 in P, can be manipulated as data by another program p2 in L, or even by p1 iteslf

<!--vert-->

very few examples:

* LISP
* Prolog
* Mathematica (Wolfram's langauge for symbolic mathematical computatio)
* All assembly languages
* R, Tcl, SNOBOL, Julia, XSLT, Rexx, ... (more or less famous languages)
* Turing machine

but not Smalltalk, C++, Java, ML, Scala, Python, and most mainstream programming languages

<!--vert-->

### Homoiconicity in LISP

* a LISP *program* is just an S-expression
* a LISP *function*
  * takes one parameter, which is an S-expression
  * returns a value, which is an S-expression
  * is itself an S-expression

<!--vert-->

## Lists vs. S-Expressions

LISP represents lists as S-expressions:

* every list is an S-expression
* not every S-expression is a list

<!--vert-->

### First/Rest Recursive Representation of Lists

essentially, the general embedding of a general tree in a binary tree: each node contains a pointer to eldest child and a pointer to the next sibling

#### Recursion base

the empty list, `()`, is represented by the special atom `NIL`

<!--vert-->

#### Recursive step

to represent a non-empty list L:

1. write L as:

   ```lisp
   (F x1 ... xn)
   ```

   where `F` is the first item in the list, and `x1 ... xn` is the, possibly empty, sequence of the remaining items in the list.
2. let `S1` be the S-expression repesentation of `F`
    * If `F` is an atom, then `S1` is `F`
    * Otherwise, `F` is a list, and `S1` is computed recursively
3. let `R` be the (possibly empty) list `(x1 ... xn)`
4. let `S2` be the the S-expression representation of `R` (computed recursively)
5. the S-expression representation of `L` is the dotted pair `[S1.S2]`

<!--vert-->

## The list notation

it is customary to write S-expressions as lists

1. atom `nil` is written as `()`
2. atom `a` is written as `A`
3. `[a.nil]` is written as `(A)`
4. `[a.[b.nil]]` is written as `(A B)`
5. `[a.[b.[c.nil]]]` is written as `(A B C)`
6. `[[a.nil].[b.nil]]` is written as `((A) B)`

<!--vert-->

not all S-expressions can be fully written with the list notatios

1. `[a.b]` is written as `[a.b]`
2. `[a.[[b.c].nil]]` is written as `(A [B.C])`

<!--vert-->

## Operations on S-Expressions (reminiscent of plus/minus on integers)

<!--vert-->

### CAR

* obtain the left sub-tree, e.g., `CAR` of `[[a.b].c]` is `[a.b]`
* obtain the first item of a given list, e.g.,  `CAR` of the two item list `((A) (B C))` is `(A)`
* fails on atoms (an empty list is an atom)
* in other languages/libraries: `head` / `first` / `top` / ...

<!--vert-->

### CDR

* obtain the right sub-tree, e.g., `CDR` of `[a.[b.[c.a]]]` is `[b.[c.a]]`
* obtain the rest of a given list, i.e., the list without its first element, e.g., CDR of the a three item list `((A) D (B C))` is a two item list `(D (B C))`
* fails on atoms (an empty list is an atom)
* in other languages/libraries: `tail` / `rest` / `remainder` / ...

<!--vert-->

### CONS

* construct a tree out of a given left and rigt sub-tree, e.g., CONS of `a` and `[b.b]` is `[A.[B.C]]
* prepend a given item to a given list,  e.g., `CONS` of `A` and `(B C)` is `(A B C)`
* never fails
* in other langauges/libraries: `prepend` / `push` / `::` (e.g., `A::B::C`) in Standard ML

<!--vert-->

* `CAR` and `CDR` are historical names; acronyms of registers in an ancient IBM machine on which LISP was first implemented; `CONS` is short of 'construct' or 'constructor'
* most Lisp dialects offer short hand functions such as `CAAR` (CAR of CAR), `CDAR` (CDR of CAR), `CADAR`, etc. In the interest of minimalizm, Mini-Lisp abstains.

---

## Predicates on S-Expressions (reminiscent of numerical comparison)

<!--vert-->

### NULL

* check wheher an S-expression is the special atom `NIL`
* used, e.g., to determine whether a list is exhausted in traversal
* never fails

<!--vert-->

### ATOM

* check whether an S-Expression is an atom
* used, e.g., to determine whether recursion on nested list structure ends
* never fails

<!--vert-->

### EQ

* check if two given atoms are equal
* returns "false" if any of the arguments is not an atom
* used, e.g., to recursively compare two S-expressions
* never fails

---

## Lists of Lists and Expression Trees

a list in Lisp is interpreted as function application; the list

   ```lisp
   (F x1 ... xn)
   ```

means: 'apply function F to arguments 'x1' through 'xn'. the nested list `(f (g 2 a) c)` is the LISP equivalent of `f(g(2,a),c)`.

<!--vert-->

the C expression

```c
sqrt(b*b - 4 * a * c)/(2*a)
```

is written in LISP as

```lisp
(/ (sqrt  (- (* b b) (* 4 a c))) (* 2 a))
```

evaluation of expressions in C (almost always) and in LISP (typically) is done bottom up: evaluate the arguments, and then apply the function to these.

---

## Meaning of atoms

* most Lisp dialects, assign 'meaning' to atoms such as `2`, `/`, `*`, `sqrt`, etc. Mini-Lisp doesn't!
* but, **all** LISP dialects, recognize the elementary functions: `CAR`, `CDR`, `CONS`, `NULL`, `ATOM`, `EQ`, ... (very few others)
* for example, the meaning of atom `CONS` is the CONS function, e.g.,

```lisp
> (cons () (() ()))
( NIL NIL NIL)
```

or, in some impelmentations

```lisp
> (cons () (() ()))
( () () ())
```

## Boolean values in Lisp

* `EQ`, `ATOM`, `NULL`, are "Boolean" functions that map S-epxression to S-expressions
* covention:
  * 'false; is marked by atom `NIL`
  * any other S-expression means 'true'
  * with the absence of a compelling reason, atom `T` is used to denote Boolean true

```lisp
> (eq () ())
T
> (eq T NIL)
NIL
> (eq (T NIL) (T NIL))
NIL
```

<!--vert-->

* the "Boolean" atoms are 't' and 'nil'; these atoms denote themselves
* other atoms can, technically, be used  possible as (kind of variables), by letting them denote other S-expressions.
* good LISP programs do not do that! functional programs do not use variables.

<!--vert-->

atoms with predefined meaning:

* the meaning of atom `nil` is atom `NIL`
* the meaning of atom `t` is atom `T`
* the meaning of atoms `CAR`, `CDR` TODO

### Other Atoms

* most atoms have no meaning
* other atoms are luxury

---

## Failures of computation (reminiscent of division by zero)

* `CONS`, `ATOM`, `EQ`, and `NULL` never fail
* `CAR` and `CDR` may fail (when applied to atoms)
* any function that calls `CAR` or `CDR` may fail
* a function invoked with more (less) arguments than it expects, will fail
* more generally, evaluation may fail
* further, evaluation may not terminate (stack overflow due to infinite recursion)

---

## The "Semantics" S-Expressions

the "semantics" of an S-expression, is the result of its "evaluation"; evaluating an S-expression gives another S-expression, unless the evaluation "fails"

<!--vert-->

### Semantics of atoms

1. the semantics of atom `nil` is itself, i.e., atom `NIL`
2. the semantics of atom `t` is itself, i.e., atom `T`
3. the semantics of several designated atoms is a function
    1. 8 + 1 atoms designate the primitive functions of Mini-LISP
        * `CAR`, `CDR`, `CONS`, `EQ`, `ATOM`: operators and predicates on S-expressions
        * `SET`, `COND`, `ERROR`: to be explained later
        * `EVAL`: a primitive function that takes an S-expression and returns its semantics, or fails.
    2. 5 predefined functions:
        * `NULL`: check whether an atom is `NIL`
        * `DEFUN`, `DEFUN'`, `LAMBDA`, `NLAMBDA`: make it posssible to define new functions
        * `QUOTE`: a function that prevents an S-expression from being evaluated
4. the semantics of any other atom is (initially) undefined; therefore, the evaluation of any other atom fails

<!--vert-->

### Semantics of dotted-pairs

the semantics of dotted pair `[x.y]`, is the application of function `x` to S-expression `Y`

1. `X` must be a name of a function that takes a certain number of arguments
2. `Y` must be a list of this many arguments
3. semnatics of `[x.y]` is the invocation of function named `X` on the list of arguments in `Y`
4. error if the expected number of arguments is different than the actual number of arguments

<!--vert-->

### Semantics of lists

semantics of `(f x y)` is the semantics of `[F.(X Y)]`, i.e., the application of function named `F` to the two arguments `X` and `Y`.

* `(cons t nil)` evaluates to `(T)`
* `(car (cons t nil))` evaluates to `(CAR (T))` and then to atom `T`
* `(cdr (cons t nil))` evaluates to `(CDR (T))` and then to the empty list `()` (which is also the atom `NIL`)
* `(cons nil (cons t nil))` evaluates to `(CONS NIL (T))` and then to the two item list `(NIL T)`

<!--vert-->

### Two semantics of function application

1. eager semantics: arguments are evaluated first, and then passed to function
2. normal semantics: arguments are passed to the function as is

most functions are eager; exceptions are:

* `ERROR`
* `COND`
* `QUOTE`
* functions defined with `NDEFUN`

---

## DETOUR: Compiled vs. Interpreted (and P-Code)

* compiled languages: translate the program, then execute it
  * prime examples: Fortran, COBOL, C++, Pascal
  * (Virtual Machine/P-Code languages are similar; they  translate the program into code in intermediate langauge, then execute, e.g., Java and C#)
* interpreted languages:
  * read, and then inerpreted (executed immediately);
  * bash, LISP, Prolog, Smalltalk,...
  * REPL!

<!--vert-->

### Compiled

the cycle of programming in compiled languages, e.g., Pascal:

1. EDIT: Write or modify a program in a file
2. COMPILE: Ask the translate the file to an executable
3. EXECUTE: Execute this executable
4. REPEAT: Until program is perfected

<!--vert-->

### Interpreted

Interpreted languages, including LISP, rely on REPL

1. READ: Read an expression from the input
2. EVAL: Evaluate this expression
3. PRINT: Print the result of the evaluation
4. LOOP: Redo from step 1

<!--vert-->

## REPL in Mini-LISP

like many interpreted languages, a LISP program is an expression:

* all LISP programs are expressions
* all LISP expressions are *S-Expressions*
* the only data structure in LISP is the *S-Expression*
* all functions in LISP are *S-Expressions*
* all parameters in LISP are *S-Expressions*

<!--vert-->

prompt of the interpreter

```text
>
```

feeding expression `(cons t nil)` as input (don't worry about the meaning of this expression for now)

```lisp
(cons t nil)
```

<!--vert-->

feeding meaningless input `!+a`

```lisp
!+a
; Error UNDEFINED on [!+A]
```

the interpreter reads the token `!+a` (it could have been also `x`, `foo` or whatever), interpretes it as an _atom_, tries _evaluate_ this atom, fails and then prints an error message, and loops

---

## Tokens and Lexical Analysis

<!--vert-->

### Line Comments

begin at `;`, continue until end of line.

<!--vert-->

### Six Punctuation Tokens

1. round parenthesis: `(` and `)`
2. square parenthesis: `[` and `]`
3. dot: `.`
4. quote: `'`

<!--vert-->

### Literals

none! Mini-LISP offers no support for integers, reals, strings, boolean, etc.

<!--vert-->

## Atoms of Mini-LISP

(reminiescent of identifiers in other languages)

```lisp
!?!? #@+ a1 1b , && 3.2.7f ++<<>* " $!%
```

a non-empty string of characters drawn from the Mini-LISP alphabet

<!--vert-->

### The Mini-LISP Alphabet

60 printable (i.e., in the range 33-126) ASCII characters:

1. 26 lower case letters (isomoprhic to upper case letters), `a` ... `z`
2. 26 upper case letters, `A` ... `Z`
3. 10 digits, `0` ... `9`
4. 25 punctuation characters

  ```lisp
  ! " # $ % &
  * + , - / :
  < = > ? @ \
  ^ _ ` { | } ~
  ```

<!--vert-->

## Notes

* Mini-LISP supports ASCII; it does not support Unicode
* an atom does not have to begin with a letter
* atom may *not* include any of the 7 special punctuation characters

  ```lisp
  ( ) [ ] . ' ;
  ```

<!--vert-->

the sequence of characgters in an atom is broken by

1. space, new line, tab, etc., or any other any other control ASCII characters, such as `^X` or `DEL`
    * these characters are always ignored
2. the six *token* characters `( ) [ ] . '`
    * these characters are part of the LISP syntax, and are *not* ignored
3. comments, which are sequences of characters that begin at `;` and end in either a `CR` or `LF` character
    * *all* characters in a comments are always ignored, even if they are one of the special token chacracters

<!--vert-->

### Separator characters

space, newlines, and, tabulation characters cannot appear within atoms, but are otherwise ignored.

<!--vert-->

### Upper casing

for historical reasons, just as in Fortran, all letters are upper case.
