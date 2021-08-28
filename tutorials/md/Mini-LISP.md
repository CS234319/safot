ֱ# Mini-LISP
## What?
A programming language designed for students of programming languages: 
- Quick to learn and master. Inappropriate for any serious programming.
- Captures the essence of LISP
- Meticiuluously, purges, eliminate, and/or ignores, anything else
## Why?
Expose students to important concepts: 
1. The functional programming paradigm
2. Symbolic computation
3. Dynamic binding
4. Evaluation
5. Homoiconicity 
6. Turing completeness
7. ...
Minimize language learning effort
1. Minimal syntax
2. Minimal set of features
3. Minimal IDE: can run locally on your browser
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
A non-empty sequence of characters which are all
1. ASCII
2. one of the 95 printable ASCII characters, i.e., characters in the range 32-126.
3. not a space
4. not any one of the 6 punctuation tokens
Regular expression 
```
[-0-9A-Za-z!"#$'*+,/:;M<>=?@\^_`]+
```
### Separators
All other characters are ignored, except that they 
