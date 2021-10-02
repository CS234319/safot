Lexical analysis (Tutorial)
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
            3. **Forbidden Keyword** never used, never will be used, e.g, const and goto in java, to protect against mistakes, denote nothing
   
