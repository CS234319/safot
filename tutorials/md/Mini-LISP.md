# Mini-LISP
## Lisp: The Mother of All Functional Languages (and Many Others)
If all you know is Pyhon, C, C++, Java, Bash, then Lisp will change the way you think about programming:
- Designed on 1958 (!) but remains influential and in use
- The second programming language ever (preceded only by by FORTRAN)
- The first example of the *functional programming paradigm*
- Conisdered a classic of programming and computer science; every one should know 
   - What are CAR, CDR, and CONS, and how they appear in their favorite language
   - What is LAMBDA, and whether and how it appears in their favorite programming language 
- Standarized implementation: The Huge Common Lisp (CL) Standard
 - Gnu Lisp manual spans over 1,200 pages
 - 

Influential and used to this very day:
- Used for zillion AI/other applications: the first psychatrist, the first symbolic math, Grammarly (contemporary grammar checking in all browsers), Google's flight search, OpusModus (editor for music composition) 
- Used for quick programming of complex algorithms, e.g., alrgorithmic trading
- Influenced many other languages such as
  - Functional Paradigm: ML, Haskell, Scheme, Clojure, Racket, ...
  - Famous, but not functional: JavaScript, R, Perl, Swift, Logo, Ruby, Python, Scala, Julia,  Lua
  - Less famous: Forth, Nim, Dylan, Rebol, Tcl, Io,  ...
 
### Min-Lisp = Cherry Picking of Lisp
*Design Objective*: maximize value/price ratio

Mini-LISP is a programming language designed for students of programming languages: 
- Quick to learn and master. Inappropriate for any serious programming.
- Captures the essence of LISP
- Meticiuluously, purges, eliminates, and/or ignores, anything else!

Don't be mistaken; the language is small; its capabilities are huge:
- As capable as any other langauge (Turing comlete)
- Capable of meta programming; it should be easy to write in Mini-Lisp tools for
  - profiling Mini-Lisp
  - debugging Mini-Lisp
  - program transformation
  - executing programs in Mini-Lisp
 
## Value = Expected Lessons
Expose students to important concepts: 
1. Taste of functional programming paradigm
2. Symbolic computation
3. List processing
4. Recursion
6. Dynamic binding
7. REPL
8. Evaluation
9. Homoiconicity 
10. The Church Rosser property
11. Turing completeness
12. ...

## Price: Learning and Programming

Miniscule language learning effort
1. Syntaxt: trivial
2. Design: slim! only one simple structure
3. Featrues: very few
4. IDE: basic, but can run locally on your browser
5. Tiny library: 8 functions
6. Minimal builtins: 8 in total

Programming in the Small:
1. Useless for large programs
2. No debugger, profiler, etc.
3. No support of integers, reals, strings, files, graphics, ...
4. Not very fast (it is an interpreted language)
5. Reference implementation (in C/C++/Chic) will crash on large programs

## Symbolic Computation
- Numeric computation is computation with numbers
- Numbers are manipulated with the four basic arithmeitcal operations, comparison, etc.
- Symbolic computation is about symbols:
  - Examples of symbols: `a`, `+`, ...
  - Symbols have no intrinsic meaning
  - Meaning of symbols is determined by program
- Allowed operations on symbols:
  - Comparison for equality
  - Assigning meeaning/binding/setting
  - Finding meaning/dereferencing/interpreting
- But, symbols can be organized in data structures...

## Data Structrues of Symbols
LISP == LISt Processing, is all about lists:
- lists of symbols 
- lists of lists of symbols
- lists of mixed kind: symbols and lists of symbols
- Lists of items, each being either a list, or a list of items.

More generally, symbolic computation is also about data structrues containg symbols, e.g., 
- Binary trees whose leaves/nodes/both are symbols
- Trees of any degree whose leaves/nodes/both are symbols
- Graphs whose nodes/edges/both are either symbols or similar graphs
- ...

