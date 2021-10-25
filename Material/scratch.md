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
   1. Story of [Lisp](../../../evolution.pdf) 
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



Prof. J. Gil



1. **Introduction: ** 
    * Why study programming languages, paradigms.
    * Synatactical Elements:
        1.  identifiers, nameable entities (variables, values, functions, procedures, templates, namespaces, labels, modules), 
        2. reserved words, reserved identifiers, pre-defined identifiers, keywords
        3.  literlas, escaping, comments. 
    * separatist, terminist, and variations.
    * Guiding principles in language design: example the C rules: the division between preprocessor, compiler and linker. The no hiding principle. Programmer are big boys principle.
    * BNF, EBNF

    **Reading**: 

    1. [http://www.underwar.co.il/1-Programming/d552/](http://www.underwar.co.il/1-Programming/d552/)
    2. [http://en.wikipedia.org/wiki/Programming_paradigm](http://en.wikipedia.org/wiki/Programming_paradigm)
    3. [http://en.wikibooks.org/wiki/Computer_Programming/Hello_world](http://en.wikibooks.org/wiki/Computer_Programming/Hello_world)
    4. [http://en.wikipedia.org/wiki/Comparison_of_programming_languages_(syntax)#Comments](http://en.wikipedia.org/wiki/Comparison_of_programming_languages_(syntax)#Comments)
    5. [http://en.wikipedia.org/wiki/Comparison_of_programming_languages_(syntax)#Statements](http://en.wikipedia.org/wiki/Comparison_of_programming_languages_(syntax)#Statements)
    6. [http://en.wikipedia.org/wiki/The_c_programming_language](http://en.wikipedia.org/wiki/The_c_programming_language)
    7. [http://en.wikipedia.org/wiki/Pascal_(programming_language)#Semicolons_as_statement_separators](http://en.wikipedia.org/wiki/Pascal_(programming_language)#Semicolons_as_statement_separators)
    8. [http://www.lysator.liu.se/c/bwk-on-pascal.html](http://www.lysator.liu.se/c/bwk-on-pascal.html)
    9. [http://www.standardpascal.org/The_Programming_Language_Pascal_1973.pdf](http://www.standardpascal.org/The_Programming_Language_Pascal_1973.pdf)
    10. [http://en.wikipedia.org/wiki/Backus%E2%80%93Naur_Form](http://en.wikipedia.org/wiki/Backus%E2%80%93Naur_Form)
    11. [http://en.wikipedia.org/wiki/EBNF](http://en.wikipedia.org/wiki/EBNF)
    12. [http://en.wikipedia.org/wiki/Wirth_syntax_notation](http://en.wikipedia.org/wiki/Wirth_syntax_notation)
    13. [http://en.wikipedia.org/wiki/Stropping_(syntax)](http://en.wikipedia.org/wiki/Stropping_(syntax))

	**Questions**:



        1. Sort the reserved words of Algol 60 into classes (see here for a list - [http://en.wikipedia.org/wiki/ALGOL_60#ALGOL_60_Reserved_words_and_restricted_identifiers](http://en.wikipedia.org/wiki/ALGOL_60#ALGOL_60_Reserved_words_and_restricted_identifiers) including:
            * reserved identifiers
            * punctuators
            * type constructors
            * other
        2. Is algol 60 a separatist or terminst language?
        3. Which approach did Algol 60 use for libraries. Explain and compare with the methods learned in class.
        4. Are there are any pre-defined identifers in Go? Epxlain how you reached this conclusion?
        5. How does Go escape special characters in literals? Warning: the answer may be long.
        6.  Write an EBNF to describe the EBNF of Go. Your EBNF should conform to the syntax of itself.
        7. How can you create anynmous variables in Go?
        8. Which are the type constructors of Go?
        9. In which fundamental way are the literals of Go different than those of C and C++.
1. **Simple Values:** The lisp value system. atomic vs. compound values. ‎The prolog value sysem, the interpretation of machine representation, First class and second class values: examples Pascal functions, C’s arrays and sructs, C++ references
    * [https://en.wikipedia.org/wiki/S-expression](https://en.wikipedia.org/wiki/S-expression)
    * [https://en.wikipedia.org/wiki/Car_and_cdr](https://en.wikipedia.org/wiki/Car_and_cdr)
    * [https://en.wikipedia.org/wiki/Cons](https://en.wikipedia.org/wiki/Cons)
    * [https://en.wikipedia.org/wiki/Prolog#Data_types](https://en.wikipedia.org/wiki/Prolog#Data_types) 
2. **Introduction to Types**

    Why types? Rice’s theorem. Array bound checking, division by zero, memory allocation, floating point operations. Kinds of safety.

        13. [https://en.wikipedia.org/wiki/Rice_theorem](https://en.wikipedia.org/wiki/Rice_theorem)
        14. [http://en.wikipedia.org/wiki/Reference_(C%2B%2B)](http://en.wikipedia.org/wiki/Reference_(C%2B%2B))
3. **Simple Type Systems:** 
    * Atomic types, rudimentary types, type constructors. The relationship between atomic types and atomic values.
    *  Compound types and compound values. atomic types vs. atomic values.
    * Type constructors such as product, disjoint sum, records, unions, arrays,  sets, associative arrays, the Unit type, the None type, the Universal type. Less common type constructors, as in e.g., metapost. 
    * Recursive type definitions

**Reading:**



        15. [http://en.wikipedia.org/wiki/Nested_function](http://en.wikipedia.org/wiki/Nested_function)
        16. [http://en.wikipedia.org/wiki/First-class_function](http://en.wikipedia.org/wiki/First-class_function)
        17. [https://en.wikipedia.org/wiki/Unit_type](https://en.wikipedia.org/wiki/Unit_type)
        18. [https://en.wikipedia.org/wiki/Empty_type](https://en.wikipedia.org/wiki/Empty_type)
        19. [http://en.wikipedia.org/wiki/Top_type](http://en.wikipedia.org/wiki/Top_type)
        20. [http://en.wikipedia.org/wiki/Product_type](http://en.wikipedia.org/wiki/Product_type)
        21. [https://en.wikipedia.org/wiki/Tagged_union](https://en.wikipedia.org/wiki/Tagged_union)
        22. [http://en.wikipedia.org/wiki/Set_(abstract_data_type)](http://en.wikipedia.org/wiki/Set_(abstract_data_type))
        23. [https://en.wikipedia.org/wiki/Function_type](https://en.wikipedia.org/wiki/Function_type)
        24. [https://en.wikipedia.org/wiki/Currying](https://en.wikipedia.org/wiki/Currying)
        25. [http://www.tug.org/tutorials/mp/mpman.pdf](http://www.tug.org/tutorials/mp/mpman.pdf)
        26. [http://en.wikipedia.org/wiki/First-class_citizen](http://en.wikipedia.org/wiki/First-class_citizen)
        27. [https://en.wikipedia.org/wiki/Recursive_data_type](https://en.wikipedia.org/wiki/Recursive_data_type)
        28. [https://en.wikipedia.org/wiki/Type_system](https://en.wikipedia.org/wiki/Type_system)
        29. [https://en.wikipedia.org/wiki/Algebraic_types](https://en.wikipedia.org/wiki/Algebraic_types)
        30. [https://en.wikipedia.org/wiki/Disjoint_union](https://en.wikipedia.org/wiki/Disjoint_union)
        31. [https://en.wikipedia.org/wiki/Tagged_union](https://en.wikipedia.org/wiki/Tagged_union)
        32. [https://en.wikipedia.org/wiki/C%2B%2B11#Tuple_types](https://en.wikipedia.org/wiki/C%2B%2B11#Tuple_types)
        33. [http://en.wikipedia.org/wiki/Set_(abstract_data_type)](http://en.wikipedia.org/wiki/Set_(abstract_data_type))
        34. [http://en.wikipedia.org/wiki/Recursive_data_type](http://en.wikipedia.org/wiki/Recursive_data_type)

    **Questions:**

    * List all atomic types of the Go programming language.
    * List all type constructors of the Go programming language.
    * What are the atomic types and the type constructors of MetaPost?
    * Demonstrate all uses of the product type in the Go programming language
    * Give reasons why Psacal is the only programming language which has a builtin type constructor for sets.
    * Study this feature: [ttp://en.wikipedia.org/wiki/Eiffel_(programming_language)#Void-safety](http://en.wikipedia.org/wiki/Eiffel_(programming_language)#Void-safety) and discuss it with comparison  to the safe handling of disjoint unions in ML.
    * Read this [http://stackoverflow.com/questions/436211/is-everything-in-net-an-object](http://stackoverflow.com/questions/436211/is-everything-in-net-an-object) and discuss it in the context of univesal type in C#.
    * Does ML have a universal type? The None type? Explain and provide references.
4. **Type Systems in Context**
    * Representation of Atomic Types: boolean, char (ASCII, EBCDIC, UNICODE), the string type. Integeral types, floating point types. 
    * **Layers of absraction in the definition of the representation of atomic types. **
    * Mapping primitive types to machine types.
    * Relationship of type systems to theoretical type systems
        35. Idealization.
        36. Model for achievement
        37. Better understanding of programming languages: e.g., void types, relationship between tuple and named tuples in calling functions, curreying, etc. 

        **Readings:**

        38. [http://en.wikipedia.org/wiki/Abstraction_layer](http://en.wikipedia.org/wiki/Abstraction_layer)
        39. [https://en.wikipedia.org/wiki/Character_encoding](https://en.wikipedia.org/wiki/Character_encoding)
        40. [https://en.wikipedia.org/wiki/ASCII](https://en.wikipedia.org/wiki/ASCII)
        41. [https://en.wikipedia.org/wiki/Extended_Binary_Coded_Decimal_Interchange_Code](https://en.wikipedia.org/wiki/Extended_Binary_Coded_Decimal_Interchange_Code)
        42. [https://en.wikipedia.org/wiki/Integer_(computer_science)](https://en.wikipedia.org/wiki/Integer_(computer_science)#Common_long_integer_sizes)
        43. [http://en.wikipedia.org/wiki/Signed_number_representations](http://en.wikipedia.org/wiki/Signed_number_representations)
        44. [http://en.wikipedia.org/wiki/Computer_number_format](http://en.wikipedia.org/wiki/Computer_number_format)
5. **Classification of type systems:  **
    * no typing, minimal typing, simple type system, advanced type constructors
    * infer vs. manifest typing, 
    * discriminatory vs. non-discriminatory (orthogonal)
    * strong typing vs weak typing, 
    * dynamic typing, vs. static typing, **gradual typing**
    * structural typing, vs. nominal typing.

	**Readings:**



            * [http://en.wikipedia.org/wiki/Type_safety](http://en.wikipedia.org/wiki/Type_safety)
            * [http://en.wikipedia.org/wiki/Type_system](http://en.wikipedia.org/wiki/Type_system#Static_type-checking)
            * [http://en.wikipedia.org/wiki/Nominal_typing](http://en.wikipedia.org/wiki/Nominal_typing)
            * [http://en.wikipedia.org/wiki/Structural_type_system](http://en.wikipedia.org/wiki/Structural_type_system)
            * [http://en.wikipedia.org/wiki/Type_inference](http://en.wikipedia.org/wiki/Type_inference)
            * [http://en.wikipedia.org/wiki/Manifest_typing](http://en.wikipedia.org/wiki/Manifest_typing)
            * [http://webcourse.cs.technion.ac.il/236703/Spring2013/ho/WCFiles/structural_nominal.pdf](http://webcourse.cs.technion.ac.il/236703/Spring2013/ho/WCFiles/structural_nominal.pdf)
            * [http://en.wikipedia.org/wiki/Serialization](http://en.wikipedia.org/wiki/Serialization)
            * [http://en.wikipedia.org/wiki/Marshalling_(computer_science)](http://en.wikipedia.org/wiki/Marshalling_(computer_science))
            * [http://en.wikipedia.org/wiki/Name_mangling](http://en.wikipedia.org/wiki/Name_mangling#Name_mangling_in_C.2B.2B)
            * [http://c2.com/cgi/wiki?NominativeAndStructuralTyping](http://c2.com/cgi/wiki?NominativeAndStructuralTyping)
6. **Polymorphism:** the polymorphism taxonomy. Higher level type constructors, i.e., templates. Why do we need them (the set type constructor of Pascal example) Reading:
    * [http://en.wikipedia.org/wiki/First-class_citizen](http://en.wikipedia.org/wiki/First-class_citizen)
    * [https://en.wikipedia.org/wiki/Recursive_data_type](https://en.wikipedia.org/wiki/Recursive_data_type)
    * [https://en.wikipedia.org/wiki/Type_system](https://en.wikipedia.org/wiki/Type_system)
    * [https://en.wikipedia.org/wiki/Algebraic_types](https://en.wikipedia.org/wiki/Algebraic_types)
    * [https://en.wikipedia.org/wiki/Disjoint_union](https://en.wikipedia.org/wiki/Disjoint_union)
    * [https://en.wikipedia.org/wiki/Tagged_union](https://en.wikipedia.org/wiki/Tagged_union)
    * [https://en.wikipedia.org/wiki/C%2B%2B11#Tuple_types](https://en.wikipedia.org/wiki/C%2B%2B11#Tuple_types)
    * [http://en.wikipedia.org/wiki/Set_(abstract_data_type)](http://en.wikipedia.org/wiki/Set_(abstract_data_type))
    * [http://en.wikipedia.org/wiki/Recursive_data_type](http://en.wikipedia.org/wiki/Recursive_data_type)
7. **Binding and namepspaces:**
    1. Namespaces: kind of keys. context, scope, global and selective importing, implicit importing including nesting and inheritance, hinding, ambiguity, linking. 
    2. Definitions and declarations. Collateral definitions, mutual definitions. Local definitions.
    3. A detailed study of management of namespaces in Java and in C++.
    4. Binding: what is it? Static vs. dynamic binding. Implementation of binding in Pascal, in Lisp and in Scheme. 

    Reading:

    * [http://en.wikipedia.org/wiki/Lexical_scope#Lexical_scoping](http://en.wikipedia.org/wiki/Lexical_scope#Lexical_scoping)
8. **Storage and memory management:** We do not necessarily need variables, selective vs. total updates, reference semantics, value semantics. Stack based memory management. Structure of the heap. Manual heap management. Dangling references. Memory leakage.  garbage collection, mark and sweep, copy collectors, reference counting, generational garbage collectors.  Memory leakage in garbage collecting systems. 
9. **Variation on the function concept:**
    * Anonymous functions
    * nested functions in Pascal and in C.
    * closures
    * iterators and implicit iterators
    * generators
    * co-routines
10. **Commands: **
    * Structured programming, atomic commands, command constructors. sequences, collateral vs. sequential execution, conditionals, loops, definite and indefinite, collateral loops. 
    * Sequencers. Short circuit evaluation. Multi level break and continue. 
    * Exception handling

    **Reading**:

    * [http://en.wikipedia.org/wiki/Assignment_(computer_science)#Chained_assignment](http://en.wikipedia.org/wiki/Assignment_(computer_science)#Chained_assignment)
    * [http://en.wikipedia.org/wiki/Exception_handling](http://en.wikipedia.org/wiki/Exception_handling)
    * [https://en.wikipedia.org/wiki/C%2B%2B11#Range-based_for_loop](https://en.wikipedia.org/wiki/C%2B%2B11#Range-based_for_loop)
11. **Abstraction: **
    * **what is abstraction, the deja vu principle, abstraction mechanisms, the evolution of abstraction mechanisms,**
        45. [http://en.wikipedia.org/wiki/Don't_repeat_yourself](http://en.wikipedia.org/wiki/Don't_repeat_yourself)
        46. [http://en.wikipedia.org/wiki/Rule_of_three_(computer_programming)](http://en.wikipedia.org/wiki/Rule_of_three_(computer_programming))
        47. [http://en.wikipedia.org/wiki/Abstraction_(computer_science)](http://en.wikipedia.org/wiki/Abstraction_(computer_science))
    * abstraction **metaphors:** functions, procecdures, modules, objects, C++ classes and operator overloading, **C++ templates.  **
    * **Encapsulation:, IGNORANCE IS STRENGTH,  IGNORANCE IS STRENGTH**
        48. [http://www.sparknotes.com/lit/1984/quotes.html](http://www.sparknotes.com/lit/1984/quotes.html)
        49. [http://en.wikipedia.org/wiki/Information_hiding](http://en.wikipedia.org/wiki/Information_hiding)
    * Parameter passing: by value, by reference, by input-output, call by name, 
        50. [http://en.wikipedia.org/wiki/Call_by_name#Call_by_name](http://en.wikipedia.org/wiki/Call_by_name#Call_by_name)

    Reading:

    * [http://en.wikipedia.org/wiki/Evaluation_strategy](http://en.wikipedia.org/wiki/Evaluation_strategy)
    * 
12. Case study: the Java JVM. Virtual machines. Strongly typed machine language. 
13. **Case study: Template programming in C++**