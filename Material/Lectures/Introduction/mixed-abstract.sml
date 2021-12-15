signature S'Expression= sig
    type Symbol
    datatype S'Expression  = Pair of S'Expression * S'Expression  | Atom of Symbol
    val car: S'Expression -> S'Expression 
    val cdr: S'Expression -> S'Expression 
    val cons:  S'Expression *  S'Expression -> S'Expression 
    val eq:  S'Expression *  S'Expression -> bool  
    val atom:  S'Expression -> bool
    val asBoolean:  S'Expression -> bool
    val asExpression: bool -> S'Expression
    val T: S'Expression
    val NIL: S'Expression
end
 
 structure T:> S'Expression =
 struct
    type Symbol = string
    datatype S'Expression  = Pair of S'Expression * S'Expression  | Atom of string
    fun car (Pair($,_)) = $
    fun cdr (Pair(_,$)) = $
    fun cons x = Pair x
    fun eq x = case x of (Atom(s1),Atom(s2)) => s1 = s2 | _ => false
    fun atom x = case x of Atom _  => true |  _ => false
    val T = Atom "T"
    val NIL = Atom "NIL"
    fun asBoolean s = eq(s,Atom "NIL")
    fun asExpression b = if b then T else NIL
 end
 open T

 val a = Atom "A"
 val b = Atom "B"
 val s1 = cons(a,b)
 val s2 = cons(b,a)

    val it = car (cons(a,b))
    val it = car a (*Runtime error*)
    val it = cdr (cons(a,b))
    val it = car a (*Runtime error*)




(* Recursive structure: Expressions over  *)
    datatype string Sx =
             Pair of string Sx * string Sx 
        |    Atom of string

    (* Let the  of atoms be all strings *)
    type S = string Sx 

    


    fun ` s = Atom s
    val a = `"a"
    val b = `"b"

    fun cons x = Pair x
    
    val it = let
       val s1 = cons (a,b)
       val s2 = cons (b,a)
       val s3 = cons(s1,a)
       val s4 = cons(s2,b)
    in
        cons(s3,s4)
    end

  


    datatype string List'of'Lists =
             list of string List'of'Lists list
        |    item of string

    (* Let the  of atoms be all strings *)
    type S = string Sx 
