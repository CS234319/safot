from eval_def import *
from w6 import *
from w5 import *

def eval_rec(a_list: A_List, ast: AST) -> S_Expression:
    # evaluating an atom: an important question, primitive or not?
    if isinstance(ast, Atom):
        if ast in PRIMITIVES:
            return S_Atom(ast)
        else:
            return lookup(a_list, ast)
    elif not ast:
        # `ast` is an empty list
        return NIL
    else:
        # evaluating a complex s-expression
        f, *args = ast
        # calling a primitive function
        if isinstance(f, Atom):
            if f == "COND":
                return eval_cond(a_list, args)
            elif f == "SET":
                return eval_set(a_list, args)
            elif f == "QUOTE":
                if len(args) != 1:
                    raise WrongNumberOfArguments
                return ast_to_sexpr(args[0])
            elif f == "ATOM":
                if len(args) != 1:
                    raise WrongNumberOfArguments
                a = eval_rec(a_list, args[0])
                if isinstance(a, S_Atom):
                    return T
                else:
                    return NIL
            elif f == "EQ":
                if len(args) != 2:
                    raise WrongNumberOfArguments
                x = eval_rec(a_list, args[0])
                y = eval_rec(a_list, args[1])
                if isinstance(x, S_Atom) and isinstance(y, S_Atom) and x == y:
                    return T
                else:
                    return NIL
            elif f == "EVAL":
                if len(args) != 1:
                    raise WrongNumberOfArguments
                return eval_rec(a_list, args[0])
            elif f == "CAR":
                if len(args) != 1:
                    raise WrongNumberOfArguments
                a = eval_rec(a_list, args[0])
                if isinstance(a, S_Cons):
                    return a.car
                raise NotAPair
            elif f == "CDR":
                if len(args) != 1:
                    raise WrongNumberOfArguments
                a = eval_rec(a_list, args[0])
                if isinstance(a, S_Cons):
                    return a.cdr
                raise NotAPair
            elif f == "CONS":
                if len(args) != 2:
                    raise WrongNumberOfArguments
                return S_Cons(eval_rec(a_list, args[0]), eval_rec(a_list, args[1]))
            elif f == "DEFUN":
                if len(args) != 3:
                    raise WrongNumberOfArguments
                return eval_defun(a_list, args)
            else:
                expr = eval_rec(a_list, f)
                if is_a_user_defined_function(expr):
                    raise NotImplementedError
        raise NotAFunction


def eval(a_list: A_List, ast: AST) -> S_Expression:
    """
    receive a list of strings, evaluate it, return the result as an s-expression
    """
    return eval_rec(a_list, normalize(ast))
