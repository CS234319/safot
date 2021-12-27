(* Recursive structure: Expressions over alphabet *)
    datatype 'Alphabet Sx =
             Pair of Sx * Sx 
        |    Atom of 'Alphabet

    (* Let the alphabet of atoms be all strings *)
    type Sx = string Sx 