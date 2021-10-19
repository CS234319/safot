exception AssertError;

fun noexcept f = f () handle _ => raise AssertError;

fun except f = (f (); raise AssertError) handle ItemNotPresent => ();

fun assert b = if b then () else raise AssertError;