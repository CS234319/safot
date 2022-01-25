from eval_def import *

def make_a_list() -> A_List:
    return []


def lookup(a_list: A_List, ast: str) -> S_Expression:
    for s, val in reversed(a_list):
        if s == ast:
            return val
    raise Undefined


def normalize(ast: AST) -> AST:
    if isinstance(ast, Atom):
        ast = ast.upper()
        if set(ast) - ALLOWED_CHARS:
            raise IllegalSymbol
        return ast
    else:
        return [normalize(x) for x in ast]


def eval_set(a_list: A_List, args: List[AST]) -> S_Expression:
    from eval import eval_rec
    if len(args) != 2:
        raise WrongNumberOfArguments
    name = eval_rec(a_list, args[0])
    if isinstance(name, S_Atom):
        value = eval_rec(a_list, args[1])
        a_list.append((name.value, value))
        return value
    else:
        raise NotASymbol


def eval_cond(a_list: A_List, args: List[AST]) -> S_Expression:
    from eval import eval_rec
    for t, v, *_ in args:
        if eval_rec(a_list, t) != NIL:
            return eval_rec(a_list, v)
    return NIL
