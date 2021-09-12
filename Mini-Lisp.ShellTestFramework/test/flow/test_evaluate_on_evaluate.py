"""
Mini-Lisp-evaluate on Mini-Lisp-evaluate
"""
import pytest
import tempfile
from pathlib import Path
from framework.lib.flow_test_framework import FlowTestFramework
from framework.lib.utils import get_flow, get_env, generate_book_files


@pytest.fixture
def flow() -> FlowTestFramework:
    """
    Return a flow loaded with all the functions
    from the latest auto-generated files from the Mini-lisp book
    """
    generate_book_files()
    return get_flow(filter_newline=False)


def run(flow, s_expr: str) -> str:
    tmp_file = Path(tempfile.mkstemp()[1])
    tmp_file.write_text(s_expr)
    out_path = Path(flow.run_s_expr_file(str(tmp_file)))
    return out_path.read_text().replace("\n", "")


def test_evaluate_on_evaluate(flow):
    """
    All the tests for all the Lisp evaluate on Lisp evaluate,
    which auto generated from the Mini-lisp book.

    `flow` already loaded with all the functions from the books
    (mini-lisp process is running)
    Meaning that the outer evaluate will use the C alist which already loaded.

    `env` is a huge string with all the functions from the books,
    used as the alist for the definitions of the inner evaluate.

    Note, that the inner evaluate defined in `env`, the outer in C alist,
    and the inner use it's own alist too.

    Read more about this flow here:
        https://github.com/yossigil/safot/tree/master/Mini-Lisp.ShellTestFramework#evaluateonevaluate
    """
    env = get_env(flow)

    print("Running: EvaluateOnEvaluate - evaluate atoms")
    alist = "(a.T t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote a) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "T"

    alist = "(a.X t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote a) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "X"
    print("Passed.")

    print("Running: EvaluateOnEvaluate - evaluate atomic functions with one arguments")
    alist = "(a.x t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (atom a)) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "T"

    alist = "(a.(x) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (atom a)) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "NIL"

    alist = "(a.(x) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (car a)) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "X"

    alist = "(a.(x y z) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (car a)) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "X"

    alist = "(a.(x.y) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (car a)) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "(X.Y)"

    alist = "(a.(x) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (cdr a)) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "NIL"

    alist = "(a.(x y z) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (cdr a)) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "(Y Z)"

    alist = "(a.(x.y) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (cdr a)) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "NIL"

    alist = "(a.x x.y t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (eval a)) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "Y"
    print("Passed.")

    print("Running: EvaluateOnEvaluate - evaluate atomic functions with two arguments")
    alist = "(a.x b.y t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (cons a b)) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "(X.Y)"
    
    alist = "(a.x b.x t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (cons a b)) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "(X.X)"
    
    alist = "(a.x t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (eq a a)) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "T"
    
    alist = "(a.x b.y t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (eq a b)) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "NIL"
    
    alist = "(a.x b.x t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (eq a b)) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "T"
    
    alist = "(a.x b.y t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (set a b)) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "Y"
    print("Passed.")

    print("Running: EvaluateOnEvaluate - evaluate cond expressions")
    alist = "(t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (cond (()))) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "NIL"
    
    alist = "(t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (cond (t nil))) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "NIL"
    
    alist = "(a.t t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (cond (a t))) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "T"
    
    alist = "(a.t b.t t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (cond (a b))) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "T"
    
    alist = "(a.a b.b t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (cond (t a) (nil b))) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "A"
    
    alist = "(a.a b.b t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (cond (nil a) (t b))) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "B"
    
    alist = "(a.t b.t t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (cond (a b) (b a))) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "T"
    
    alist = "(a.nil b.t t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (cond (a b) (b a))) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "NIL"
    
    alist = "(a.nil b.t t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (cond (a b) (a b) (b a))) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "NIL"
    print("Passed.")

    print("Running: EvaluateOnEvaluate - evaluate errors")
    alist = "(t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (error)) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "Error [(NIL)] in (ERROR ACTUALS)"

    alist = "(a.my_err t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (error a)) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "Error [((MY_ERR))] in (ERROR ACTUALS)"

    alist = "(t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (bla)) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "Error [UNDEFINED] in UNDEFINED"

    alist = "(t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (NIL NIL)) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "Error [CAR] in NIL"
    print("Passed.")

    print("Running: EvaluateOnEvaluate - evaluate lambda/nlambda functions")
    # id
    alist = "(id.(lambda (x) x) a.t t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (id a)) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "T"

    alist = "(id.(lambda (x) x) a.(a b) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (id a)) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "(A B)"

    # quote
    alist = "(quote.(nlambda (x) x) a.t t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (quote a)) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "A"

    alist = "(quote.(nlambda (x) x) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (quote bla)) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "BLA"

    # first_3
    alist = "(first.(nlambda (x y z) x) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (first a b c)) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "A"

    alist = "(first.(lambda (x y z) x) a.a b.b c.c t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (first a b c)) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "A"

    # last_3
    alist = "(last.(nlambda (x y z) z) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (last a b c)) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "C"

    alist = "(last.(lambda (x y z) z) a.a b.b c.c t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (last a b c)) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "C"

    # car (xcar)
    alist = "(xcar.(lambda (x) (car x)) a.(a b) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (xcar a)) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "A"

    alist = "(xcar.(nlambda (x) (car x)) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (xcar (a b))) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "A"

    # cdr (xcdr)
    alist = "(xcdr.(lambda (x) (cdr x)) a.(a b) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (xcdr a)) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "(B)"

    alist = "(xcdr.(nlambda (x) (cdr x)) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (xcdr (a b))) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "(B)"

    # mirror
    alist = "(mirror.(lambda (x) (cons (cdr x) (car x))) a.(a b) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (mirror a)) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "((B).A)"

    alist = "(mirror.(nlambda (x) (cons (cdr x) (car x))) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (mirror (a b))) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "((B).A)"

    # zcar
    alist = "(zcar.(lambda (x) (cond ((atom x) x) (t (car x)))) a.a t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (zcar a)) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "A"

    alist = "(zcar.(lambda (x) (cond ((atom x) x) (t (car x)))) a.(a b) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (zcar a)) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "A"

    alist = "(zcar.(nlambda (x) (cond ((atom x) x) (t (car x)))) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (zcar (a b))) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "A"

    alist = "(zcar.(nlambda (x) (cond ((atom x) x) (t (car x)))) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (zcar (a))) (quote {alist})) '({env}))"
    assert run(flow, s_expr) == "A"
    print("Passed.")
