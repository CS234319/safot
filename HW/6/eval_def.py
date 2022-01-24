from typing import List, Tuple, Union
from dataclasses import dataclass
import functools

Atom = str
AST = Union[List["AST"], Atom]


@dataclass(frozen=True)
class S_Expression:
    pass


# an atom is a kind of s-expression
@dataclass(frozen=True)
class S_Atom(S_Expression):
    value: str


# Cons of 2 s-expressions is a kind of s-expression
@dataclass(frozen=True)
class S_Cons(S_Expression):
    car: S_Expression
    cdr: S_Expression


NIL = S_Atom("NIL")
T = S_Atom("T")

# an alias
env_record = Tuple[str, S_Expression]
# enviroment list
A_List = List[env_record]


PRIMITIVES = {"QUOTE", "ATOM", "EQ", "EVAL", "CAR", "CDR", "CONS", "SET", "COND"}

# converts a string to a s-expression
def ast_to_sexpr(ast: AST) -> S_Expression:
    if isinstance(ast, Atom):
        return S_Atom(ast.upper())
    else:
        # converts recursively a string list to an s-expression
        return functools.reduce(
            lambda acc, x: S_Cons(ast_to_sexpr(x), acc),
            reversed(ast),
            NIL,
        )


class MiniLispError(Exception):
    pass


class Undefined(MiniLispError):
    pass


class NotAPair(MiniLispError):
    pass


class WrongNumberOfArguments(MiniLispError):
    pass


class NotAFunction(MiniLispError):
    pass


class NotASymbol(MiniLispError):
    pass

class IllegalSymbol(MiniLispError):
    pass


ALLOWED_CHARS = set("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890-+!@#$%^&*~`'?/><=:|")
