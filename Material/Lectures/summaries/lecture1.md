# Lecture 1

Today's lecture started with technical problems, and time was taken to
reiterate formalities, grading policy, bonus assignments, and the recycle
promise. The four main paradigms: functional, object-oriented, imperative,
and logic based, were discussed. The four main programming languages used in
the course are Prolog, Pascal, ML, and Lisp.

* In response to students' request, we discussed the issue of a programming language being universal; see these [notes](Misc/univrsal.pdf)

* Other terms discussed: variable != value; name != named;  anonymous entities; anonymous variables; nested functions; anonymous types with struct` in C; builtin != predefined != reserved identifier; recursive structure; atomic != compound

* The semicolon in Pascal issue was discussed:
  * Separatist grammar: ';' is a command separator
  * Lenient separatist grammar: ';' is a command separator, but there is also an empty command
  * Terminist grammar: ';' terminates commands
  * Separatist terminist grammar: ';' separates commands, is optional at end (almost the same as lenient separatist)
  * Lenient grammar: as found in Python, ';' can be omitted at eoln
  * Go's grammar: ';' is automatically omitted at eoln