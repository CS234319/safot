# 236319: Winter 2021/22 Schedule

* [week 1](#week-1-2410-3010)
* [week 2](#week-2-3110-611)
* [week 3](#week-3-711-1311)
* [week 4](#week-4-1411-2011)
* [week 5](#week-5-2111-2711)
* [week 6](#week-6-512-1112)
* [week 7](#week-7-1212-1812)
* [week 8](#week-8-1912-2512)
* [week 9](#week-9-2612-11)
* [week 10](#week-10-21-81)
* [week 11](#week-11-91-1511)
* [week 12](#week-12-161-221)
* [week 13](#week-13-231-291)

## Week 1 \[24.10-30.10\]

* **Lecture**
    1. [Motivation and Paradigms](Lectures/introduction.md)
    2. [Abstract Introduction](https://docs.google.com/presentation/d/1LKVaPEXuPYzI149K-68XZR-HHv6cJkOWgdBg9T98cog/edit?usp=sharing)
    3. [Quick Pascal](https://docs.google.com/presentation/d/1n_VQM6HCASj5FINurqF3wusE4fS2qqq_h7AoQvMgXzI/edit?usp=sharing)
* **Tutorial**
    1. [ML - Introduction](Tutorials/sml/introduction.md) --- [pdf-article](Tutorials/pdfs/articles/sml/introduction.pdf) --- [pdf-slides](Tutorials/pdfs/slides/sml/introduction.pdf)
    2. [ML - Functions](Tutorials/sml/functions.md) --- [pdf-article](Tutorials/pdfs/articles/sml/functions.pdf) --- [pdf-slides](Tutorials/pdfs/slides/sml/functions.pdf)
* **Reading**
    1. [Summary of first lecture: chapters 1-2](https://docs.google.com/document/d/1LNSWwi2VYPrOcNPdQ3YvXhFfZtg_r4D6SH9adcFAIK4/edit?usp=sharing)
    2. [Specification of Pascal 72](Misc/PascalReport.pdf)
* **Reference**
    1. [Summary of Standard ML (Hebrew)](https://drive.google.com/file/d/0B3645jTHku6WZm4zeEJxSzRTMU0/view?usp=sharing&resourcekey=0-bLE_IX7sWV2H21phV4i6Vw)
    2. [Programming in Standard ML](https://drive.google.com/file/d/0B8_AnUZwVFgoTEpaM1VOWXY5NWs/view?usp=sharing&resourcekey=0-wsdSa5CtgDEwdDZZ4KNY6w)
    3. [Programming in Standard ML ’97: A Tutorial Introduction](http://www.lfcs.inf.ed.ac.uk/reports/97/ECS-LFCS-97-364/ECS-LFCS-97-364.pdf)
* **Prerequisites terms**
    1. Regular expressions
    2. Context free grammars
    3. Bakus Naur Form (BNF) and Extended  BNF.
    4. Recursive definitions and structural induction
* **HW**: [HW1](https://docs.google.com/document/d/1SH2WwvPzrA8hcORU0aM4JIJbc_irVmN0dy1BavYUTQM/edit?usp=sharing) is published \[30.10\]

* **Highlights of Lecture**

  Today's lecture started with technical problems, and time was taken to reiterate formalities, grading policy, bonus assignments, and the recycled questions promise. The four main paradigms: functional, object-oriented, imperative, and logic based, were discussed. The four main programming languages used in the course are Prolog, Pascal, ML, and Lisp.

  * In response to students' request, we discussed the issue of a programming language being universal; see these [notes](Misc/univrsal.pdf)

  * Other terms discussed: variable != value; name != named;  anonymous entities anonymous variables; nested functions; anonymous types with struct` in C; builtin != predefined != reserved identifier; recursive structure; atomic != compound

  * The semicolon in Pascal issue was discussed:
    * Separatist grammar: ';' is a command separator, e.g., items in an SML record
    * Lenient separatist grammar: ';' is a command separator, but there is also an empty command, e.g., Pascal
    * Terminist grammar: ';' terminates commands
    * Separatist terminist grammar: ';' separates commands, is optional at end (almost the same as lenient separatist)
    * Lenient grammar: as found in Python, ';' can be omitted at eoln
    * Go's grammar: ';' is automatically omitted at eol
    * SML's grammar: ';' is optional at the end of "commands"

## Week 2 \[31.10-6.11\]

* **Lecture**
    1. [Quick Pascal (Cont.)](https://docs.google.com/presentation/d/1n_VQM6HCASj5FINurqF3wusE4fS2qqq_h7AoQvMgXzI/edit?usp=sharing)
* **Tutorial**
    1. [ML - Declarations](Tutorials/sml/declarations.md) --- [pdf-article](Tutorials/pdfs/articles/sml/declarations.pdf) --- [pdf-slides](Tutorials/pdfs/slides/sml/declarations.pdf)
    2. [ML - Datatypes](Tutorials/sml/datatypes.md) --- [pdf-article](Tutorials/pdfs/articles/sml/datatypes.pdf) --- [pdf-slides](Tutorials/pdfs/slides/sml/datatypes.pdf)
* **Reading**
    1. [Summary of first lecture: chapter 3](https://docs.google.com/document/d/1LNSWwi2VYPrOcNPdQ3YvXhFfZtg_r4D6SH9adcFAIK4/edit?usp=sharing)

## Week 3 \[7.11-13.11\]

* **Lecture** (see summary below)
* **Tutorial**
    1. [ML - Lists](Tutorials/sml/lists.md) --- [pdf-article](Tutorials/pdfs/articles/sml/lists.pdf) --- [pdf-slides](Tutorials/pdfs/slides/sml/lists.pdf)
* **Workshop**
    1. [ML - workshop](Tutorials/sml/errors.md) --- [pdf-article](Tutorials/pdfs/articles/sml/errors.pdf)
* **Submission**: [HW1](https://docs.google.com/document/d/1SH2WwvPzrA8hcORU0aM4JIJbc_irVmN0dy1BavYUTQM/edit?usp=sharing) \[13.11 23:59\]
* **HW**: [HW2](https://docs.google.com/document/d/1m7_gqrUY_r3zGYKbNkJFUOc4EVaHn_UyaKfndIQCjZA/edit?usp=sharing) is published \[13.11\]
* **Highlights of Lecture**

  Recursion of concepts and their definitons in Pascal.
  * Program is defined by definitions, procedures, functions, and commands.
  * Functions and procedures are mutually recursive: functions can contain procedures, and procedures can contain functions.
  * Expressions are defined inductively: atomic expressions are literals, or variable references,   while constructors are function calls and operators.
  * Commands may include expressions and other commands.
  * Definitions: each may refer to its precursors; only sensible order is label, const, type, var.

  Recursion of concepts and their definitions in SML: Declatations and Expressions

  * Values: those thing passed as arguments, or returned from functions
    * Atomic values: reference to a named value by its name, atomic values of atomic types, integer, real, etc.
    * Compound values: tuples, etc.
    * Recursive values: disallowed, except for recursive functions.
    * Opaque values: values which cannot be broken further, e.g., functions in SML
  * Expressions: recipe for producing values
    * Atomic expressions: literal, name
    * Evaluating an expression: apply the recipe to produce values.
  * Names:
    * Two kinds of names:
      * Alphabetic: few reserved keywords (and, of, val, fun, fn...); all the rest are free or predefined (including int, true, ...)
      * Symbolic (Punctuation): few reserved identifiers ( "|",  ",", ".", etc.);  all the
        rest are free or predefined (including ">", "+", "`",, ...)
    * Two namespaces: a name has distinct meaning (no meaning) in both namespaces.
      * values (including function names, constructors, and field names marked with #)
      * types  
  * Declaration: are mostly binding of a name to a value,
    * value is denoted by an expression
    * expression is evaluated to produce value.
    * Thus declaration may refer to expressions
  * Expressions can be also composed from declarations, using `let`...`in`...`end`
  * Declarations can be also composed from declarations using `local`...`in`...`end`
  * Types: are also defined inductively, from atomic types and type constructors
  * Declarations can also bind names to types (in the type name space)
  * Deferred execution: expressions that follow `=>`, or `fun ... =` are not evaluated immediatley. The recipe of their evaluation is recorded and encapsualted as an opaque value.

  Summary:

  * Types:
    * Atomic/Compound: Are constructed from other smaller types.
    * Can be mutually/self recursive, using `datataype` and `and`
  * Expressions:
    * Atomic/Compound: Are constructed from other smaller expressions.
    * Are not mutually/self recursive
  * Values:
    * Atomic/Compound: Are constructed from other smaller expressions.
    * Cannot be recursive, except for mutually recursive functions.

  Exercise: do the same summary for Pascal.

  Perspective on ML:

  * Essentially, a dying language
  * Daughter languages: OCaml and Haskell, but also Kotlin are more successful
  * Very clean and elegant
  * Foundation of the Hindley-Milner type inference algorithm:
    * Given: a structure of nested declarations and expressions
    * Determine: the most general type for this structure.
    * HM Algorithm: Doubly exponential, but guaranteed to terminate. Not true for Java/C++.

  Classification of PL based on their values:

  * Machine values: int/real/boolean/...
  * Abstract, programmatic values: function, generator, co-routine
  * Symbolic values: A value is symbolic if the only operation that can be done on it is comparison for equality.

  Symbolic languages: languages whose atomic values are symbols; the only interesting feature then is the structure by which these symbols are organized:

  * Formal languages over alphabet of symbols (letters); languages such as bash and Snobol
  * Prolog (Course version): Abstract trees, given a signature, construct all trees whose labels are drawn from a signature, +  
  * Abstract terms, same as trees, but allowing leaves to contain variables
  * Cyclic/rational trees/terms (modern version): trees with cycles which expand to infinite trees
  * HM-Algorithm is related to operations on such trees
  * List of lists / generalized trees as in Mathematica.

  S-Expression:

  * Generalizes them all.
  * Car/Cons/Cdr
  * eq/atom

## Week 4 \[14.11-20.11\]

* **Lecture** (see summary below)
* **Tutorial**
    1. [ML - Modules](Tutorials/sml/modules.md) --- [pdf-article](Tutorials/pdfs/articles/sml/modules.pdf) --- [pdf-slides](Tutorials/pdfs/slides/sml/modules.pdf)
    2. [ML - Exceptions](Tutorials/sml/exceptions.md) --- [pdf-article](Tutorials/pdfs/articles/sml/exceptions.pdf) --- [pdf-slides](Tutorials/pdfs/slides/sml/exceptions.pdf)
    3. [ML - References](Tutorials/sml/refs.md) --- [pdf-article](Tutorials/pdfs/articles/sml/refs.pdf) --- [pdf-slides](Tutorials/pdfs/slides/sml/refs.pdf)
    4. [Classification of Type Systems](Tutorials/theory/type-system-classification.md) --- [pdf-article](Tutorials/pdfs/articles/theory/type-system-classification.pdf) --- [pdf-slides](Tutorials/pdfs/slides/theory/type-system-classification.pdf)

### Summary

S-Expressions: full binary trees, in which leaves, and only leaves, carry symbolic tag, drawn from some alphabet. 
*  Textual notation as dotted pairs and square brackets: 
 `a`, `nil`, `[a.n]`, `[a.[a.n]]`, etc.
* SML Definition
    
    ```sml (* Recursive structure: Expressions over alphabet *)
    datatype 'Alphabet Sx =
             Pair of Sx * Sx 
        |    Atom of 'Alphabet

    (* Let the alphabet of atoms be all strings *)
    type Sx = string Sx 

* Atomic values
    ```sml
    fun ` s = Atom s
    val a = `"a"
    val b = `"b"
* Compound values
    ```sml fun cons x = Pair x
    val it = let
       val s1 = cons (a,b)
       val s2 = cons (b,a)
       val s3 = cons(s1,a)
       val s4 = cons(s2,b)
    in
        cons(s3,s4)
    end 
    ```

#### Partial functions: 
```sml 
    fun car (Pair(result,_)) = result
    fun cdr (Pair(_,result)) = result

    val it = car (cons(a,b))
    val it = car `a (*Runtime error*)
    val it = cdr (cons(a,b))
    val it = car `a (*Runtime error*)
```

#### Predicates (full functions)
* Test for atomicity
```sml
 fun atom x = case x of 
        Atom _  => true 
      |      _  => false
 ```
* Equality of atoms and atoms only
```sml
 fun eq x = case x of 
        (Atom(s1),Atom(s2)) => s1 = s2 
    |   _                   => false

 ```

#### S-Expessions and Lisp
* Lisp is an intepreted (essentially) untyped programming language
    - All values are S-Expessions
    - Every function is an S-Expression
    - Every S-Expression is a funtion (often partial functions)

We need a bit of introduction before hands on with Lisp.

* Designated atoms: used for predicates, since Lisp has no Bolean types
    - `NIL` denotes end of lists, false, etc.
    - `T` denotes the "absolute" truth
        - any S-expressions  which is not `NIL` is considered true.
* The List Notation (l1 l2 ... ln)
    - `()` the empty list, aka `NIL`
    - `(X)` a list containing `X`, aka `[X.NIL]`
    - `(X Y )` a list containing `X`, aka `[X.[Y.NIL]]`
* Lists of Lists
    - The dotted pair notation is rarely used and may be ambigous if employs round brackets.
    - Nested lists are allowed `((A X Y) (B C) (((E)))))`
    - Every list of lists can be represented as an S-Expression
    - Not every S-expression can be represented as list of lists, e.g., `[A.B]`
* Lists of Lists in SML
```sml 
    datatype 'Alphabet List'of'Lists =
             list of 'Alphabet List'of'Lists list
        |    item of 'Alphabet
```
List of lists is essentially a tree of unbounded degree, in which each only leaves carry leabels.
* Semantics of lists of lists: evaluation as expressions:
    - `()` evaluates to `NIL`
    - `a` an item which is an atom `a` evaluates to the "meaning" of `a`
        - initially no atom has meaning
        - for technical reasons
            - the meaning of `NIL` is `NIL` and the meaning of `T` is `T`
            - not an essential requirement 
        - 
    - `(g)` invoke 0-parameter function `g` with no arguments
    - `(f a b)`  invoke 2-parameter function f with arguments a and b
    - `(f (f a b) (f c d))`  invoke f on a and b, then on c and d, and then on the result of the previous two applications 
    - `((g) h)` invoke 0-parameter function `g` with no arguments; use the result of the application as a function to apply to `h`

* The list notation for experssions
    - Lisp with symbolic values only (mini-lisp): Atoms are unbreaksable strings
    - Common Lisp: 
        - Atoms can be inegers, reals, characters,...
        - Predefined functions
    - Examples:
        - `(* (+ 2 3) (+ 5 6))`
        - `(cons (car x) (cdr (cdr x)))` 
            - `x` can be an atom with some meaning...
            - replace `x` with something such as `( () () ( () (()) ) )`?
                - Will not work, `(() ())` cannot be evaluated, since `NIL` is not a function and cannot be applied to `NIL`

##### Lisp REPL: live demo
- the function `quote`
- the single quote ' notation
- function `set`
- function `defun`

#### Type System
- Typically, in non-symbolic computation
    - Simple type systems in Pascal, SML, C
    - Challenge: Type system to support values such as functions, instances of classes, closures, inheritance.
- Partition the set of possible values into sets, aka types.
- A type is a:
    - Set of values 
    - Set of values that behave similiarly under the same operations.
- #values in type: type be empty, singleton, two or any finite number of values, or infinite
- #types for value: 
    - often, only one `true` in Pascal
    - sometimes infinite: `0` in C
    - somtimes finite: `1` in C
    - sometimes has one "principal type", or "most general type"
        - type from which all other types of a value can be derived.
        - Hindley Milner algorithm finds this type in SML and all tis daughter
- Signficance of type:
    - Determine which operations are allowed and which are not
        - The "evil" rice theorem
    - Interprestation of representation:
        - the same 8 bits can be interprested as 
            - integer
            - unsigned integer
            - index to a table (ASCII table?)
            - truth or false
        - Type punning; unintended interpretation of bits, e.g., union, address arithmicetic. Impossible in ML, Java; easy in Pascal (variant records) and super tempting in C (`union`, address arithmetics, casting)
    - Overloading: for example, Julia

#### The  Basics of Type System (type system of mock)
- Atomic types: int, real, ..., 
- Type constructors: record, tuple,
- Type rules: when are two types the same? how types are enforced? etc.

#### The Essential Type Constructors:
- Tuple: denoted by '*' #(T1*T2) = #T1 * #T2
    - Needs constructors and "de-" cosntructors.
    - Is n=2, or is n=any?
    - Associative? Commutative? Idempotent?
    - if n is zero, then the unit type
- The unit type: void in C.
- The power set: denoted by '2^' #(2^T) = 2^(#T1)
    - nice but rare
- The map type denoted by '->' #(T1->T2) = #T2 ^ #T2
    - A map can full or partial.
    - A map can be represented by a table or by code (function)
    - Both table and function maps may be partial
- Map and Tuple are just like the Times and Power.
    - `x^(a * b) = ((x ^b)^a)
    - (a*b)->x = a->b->x
- Branding: given a lable L and a type T, then `L of T` is a type similar to `T` bugt having a different name. (this is not type aliasing) 
- Record: given types T1...Tn and labels L1...Ln
    - Similar to tuple of branded types
- UNION: No such type constructor...
- Disjoint union: denoted sometimes by `+`
    - given T1 and T2, assume that they are disjoint. If not make them disjoint
    - type is union 
    - Found in SML and duaghters, approximated by other languages
    - Associative? Commutative? Idempotent? Arity?
- Empty type: neutral element of disjoint union
    - has no values
    - cannot be found in SML
    - similar to exceptions


#### Recursive type equations
- For lists, trees, ...
- Often mutually recursive, e.g., 
    - Expression = sum of Products
    - Product = product of Terms
    - Term = ...


    SML Example
    ```
    datatype 
       corner = corner  of rectangle * rectangle * rectangle * rectangle
    and
        rectangle= rectangle of corner * corner * corner * corner
    ```

    ```
    datatype 
        Program = program of Definitions*Inners*Block
    and
        Inners = innes of Routine list
    and 
        Routine = function of Function | procedure of Procedure
    and
        Function = function of Definitions*Inners*Block
    and 
        Procedure = Procedure of Definitions*Inners*Block
    and 
        Definitions = definitions of Labels * Constants * Types * Variables
    and 
        block = block of statement list
    and
        statement = variable * expression
    
    ```

Solving recursive type equations:
    - bottom up approach
    - not always possible

## Week 5 \[21.11-27.11\]

* **Lecture**
    1. [Types](Tutorials/theory/sml-type-system.md) --- [pdf-slides](Tutorials/pdfs/slides/theory/sml-type-system.pdf)
* **Tutorial**
    1. [ML - Sequences](Tutorials/sml/sequences.md) --- [pdf-article](Tutorials/pdfs/articles/sml/sequences.pdf) --- [pdf-slides](Tutorials/pdfs/slides/sml/sequences.pdf)
* **Submission**: [HW2](https://docs.google.com/document/d/1m7_gqrUY_r3zGYKbNkJFUOc4EVaHn_UyaKfndIQCjZA/edit?usp=sharing) \[27.11 23:59\]
* **HW**: [HW3](https://docs.google.com/document/d/1ILdKh0F0A21O2e8EC2_uFlft2KtHNbTLKMc3uO_4hDI/edit?usp=sharing) is published \[29.11\]

## Week 6 \[5.12-11.12\]

* **Lecture**
    1. TBD
* **Tutorial**
    1. [mini-lisp](Tutorials/theory/mini-lisp.md)

## Week 7 \[12.12-18.12\]

* **Lecture**
    1. TBD
* **Tutorial**
    1. [Prolog - Introduction](Tutorials/prolog/introduction.md) --- [pdf-slides](https://github.com/CS234319/safot/blob/master/Material/Tutorials/pdfs/slides/prolog/introduction.pdf)
* **Submission**: [HW3](https://docs.google.com/document/d/1ILdKh0F0A21O2e8EC2_uFlft2KtHNbTLKMc3uO_4hDI/edit?usp=sharing) \[18.12 23:59\]
* **HW**: [HW4](???) is published \[18.12\]

## Week 8 \[19.12-25.12\]

* **Lecture**
    1. [Elad's lecture](Tutorials/pdfs/slides/theory/rehearsal-lecture.pdf)
* **Tutorial**
    1. [Prolog - Lists](Tutorials/prolog/lists.md)
    2. [Prolog - CLP(FD)](Tutorials/prolog/clp.md)

## Week 9 \[26.12-1.1\]

* **Lecture**
    1. TBD
* **Tutorial**
    1. [Prolog - Control Predicates](Tutorials/prolog/control.md)
    2. [Prolog - Exam Questions](Tutorials/prolog/exam-questions.md)
* **Submission**: [HW4](???) \[1.1 23:59\]
* **HW**: [HW5](???) is published \[1.1\]

## Week 10 \[2.1-8.1\]

* **Lecture**
    1. TBD
* **Tutorial**
    1. [MiniLisp](Tutorials/minilisp/eval.pdf)

## Week 11 \[9.1-15.1\]

* **Lecture**
    1. [Advanced Constructs - Evaluation Strategies](Lectures/slides/chapter-7.pdf)
* **Tutorial**
    1. TBD
* **Submission**: [HW5](???) \[15.11 23:59\]
* **HW**: [HW6](???) is published \[15.11\]

## Week 12 \[16.1-22.1\]

* **Lecture**
    1. [Advanced Constructs - Closures](Lectures/slides/chapter-7.pdf)
    2. [Advanced Constructs - Beyond Closures](Lectures/slides/chapter-7.pdf)
* **Tutorial**
    1. [Lexical and Dynamic Scoping](Tutorials/theory/scoping.md)
    2. [Python Generators](Tutorials/python/generators.md)
    3. TBD

## Week 13 \[23.1-29.1\]

* **Lecture**
    1. [Real Life Programming Languages](https://docs.google.com/presentation/d/1FGUzbhURUqzL3hfzCj8m3nR1swqmpG8CYu77H4Tgm5U/edit#slide=id.gb50064ae0_0_89)
* **Tutorial**
    1. TBD
* **Reading material**
* **Submission**: [HW6](???) \[29.1 23:59\]

## Extra curricular

1. Hello world 1.3
2. History of programming languages: 2.3
3. Syntax notation: regexp, bnf, ebnf
4. Type constructors of Mock 3.3
5. Atomic types: 3.5
6. Type constructors in actual languages self read: 3.4
7. Kinds of Arrays 5.2 dead; array representation live.
8. Exceptions 6.9 abbreviated
9. Parallel execution OCCAM pigsty
