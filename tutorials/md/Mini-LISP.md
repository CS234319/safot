ֱ# Mini-LISP
## What?
LISP is very important:
- The first example of functional programming
- Conisdered a classic of programming and computer science
- Implemntation is by a (huge) standard: common Lisp.
### Educational Purpose
Mini-LISP is a programming language designed for students of programming languages: 
- Quick to learn and master. Inappropriate for any serious programming.
- Captures the essence of LISP
- Meticiuluously, purges, eliminates, and/or ignores, anything else!
Don't be mistaken; the language is small; its capabilities are huge:
- Capable of carrying out any possible computation
- Can do meta programming:
  - profiling
  - debugging
  - program transformation
  - language can be interpreted 
## Why?
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
## How?
Miniscule language learning effort
1. Syntaxt: trivial
2. Design: slim! only one simple structure
3. Featrues: very few
4. IDE: basic, but can run locally on your browser
5. Tiny library: 8 functions
6. Minimal builtins: 8 in total 
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
## The S-Expression Data Structure
S-Expression is short for *symbolic expression* 
- Can represent symbols, lists of symbols, lists of lists, etc.
- Easy to manipulate: three basic operations
### Intuition
Binary tree in which all leaves are symbols
### Definition
- **Given**: An alphabet, finite or infinite, of symbols. 
- **Define**: Set of *S-Expression* over the alphabet
  1. Atomic S-Expressions (Atoms): Every symbol in the alphabet is an S-expression
  2. Compound S-Expression (concstructed S-expressions): If 'S1' and 'S2' are S-expressions then, the *dottet pair* of 'S1' and 'S2', written '[S1.S2]' is also an S-Epxression
  3. (Just be sure: Nothing else is an S-Expression)
### Examples over finite alphabet '{a,b,c}'
a, b, [a.b], [a.[b.c]], [[a.b].c], [c.[[a.b].[b.a]]]
### S-Expression in LISP

ֱ### Operations on S-Expressions (reminiscent of plus/minus on integers)
1. CAR: obtain the left sub-tree, e.g., car([[a.b].c]) = [a.b] 
2. CDR: obtain the right sub-tree, e.g., cdr([a.[b.[c.a]]]) = [b.[c.a]] |
3. CONS: construct a tree out of a given left and rigt sub-tree
CAR and CDR are historical names; acronyms of registers in an ancient IBM machine on which LISP was first implemented. 
### Predicates on S-Expressions (reminiscent of numerical comparison)
1. ATOM: check whether an S-Expression is an atom
2. EQ: check if two given symbols are equal
### Failures of computation (reminiscent of division by zero)
- CAR and CDR will fail on atomic S-expressions
- CONS never fails
- ATOM never fails
- EQ never fails; it returns "false" if any of the compared expressions is not an atom
### "Boolean" atoms
- CAR, CDR, and CONS are (partial) functions from S-expressions to S-expressions
- Let's make EQ and ATOM such functions as well
- Let's give meaning to two special symbols:
  - Let Atom `nil` represents falsefullness
  
Given a (finite or f alpahet/aka set of symbols, also called, 'atoms'

## DETOUR: Compiled vs. Interpreted (and P-Code)
- Compiled languages: translate the program, then execute it
  - Prime examples: Fortran, COBOL, C++, Pascal 
  - (Virtual Machine/P-Code languages are similar; they  translate the program into code in intermediate langauge, then execute, e.g., Java and C#)
- Interpreted languages: 
  - read, and then inerpreted (executed immediately);
  - bash, AWK, LISP, Prolog, Smalltalk
  - REPL!
## REPL
The cycle of programming in compiled languages, e.g., Pascal:
1. EDIT: Write or modify a program in a file
2. COMPILE: Ask the translate the file to an executable
3. EXECUTE: Execute this executable
Interpreted languages, including LISP, rely on REPL=
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
``
The interpreter reads the token `!+a` (it could have been also `x`, `foo` or whatever), interpretes it as an _atom_, tries _evaluate_ this atom, fails and then prints an error message, and loops Feeding meaningless `!+a`
```
> !+a
```
## Tokens and Lexical Analysis
### Line Comments
Begin at `;`, continue until end of line. 
### Six Punctuation Tokens
1. Round parenthesis: `(` and `)` 
2. Square parenthesis: `[` and `]`
3. Dot: `.`
4. Backquote: `` ` ``
### Literals
None! Mini-LISP offers no support for integers, reals, strings, boolean, etc.
### Atoms (reminiescent of identifiers in other languages)
Examples: 
```
!?!? #@+ a1 1b , && 3.2.7f ++<<>* " $!%
```
A non-empty sequence of printable ASCII characters, i.e., characters in the range 32-126.
1. Lower case letters
2. Upper case letters
3. All punctuation characters, except for the six puntuation tokens `(`, ')'), '[', ']', '.`
4. not any one of the 6 punctuation tokens
Regular expression 
```
[-0-9A-Za-z!"#$'*+,/:;M<>=?@\^_`]+
```
### Separator characters
Space, newlines, and, tabulation characters cannot appear within atoms, but are otherwise ignored. 
### Upper casing
For historical reasons, 
All other characters are considered space