## Lists in LISP
Empty list:
```
()
```
Singleton list containing the empty list:
```
( () )
```
List containing two empty lists:
```
( () () )
```
More lists:
```
( (()) ())
((() ()) ())
( () ( (()) ()) ((() ()) ()))
```
## Atoms in LISP
Examples:
```
November/2nd <^V>v ? 2x B4 && FOO ! 12 + 
```
- Atoms are case insensitive; `a` is the same as `A`
- Internal representation is always upper case
- Convention: 
   - Input in lower case
   - Output/Internal representation: UPPER CASE
```LISP
> t
T
```
Lists may contain atoms or lists:
```LISP
(A) ; a list containing one atom
(+ 12); a list containing two atoms
(A (B1 () ) ); a list with an atom and a list with an atom and the empty list.
```
- The atom `NIL` is synoymous to the empty list `()`


## The S-Expression Data Structure

### Intution
S-Expression is short for *symbolic expression* 
- Can represent symbols, lists of symbols, lists of lists, etc.
- Easy to manipulate: three elementary operations
- Essentially, a binary tree in which all leaves are symbols

(other languages for symbolic compuations rely on other data structures, e.g., general trees or strings)

### Definition
- **Given**: An alphabet, finite or infinite, of symbols. 
- **Define**: Set of *S-Expression* over the alphabet has two kinds of elements
  1. *Atomic S-Expressions (Atoms)*: Every symbol in the alphabet is an S-expression
  2. *Compound S-Expressions (concstructed S-expressions)*: If 'S1' and 'S2' are S-expressions then, the *dottet pair* of 'S1' and 'S2', written '[S1.S2]' is also an S-Epxression
  3. (Just be sure: Nothing else is an S-Expression)
### Examples over finite alphabet '{a,b,c}'
a, b, [a.b], [a.[b.c]], [[a.b].c], [c.[[a.b].[b.a]]]

## Homoiconicity
### Etymology
- homo="the same" 
- icon="representation"
- Homoiconicity = "the same represenetation". 
A programming langauge P is homoiconic if a program p1 in P, can be manipulated as data by another program p2 in L, or even by p1 iteslf.

