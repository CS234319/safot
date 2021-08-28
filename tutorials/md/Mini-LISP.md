ֱ# Mini-LISP
## What?
A programming language designed for students of programming languages: 
- Quick to learn and master. Inappropriate for any serious programming.
- Captures the essence of LISP
- Meticiuluously, purges, eliminates, and/or ignores, anything else!

Don't be mistaken; the language is small; its capabilities are huge:
- Capable of carrying out any possible computation
- Can do meta programming:
  - profiling
  - debugging
  - program transformation
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
6. Minimal builtins: 8 in total, 
## REPL
The cycle of programming in compiled languages, e.g., Pascal:
1. EDIT: Write or modify a program in a file
2. COMPILE: Ask the translate the file to an executable
3. EXECUTE: Execute this executable
Interpreted languages, including LISP, rely on
1. READ: Read an expression from the input
2. EVAL: Evaluate this expression
3. PRINT: Print the result of the evaluation
4. LOOP: Redo from step 1
No separate compilation phase
## Example
Prompt of the interpreter 
```
> 
```
Feeding atom `a
Prompt of the interpreter 
```
> A
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
