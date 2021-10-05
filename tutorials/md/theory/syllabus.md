# Syllabus

### W1-3 Introduction: 5L 0T
1. Motivation + Paradigms: 1L
2. Quick Pascal: 2L
   1. Recursive set of expressions
   2. Recursive set of statements, defined based on statements
   3. Recursive set of types
   4. Mutual recursion in nesting of procedures and functions
   5. Names, predefined, nesting
3. Principles: 0L
   1. Recursive Structures:
      - Atomics vs. Compound
      - Constructor and atoms
      - Mutually Recursive
   2. Names
      - named vs. name of names
      - binding
      - Scope vs. environment
      - Anonymous vs. nameables
   3. Basic terminology
      1. Variable vs. Value vs. Type
      2. Expression vs. command vs. Statement
      3. Definition vs. Declaration
   4. The Collateral Confusion
      1. Sequential vs. Collateral Computation
      2. Definition vs. declaration vs. initialization
      3. Sequential vs. Recursive vs. Collateral definition   +/Pas : 3
4. Language Analysis Techniques
   1. Language Scope:
      - Vision and Price
      - Paradigm
      - Method of language definition 
   2. Execution
      - Hello World
      - Extent of program
      - Interpreted, P-System or Compiled
      - Where does the program start? How does it end
      - Library vs. predefined vs. lockedin 
   3. Concepts and names
       - Find the concepts: expression, threads, definition, labels,
         declaration, function, reference, traits, labels, macro, command,
         enumeration, procedure, class, type, module, template,
         monads,
       - Recursive relationship among concepts
       - Are they nameable? can they be anonymous? can they have
       multiple names?
5. **Values**: what values can the language manipulate? how close are they to the machine?
      1. Symbolic values:
          1. Strings: e.g., icon and Snobol
          2. S-Expression, e.g., the lisp family
          3. Trees, e.g., the lisp family
          4. Terms, e.g., Prolog
      2. Non symbolic values (will study with types)
          1. Primitive values; Virtual machine values, integers, points, colors, lines,
          2. Values composition
      3. Programmatic values:
          - functions aka closures aka labmda expressions
          - function objects such as iterators
          - co-routines
          - continuation
6. Survey of other techniques
    1. Lexical analysis
    2. Type system
    3. Evaluation method
    4. Memory model (if any)
    5. Commands


 

### W3-5 Types 5L 1T
1. Type systems: Constructors and atomic types
2. Atomic types and mapping to hardware
3. Classification
4. Polymorphism
5. Structural vs nominal typing
6. ML Type Constructors? C? C++? D?

### W6-7 Symbolic Values and Pure Lisp  5L 2T
1. **Lecture**: 
   1. Story of [Lisp](../../evolution.pdf) 
   2. S-Expressions as special values
   3. Evaluation trees and evaluation order
   4. Pure Lisp / Normal vs. Eager Argument Passing; Church Rosser
   5. Dynamic vs. Lexical Binding
   6. Implementation of lexical binding
2. **Tutorial**:
   1. Using mini-lisp (Tutorial)
   2. Implementation of eval (Tutorial)

### W7-8 Prolog 2L 3T

### W9 State and Storage 2L 1T
- **Lecture**:
  1. Memory Model
  2. Reference vs. value
  3. Lvalue vs. rvalue in C/C++
  4. Deep and shallow copy
- **Tutorial**
  1. Garbage collection and RTTI
  2. Stack and lexical scoping

## W10 Commands vs Expressions 2L 1T
1. Theoretical 
2. Atomic commands: Assignments, assertions, empty, procedure call, ...
3. Command constructors: Sequential and variations, conditional, iterative
4. Sequencers
5. Expression Language vs. Command Language including JVM? Flowcharts. Primitive goto language.

## W11. Abstractions


### Tutorial on D 2T
1. Lexical analysis 1T
    1. Methodology: identify the stages, identify the tokens, identify the meaning
    2. Stages of lexical processing:
        1. **Prepare**:
            1. **Remove** ignored characters
            2. **Separators**: find all separators and remove them
                1. **Characters**: space, newline and other spacing characters
                2. **Lines**: line comments
                3. **Chunks**: blocks comments either Nested/Unnested/Escapeable
        2. **Tokenize**: using regular expressions
        3. **Analyze**: characetrize and parse
    3. **Analysis I: Categories of tokens**:
        1. **Literals**: mean themselves, no need to create before using, string, integer, real
        2. **Identifier**/*name*, e.g.,`a101` or `foo2`, defined by RE, e.g.,
           `[a-zA-Z_$][a-zA-Z_$0-9]*`, used by programmers to refer to *entities*.
        3. **Keyword**/*reserved word*: token matching Identifier RE, but cannot be used as name
        4. **Punctuation**: e.g, `;` `,` `()
        5. **Operators**: e.g. `+`, `<<<`, `<=`
    4. **Analysis II: Meaning of tokens**: what do they denote?
        1. **Comments**: denote nothing
        2. **Punctuation**: Do not provide content. How to parse and organize informational tokens
        3. **Informational**: provide contents
            1. **Literal**: provides itself
            2. **Identifier**: provides this which it identifies
                1. **Free**: available, clean to programmer
                2. **Predefined**: can be redefined by programmer
                3. **reserved identifier**: cannot be redefined by user
            3. **Operator**: identify an operator; possibly overload-able.
        4. **Meaning of keywords**: sometimes any of the above, sometimes none, sometimes it depends.
            1. **Punctuation + Keyword**: e.g., `begin`, `var`, `record`, `of`, `array`, `if`, `return`
               **Contextual Punctuation Keyword ** e.g., override in C++, is keyword in some contexts, but not in others
            2. **Literal + Keyword**:  reserved identifier of special values, e.g., and mainly `true`, `false`, `null`; more correctly,
            3. **Identifier + Keyword**: reserved identifier of value, type, variable, function, ...
            4. **Operator + Keyword** e.g., `or`/`and` / `mod` / `new`/
            5. **Unused Keywords**
                1. **Reserved Keyword** for future e.g., entry in early C, later dropped
                2. **Deprecated Keyword** used in the past, e.g., delete in D; frowned upon now
                3. **Forbidden Keyword** never used, never will be used, e.g, const and goto in java, to protect against
                   mistakes, denote nothing
2. tokens of D example: 1T
3. Optional: **Other Lexical Perspectives**
    1. Block open/closing
    2. Separatist/Terminist/Permissive/Mixed
    3. Case
    4. Lexical Conventions
    5. Escaping

                                             3. 
4. [Example](../../lisp.pdf) in D
   1. 