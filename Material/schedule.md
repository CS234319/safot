# 236319: Winter 2021/22 Schedule

## Week 1 \[24.10-30.10\]

* **Lecture** \[[summary](Lectures/summaries/lecture1.md)\]
    1. [Motivation and Paradigms](Lectures/introduction.md)
    2. [Abstract Introduction](https://docs.google.com/presentation/d/1LKVaPEXuPYzI149K-68XZR-HHv6cJkOWgdBg9T98cog/edit?usp=sharing)
    3. [Quick Pascal](https://docs.google.com/presentation/d/1n_VQM6HCASj5FINurqF3wusE4fS2qqq_h7AoQvMgXzI/edit?usp=sharing)
* **Tutorial** \[[summary](Tutorials/summaries/1.md)\]
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

* **Lecture**
    1. [Types](Lectures/slides/chapter-3.pdf)
* **Tutorial**
    1. [ML - Lists](Tutorials/sml/lists.md) --- [pdf-article](Tutorials/pdfs/articles/sml/lists.pdf) --- [pdf-slides](Tutorials/pdfs/slides/sml/lists.pdf)
* **Workshop**
    1. [ML - workshop](Tutorials/sml/errors.md) --- [pdf-article](Tutorials/pdfs/articles/sml/errors.pdf)
* **Optional Reading**
    1. [Summary of Polymorphism](https://drive.google.com/file/d/0B3645jTHku6WeDF0MlpIUDh4Zlk/view?usp=sharing&resourcekey=0-fiLhA6npEgrkLQ7p4-sydQ)
* **Submission**: [HW1](https://docs.google.com/document/d/1SH2WwvPzrA8hcORU0aM4JIJbc_irVmN0dy1BavYUTQM/edit?usp=sharing) \[13.11 23:59\]
* **HW**: [HW2](???) is published \[13.11\]
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

* **Lecture**
    1. [Advanced Typing](Lectures/slides/chapter-4.pdf)
    2. [ML's Type System](Tutorials/theory/sml-type-system.md)
* **Tutorial**
    1. [ML - Modules](Tutorials/sml/modules.md) --- [pdf-article](Tutorials/pdfs/articles/sml/modules.pdf) --- [pdf-slides](Tutorials/pdfs/slides/sml/modules.pdf)
    2. [ML - Exceptions](Tutorials/sml/exceptions.md) --- [pdf-article](Tutorials/pdfs/articles/sml/exceptions.pdf) --- [pdf-slides](Tutorials/pdfs/slides/sml/exceptions.pdf)
    3. [ML - References](Tutorials/sml/refs.md) --- [pdf-article](Tutorials/pdfs/articles/sml/refs.pdf) --- [pdf-slides](Tutorials/pdfs/slides/sml/refs.pdf)
    4. [Classification of Type Systems](Tutorials/theory/type-system-classification.md) --- [pdf-article](Tutorials/pdfs/articles/theory/type-system-classification.pdf) --- [pdf-slides](Tutorials/pdfs/slides/theory/type-system-classification.pdf)

## Week 5 \[21.11-27.11\]

* **Lecture**
    1. [State and Storage](Lectures/slides/chapter-5.pdf)
* **Tutorial**
    1. [ML - Sequences](Tutorials/sml/sequences.md)
* **Submission**: [HW2](???) \[27.11 23:59\]
* **HW**: [HW3](???) is published \[27.11\]

## Week 6 \[5.12-11.12\]

* **Lecture**
    1. [Symbolic Values and Pure Lisp](???)
* **Tutorial**
    1. [Automatic Memory Management](Tutorials/theory/automatic-memory-management.md)
    2. [RTTI](Tutorials/theory/rtti.md)
    3. [Lexical Analysis and ASTs](Tutorials/theory/lexical-analysis.md)

## Week 7 \[12.12-18.12\]

* **Lecture**
    1. [Symbolic Values and Pure Lisp (Cont.)](???)
* **Tutorial**
    1. [mini-lisp](Tutorials/theory/mini-lisp.md)
* **Submission**: [HW3](???) \[18.12 23:59\]
* **HW**: [HW4](???) is published \[18.12\]

## Week 8 \[19.12-25.12\]

* **Lecture**
    1. [Prolog](???)
* **Tutorial**
    1. [Prolog - Introduction](Tutorials/prolog/introduction.md)

## Week 9 \[26.12-1.1\]

* **Lecture**
    1. [Commands](Lectures/slides/chapter-6.pdf)
* **Tutorial**
    1. [Prolog - Lists](Tutorials/prolog/lists.md)
    2. [Prolog - CLP(FD)](Tutorials/prolog/clp.md)
* **Submission**: [HW4](???) \[1.1 23:59\]
* **HW**: [HW5](???) is published \[1.1\]

## Week 10 \[2.1-8.1\]

* **Lecture**
    1. [Commands (Cont.)](Lectures/slides/chapter-6.pdf)
* **Tutorial**
    1. [Prolog - Higher Order Programming](Tutorials/prolog/higher-order.md)
    2. [Prolog - Exam Questions](Tutorials/prolog/exam-questions.md)

## Week 11 \[9.1-15.11\]

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
   1. [Exam Questions](???)
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
