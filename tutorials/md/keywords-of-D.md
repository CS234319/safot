1. Unused
  1. Deprecated: delete
  2. Typos: macro, body

1. Reserved identifiers
  1. Naming Values: keyword literals: false, true, null
  1. Naming parameterless compile time function: `__FILE__,  __FILE_FULL_PATH__, __MODULE__,
  __LINE__ __FUNCTION__, __PRETTY_FUNCTION__`
  1. Naming runtime value: this
  1. Naming Operators:  cast, new, delete, typeid, in (index of associative arrays)
  1. Naming Types: seems to be very orthogonal 
    1. Pseudo: void
    1. Ordinal: 
       1. Boolean: bool 
       1. Character: char wchar dchar
    1. Integral: 
      1. Signed: byte, short, int, long, cent
      1. Unsigned: ubyte, ushort, uint, ulong, ucent
    1. Floating:
      1. Real: float, double, real
      1. Imaginary: ifloat, idouble, ireal 
      1. Complex: cfloat, cdouble, creal 

1. Familiar command constructors: 
  1. Atomic: assert debug
  1. Iterative: do for `foreach_reverse` while foreach  
  1. Conditional: default, if, else, case, switch,
  1. Sequencer: 
    1. Inner procedural: continue, return, throw, goto, break 
    1. Intra procedural: throw try catch finally

  Parameter passing mode: in, out, ref, lazy, 

Candidate Nameables: 
  1. Functions: unittest, function, invariant, delegate 
  2. Types: class, enum, interface, struct, union, function, 
  3. Advanced: mixin, module, package

Modifiers: of functions? classes? who knows?
abstract
  auto
  const
    private
    protected
    public
    final
    static
    deprecated
    nothrow
    override



    alias
    align
    asm
    body

    immutable
    import
    is

    mixin


    out

    pragma
    pure
    ref

    scope
    shared
    super
    synchronized
    template
    typeid
    typeof


    version

    with

        __gshared
    __traits
    __vector
    __parameters

    delegate
    export
    extern