Very few examples:
- LISP
- Prolog
- Mathematica (Wolfram's langauge for symbolic mathematical computatio)
- All assembly languages
- R, Tcl, SNOBOL, Julia, XSLT, Rexx, ... (more or less famous languages)
- Turing machine

But not Smalltalk, C++, Java, ML, Scala, Python, and most mainstream programming languages

### Homoiconicity in LISP
- A LISP *program* is just an S-expression
- A LISP *function*
 - takes one parameter, which is an S-expression
 - returns a value, which is an S-expression
 - is itself an S-expression


## Lists vs. S-Expressions
LISP represents lists as S-expressions:
- Every list is an S-expression
- Not every S-expression is a l-list
### First/Rest Recursive Representation of Lists:
#### Recursion base
  The empty list, `()`, is represented by the special atom `NIL`
#### Recursive step
To represent a non-empty list L:
1. Write L as:
   ```
   (F x1 ... xn)
   ```
   where `F` is the first item in the list, and `x1 ... xn` is the, possibly empty, sequence of the remaining items in the list.
2. Let `S1` be the S-expression repesentation of `F`
    - If `F` is an atom, then `S1` is `F`
    - Otherwise, `F` is a list, and `S1` is computed recursively
3. Let `R` be the possibly empty list `(x1 ... xn)`
4. Let `S2` be the the S-expression representation of `R` (computed recursively)
5. The S-expression representation of `L` is the dotted pair ```
  ```
  [S1.S2]
  ```
## The list notation
It is customary to write S-expressions as lists
1. Atom `nil` is written as `()`
2. Atom `a` is written as `A`
3. `[a.nil]` is written as `(A)`
4. `[a.[b.nil]]` is written as `(A B)`
5. `[a.[b.[c.nil]]]` is written as `(A B C)`
6. `[[a.nil].[b.nil]]` is written as `((A) B)`


Not all S-expressions can be fully written with the list notatios 
1. `[a.b]` is written as `[a.b]`
2. `[a.[[b.c].nil]]` is written as `(A [B.C])`

## Operations on S-Expressions (reminiscent of plus/minus on integers)
### CAR
  - obtain the left sub-tree, e.g., CAR of `[[a.b].c]` is `[a.b]` 
  - obtain the first item of a given list, e.g.,  CAR of the two item list `((A) (B C))` is `(A)` 
  - fails on atoms (an empty list is an atom)
  - in other languages/libraries: `head` / `first` / `top` / ...
### CDR
  - obtain the right sub-tree, e.g., CDR of `[a.[b.[c.a]]]` is `[b.[c.a]]`
  - obtain the rest of a given list, i.e., the list without its first element, e.g., CDR of the a three item list `((A) D (B C))` is a two item list `(D (B C))`
  - fails on atoms (an empty list is an atom)
  - in other languages/libraries: `tail` / `rest` / `remainder` / ...
### CONS
  - construct a tree out of a given left and rigt sub-tree, e.g., CONS of `a` and `[b.b]` is `[A.[B.C]]
  - prepend a given item to a given list,  e.g., CONS of `A` and `(B C)` is `(A B C)`

CAR and CDR are historical names; acronyms of registers in an ancient IBM machine on which LISP was first implemented; `CONS` is short of 'construct' or 'constructor'

## Predicates on S-Expressions (reminiscent of numerical comparison)
1. NULL
  - check wheher an S-expression is the special atom `NIL`
  - check whether a list is empty
2. ATOM: check whether an S-Expression is an atom
3. EQ: check if two given symbols are equal
### Failures of computation (reminiscent of division by zero)
- CAR and CDR will fail on atomic S-expressions
- CONS, ATOM and NULL never fail
- EQ also never fails; but note that it returns "false" if any of the compared expressions is not an atom
## "Boolean" atoms
- CAR, CDR, and CONS are (partial) functions from S-expressions to S-expressions
- Let's make EQ and ATOM such functions as well
- Provide: meaning to two special symbols:
  - Atom `nil` represents falsehood
  - Atom `t` represents truth
Given a (finite or f alpahet/aka set of symbols, also called, 'atoms'

## The "Semantics" S-Expressions
The "semantics" of an S-expression, is the result of its "evaluation"; evaluating an S-expression gives another S-expression, unless the evaluation "fails" 
### Semantics of atoms
1. The semantics of atom `nil` is itself, i.e., atom `NIL`
2. The semantics of atom `t` is itself, i.e., atom `T`
3. The semantics of several designated atoms is a function
 1. 8 + 1 atoms designate the primitive functions of Mini-LISP
   - `CAR`, `CDR`, `CONS`, `EQ`, `ATOM`: operators and predicates on S-expressions
   - `SET`, `COND`, `ERROR`: to be explained later
   - `EVAL`: a primitive function that takes an S-expression and returns its semantics, or fails. 
 2. 5 predefined functions:
  - `NULL`: check whether an atom is `NIL`
  - `DEFUN`, `DEFUN'`, `LAMBDA`, `NLAMBDA`: make it posssible to define new functions
  - `QUOTE`: a function that prevents an S-expression from being evaluated  
4. The semantics of any other atom is (initially) undefined; therefore, the evaluation of any other atom fails
### Semantics of dotted-pairs
The semantics of dotted pair `[x.y]`, is the application of function `x` to S-expression `Y`
1. `X` must be a name of a function that takes a certain number of arguments
2. `Y` must be a list of this many arguments
3. Semnatics of `[x.y]` is the invocation of function named `X` on the list of arguments in `Y`
4. Error if the expected number of arguments is different than the actual number of arguments
### Semantics of lists
Semantics of `(f x y)` is the semantics of `[F.(X Y)]`, i.e., the application of function named `F` to the two arguments `X` and `Y`.
-  `(cons t nil)` evaluates to `(T)`
-  `(car (cons t nil))` evaluates to `(CAR (T))` and then to atom `T`
-  `(cdr (cons t nil))` evaluates to `(CDR (T))` and then to the empty list `()` (which is also the atom `NIL`)
-  `(cons nil (cons t nil))` evaluates to `(CONS NIL (T))` and then to the two item list `(NIL T)`
### Two semantics of function application:
1. Eager semantics: arguments are evaluated first, and then passed to function
2. Normal semantics: arguments are passed to the function as is
3. Most functions are eager; exceptions are
  - `ERROR`
  - `COND`
  - `QUOTE`
  - Functions defined with `NDEFUN`

## DETOUR: Compiled vs. Interpreted (and P-Code)
- Compiled languages: translate the program, then execute it
  - Prime examples: Fortran, COBOL, C++, Pascal 
  - (Virtual Machine/P-Code languages are similar; they  translate the program into code in intermediate langauge, then execute, e.g., Java and C#)
- Interpreted languages: 
  - read, and then inerpreted (executed immediately);
  - bash, LISP, Prolog, Smalltalk,...
  - REPL!
## REPL
The cycle of programming in compiled languages, e.g., Pascal:
1. EDIT: Write or modify a program in a file
2. COMPILE: Ask the translate the file to an executable
3. EXECUTE: Execute this executable
4. REPEAT: Until program is perfected

Interpreted languages, including LISP, rely on REPL
1. READ: Read an expression from the input
2. EVAL: Evaluate this expression
3. PRINT: Print the result of the evaluation
4. LOOP: Redo from step 1
## REPL in Mini-LISP
Like many interpreted languages, a LISP program is an expression:
- All LISP programs are expressions
- All LISP expressions are *S-Expressions*
- The only data structure in LISP is the *S-Expression*
- All functions in LISP are *S-Expressions*
- All parameters in LISP are *S-Expressions*
## REPL in Mini-LISP 
Prompt of the interpreter 
```
> 
```
Feeding expression `(cons t nil)` as input (don't worry about meaning of this expression for now) 
```
> (cons t nil)
```
The above expression evaluates to 
Feeding meaningless input `!+a`
```
> !+a
```
The interpreter reads the token `!+a` (it could have been also `x`, `foo` or whatever), interpretes it as an _atom_, tries _evaluate_ this atom, fails and then prints an error message, and loops
```
> !+a
Error UNDEFINED on [!+A]
```
## Tokens and Lexical Analysis
### Line Comments
Begin at `;`, continue until end of line. 
### Six Punctuation Tokens
1. Round parenthesis: `(` and `)` 
2. Square parenthesis: `[` and `]`
3. Dot: `.`
4. Quote: `` ' ``
### Literals
None! Mini-LISP offers no support for integers, reals, strings, boolean, etc.
## Atoms of Mini-LISP
(reminiescent of identifiers in other languages) 
```
!?!? #@+ a1 1b , && 3.2.7f ++<<>* " $!%
```
A non-empty string of characters drawn from the Mini-LISP alphabet 
### The Mini-LISP Alphabet 
60 printable (i.e., in the range 33-126) ASCII characters:
1. 26 lower case letters (isomoprhic to upper case letters), `a` ... `z`
2. 26 upper case letters, `A` ... `Z`
3. 10 digits, `0` ... `Z`
3. 25 punctuation characters
```
! " # $ % & 
* + , - / :
< = > ? @ \ 
^ _ ` { | } ~
```
## Notes
- Mini-LISP supports ASCII; it does not support Unicode
- An atom does not have to begin with a letter
- Atom may *not* include any of the 7 special punctuation characters
``` 
 ( ) [ ] . ' ; 
```
- The sequence of characgters in an atom is broken by
  1. space, new line, tab, etc., or any other any other control ASCII characters, such as `^X` or `DEL`
    - these characters are always ignored
  2. the six *token* characters
    ``` ( ) [ ] . ' ```
    - these characters are part of the LISP syntax, and are *not* ignored
  3. comments, which are sequences of characters that begin at `;` and end in either a `CR` or `LF` character
    - *all* characters in a comments are always ignored, even if they are one of the special token chacracters 
### Regular expression 
```
[a-zA-Z0-9!"#$%&*+,\-/:<=>?@\\\^ _`{|}~]*
```
### Separator characters
Space, newlines, and, tabulation characters cannot appear within atoms, but are otherwise ignored. 
### Upper casing
For historical reasons, 
All other characters are considered space
