from eval_def import *

def is_a_user_defined_function(f: S_Expression) -> bool:
    raise NotImplementedError

def eval_defun(a_list: A_List, args: List[AST]) -> S_Expression:
    from eval import eval_rec
    raise NotImplementedError
