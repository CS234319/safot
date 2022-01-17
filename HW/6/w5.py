from eval_def import *

def make_a_list() -> A_List:
    raise NotImplementedError

def normalize(ast: AST) -> AST:
    raise NotImplementedError

def lookup(a_list: A_List, name: str) -> S_Expression:
    raise NotImplementedError

def eval_cond(a_list: A_List, args: List[AST]) -> S_Expression:
    from eval import eval_rec
    raise NotImplementedError

def eval_set(a_list: A_List, args: List[AST]) -> S_Expression:
    from eval import eval_rec
    raise NotImplementedError
