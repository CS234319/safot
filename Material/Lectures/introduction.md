# Introduction to C236319 / Programming Languages

---

## Procedural vs. Declarative Study
- *Procedural*: Driving, Swimming, Acting, Literature, History, Bible
- *Declarative*: Street Signs Math, Physics
Study of programming languages:
- No theorems, integration by parts, ...
- Definitions are easy; lots of contents; you cannot simply memorize it
- Lots of fun
- Tools of the trade

---

## New ways of thought
- Productive programmers tend to know more programming languages
  - A real programmer can program in Fortran in any language
- Rich toolbox of programming techniques
- The Sapir Whorf thesis: names of God, Jerusalem, Snow; tenses; Babylon 17, ...
- Classical studies (ancient, dead languages such as Greek and Latin) distill the main ideas
  - Typing
  - Evaluation
  - Functional programming
  - Logic programming
---

## The Four Main Paradigms
- Imperative paradigm
- Functional
- Object oriented
- Logical
---
## A Taste of Lisp
The implementation of a `cond` a lisp function similar to `swhitch`
```Lisp
(defun evaluate-cond(test-forms a-list)
  (cond ((null test-forms) nil) ; if no more test-forms, return nil
        ((evaluate (car (car test-forms)) a-list) ; evaluate condition part of the first test-form
        (evaluate (car (cdr (car test-forms))) a-list)) ; if true, evaluate value part (second part) of the first test-form
        (t (evaluate-cond (cdr test-forms) a-list)))) ; otherwise, recurse on rest of test-forms
```
---

## A Taste of OO
```Smalltalk
1 + 2 * 3 * 0 + a < b
  ifTrue: [^'a is less than b']
  ifFalse: [^'a is greater than or equal to b']
```
---
## A Taste of Prolog
```prolog
% prolog # try to run prolog
The program 'prolog' can be found in the following packages:
 * gprolog
 * swi-prolog-nox
Try: sudo apt-get install <selected package>
% sudo apt-get install # install prolog
[sudo] password for yogi:
 瞎说 
% prolog # invoke the Prolog interpreter from command line
Welcome to SWI-Prolog (Multi-threaded, 瞎说
For help, use ?- help(Topic). or ?- apropos(Word).
?- X == X.
true.

?- X = X.
true.

?- plus(2,2,4).
true.

?- plus(1,1,3).
false.

?- plus(3,X,17).
X = 14.
```

## More of Prolog 


## Let's try it with Pascal 

[Quick Pascal](https://docs.google.com/presentation/d/1n_VQM6HCASj5FINurqF3wusE4fS2qqq_h7AoQvMgXzI/edit?usp=sharing)
---

## Basic terminology
      1. Variable vs. Value vs. Type
      2. Expression vs. command vs. Statement
      3. Definition vs. Declaration
---



 
## Languages covered in this course
You should be able to recognize the main concepts and how they appear in
 - Standard ML: Strong typing + Functional paradigm
 - Lisp/Mini Lisp: Symbolic computation; evaluation 
 - Pascal: Strong typing + procedural
 - Prolog: the logical paradigm
 - Java: the non OO parts
 - AWK, C, Bash, Go, Python... : to the extent presented
---

## Language Analysis Techniques
  1. Group I: Scope and Context
  2. Group II: Execution Model
  3. Group III: Concepts and Names
---


### Group I: Language Scope and Context
  - Vision and Price
  - Paradigm: 
  - Method of language definition: BNF/EBNF/Reference/Legalese 
  - Community: Active? Research only? Experimental? Variations? 
  - Standardization
  - Turing completeness
---


## Language Execution Model
  - Hello World
  - Extent of program
  - Interpreted, P-System or Compiled
  - Where does the program start? How does it end
  - Library vs. pre-defined vs. lockedin 
---


## Concepts and Names
 - Find the concepts: expression, threads, definition, labels,
     declaration, function, reference, traits, labels, macro, command,
     enumeration, procedure, class, type, module, template,
     monads,
 - Are they nameable? Can they be anonymous? Can they have multiple names?
 - named vs. name of names
 - Anonymous vs. nameables
 - Binding
    - Scope vs. environment
---


## Recursive Structures:
 - Recursive relationship among concepts
      - Atomics vs. Compound
      - Constructor and atoms
      - Mutually Recursive
 - The Collateral Confusion
      1. Sequential vs. Collateral Computation
      2. Definition vs. declaration vs. initialization
      3. Sequential vs. Recursive vs. Collateral definition   +/Pas : 3
---

  
