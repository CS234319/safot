"""
Mini-Lisp-evaluate on Mini-Lisp-evaluate

The following file includes all the tests for evaluate on evaluate,
which based on the test: test_evaluate.in.lisp

For example:
    Original test:
        * (evaluate 'a '(a.x t.t nil.nil)) ; X

    New test:
        * (evaluate '(evaluate (quote a) (quote (a.X t.t nil.nil))) '(environment)) ; X

    Where environment includes all the definitions used by evaluate:
        (t.t nil.nil apply.(lambda ...) evaluate.(lambda ...) quote.(nlambda ...) ...)

Steps:
    1. Generate the latest lisp files from the Mini-lisp book.
    2. Open communication with the mini-lisp executable in Mini-Lisp.Chic.
    3. Feed the shell with all the files from the book. (create our `executable alist`)
    4. Generate environment (string) which will be used by the evaluate function,
       using all the files from the book, similar to step 2. (create our `evaluate alist`)
    5. Create our s-expression as a string (including `evaluate alist` and our `applied evaluate alist`)
    6. Feed the shell with the input s-expression.
    6. Communicate with the mini-lisp process.
    7. Compare our output with expected.
    8. If the strings are identical then the test passed, else failed and show diffs.
Environment:
    1. executable alist - our real alist from the C code, includes all functions
                          that will be feeded from the book (step 3)

    2. evaluate alist - our alist for the top evlauate function, includes all functions
                          that will be feeded from the book (step 4).
                          It (almost) similar to the executable alist, but will
                          be executed only when running the s-expression.

    3. applied evaluate alist - out alist for the applied evaluate function,
                          can be very small (e.g: (t.t nil.nil))
"""
import pytest
from framework.lib.flow_test_framework import FlowTestFramework
from framework.lib.utils import get_flow, get_env, generate_book_files


@pytest.fixture
def flow() -> FlowTestFramework:
    """
    Return a flow loaded with all the functions
    from the latest auto-generated files from the Mini-lisp book
    """
    generate_book_files()
    return get_flow(polling=True, filter_newline=False)


@pytest.fixture
def env() -> str:
    """
    Return an a-list string.
    Calculated once before the tests.
    """
    return get_env()


def test_lookup(flow, env):
    """
    Original tests:
        * (evaluate 'a '(a.T t.t nil.nil)) ; T
        * (evaluate 'a '(a.x t.t nil.nil)) ; X
    """
    alist = "(a.T t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote a) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "T"

    alist = "(a.X t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote a) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "X"


def test_atomic_one_arguments(flow, env):
    """
    Original tests:
        * (evaluate '(atom a) '(a.x t.t nil.nil))      ; T
        * (evaluate '(atom a) '(a.(x) t.t nil.nil))    ; NIL
        * (evaluate '(car a) '(a.(x) t.t nil.nil))     ; X
        * (evaluate '(car a) '(a.(x y z) t.t nil.nil)) ; X
        * (evaluate '(car a) '(a.(x.y) t.t nil.nil))   ; X.Y
        * (evaluate '(cdr a) '(a.(x) t.t nil.nil))     ; NIL
        * (evaluate '(cdr a) '(a.(x y z) t.t nil.nil)) ; (Y Z)
        * (evaluate '(cdr a) '(a.(x.y) t.t nil.nil))   ; NIL
        * (evaluate '(eval a) '(a.x x.y t.t nil.nil))  ; Y
    """
    alist = "(a.x t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (atom a)) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "T"

    alist = "(a.(x) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (atom a)) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "NIL"

    alist = "(a.(x) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (car a)) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "X"

    alist = "(a.(x y z) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (car a)) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "X"

    alist = "(a.(x.y) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (car a)) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "(X.Y)"

    alist = "(a.(x) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (cdr a)) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "NIL"

    alist = "(a.(x y z) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (cdr a)) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "(Y Z)"

    alist = "(a.(x.y) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (cdr a)) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "NIL"

    alist = "(a.x x.y t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (eval a)) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "Y"


def test_atomic_two_arguments(flow, env):
    """
    Original tests:
        * (evaluate '(cons a b) '(a.x b.y t.t nil.nil))  ; (X.Y)
        * (evaluate '(cons a b) '(a.x b.x t.t nil.nil))  ; (X.X)
        * (evaluate '(eq a a) '(a.x t.t nil.nil))        ; T
        * (evaluate '(eq a b) '(a.x b.y t.t nil.nil))    ; NIL
        * (evaluate '(eq a b) '(a.x b.x t.t nil.nil))    ; T
        * (evaluate '(set a b) '(a.x b.y t.t nil.nil))   ; Y
    """
    alist = "(a.x b.y t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (cons a b)) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "(X.Y)"
    
    alist = "(a.x b.x t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (cons a b)) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "(X.X)"
    
    alist = "(a.x t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (eq a a)) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "T"
    
    alist = "(a.x b.y t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (eq a b)) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "NIL"
    
    alist = "(a.x b.x t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (eq a b)) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "T"
    
    alist = "(a.x b.y t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (set a b)) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "Y"


def test_cond(flow, env):
    """
    Original tests:
        * (evaluate '(cond (())) '(t.t nil.nil))                    ; NIL
        * (evaluate '(cond (t nil)) '(t.t nil.nil))                 ; NIL
        * (evaluate '(cond (a t)) '(a.t t.t nil.nil))               ; T
        * (evaluate '(cond (a b)) '(a.t b.t t.t nil.nil))           ; T
        * (evaluate '(cond (t a) (nil b)) '(a.a b.b t.t nil.nil))   ; A
        * (evaluate '(cond (nil a) (t b)) '(a.a b.b t.t nil.nil))   ; B
        * (evaluate '(cond (a b) (b a)) '(a.t b.t t.t nil.nil))     ; T
        * (evaluate '(cond (a b) (b a)) '(a.nil b.t t.t nil.nil))   ; NIL
        * (evaluate '(cond (a b) (a b) (b a)) '(a.nil b.t t.t nil.nil)) ; NIL
    """
    alist = "(t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (cond (()))) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "NIL"
    
    alist = "(t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (cond (t nil))) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "NIL"
    
    alist = "(a.t t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (cond (a t))) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "T"
    
    alist = "(a.t b.t t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (cond (a b))) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "T"
    
    alist = "(a.a b.b t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (cond (t a) (nil b))) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "A"
    
    alist = "(a.a b.b t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (cond (nil a) (t b))) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "B"
    
    alist = "(a.t b.t t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (cond (a b) (b a))) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "T"
    
    alist = "(a.nil b.t t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (cond (a b) (b a))) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "NIL"
    
    alist = "(a.nil b.t t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (cond (a b) (a b) (b a))) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "NIL"


def test_id(flow, env):
    """
    Original tests:
        * (evaluate '(id a) '(id.(lambda (x) x) a.t t.t nil.nil))     ; T
        * (evaluate '(id a) '(id.(lambda (x) x) a.(a b) t.t nil.nil)) ; (A B)
    """
    alist = "(id.(lambda (x) x) a.t t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (id a)) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "T"

    alist = "(id.(lambda (x) x) a.(a b) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (id a)) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "(A B)"


def test_quote(flow, env):
    """
    Original tests:
        * (evaluate '(quote a) '(quote.(nlambda (x) x) a.t t.t nil.nil))  ; A
        * (evaluate '(quote bla) '(quote.(nlambda (x) x) t.t nil.nil))    ; bla
    """
    alist = "(quote.(nlambda (x) x) a.t t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (quote a)) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "A"

    alist = "(quote.(nlambda (x) x) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (quote bla)) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "BLA"


def test_first_3(flow, env):
    """
    Original tests:
        * (evaluate '(first a b c) '(first.(nlambda (x y z) x) t.t nil.nil)) ; a (normal)
        * (evaluate '(first a b c) '(first.(lambda (x y z) x) a.a b.b c.c t.t nil.nil)) ; a
    """
    alist = "(first.(nlambda (x y z) x) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (first a b c)) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "A"

    alist = "(first.(lambda (x y z) x) a.a b.b c.c t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (first a b c)) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "A"


def test_last_3(flow, env):
    """
    Original tests:
        * (evaluate '(last a b c) '(last.(nlambda (x y z) z) t.t nil.nil)) ; c (normal)
        * (evaluate '(last a b c) '(last.(lambda (x y z) z) a.a b.b c.c t.t nil.nil)) ; c
    """
    alist = "(last.(nlambda (x y z) z) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (last a b c)) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "C"

    alist = "(last.(lambda (x y z) z) a.a b.b c.c t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (last a b c)) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "C"


def test_car(flow, env):
    """
    Original tests:
        * (evaluate '(xcar a) '(xcar.(lambda (x) (car x)) a.(a b) t.t nil.nil)) ; a
        * (evaluate '(xcar (a b)) '(xcar.(nlambda (x) (car x)) t.t nil.nil)) ; a (normal)
    """
    alist = "(xcar.(lambda (x) (car x)) a.(a b) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (xcar a)) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "A"

    alist = "(xcar.(nlambda (x) (car x)) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (xcar (a b))) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "A"


def test_cdr(flow, env):
    """
    Original tests:
        * (evaluate '(xcdr a) '(xcdr.(lambda (x) (cdr x)) a.(a b) t.t nil.nil)) ; b
        * (evaluate '(xcdr (a b)) '(xcdr.(nlambda (x) (cdr x)) t.t nil.nil)) ; b (normal)
    """
    alist = "(xcdr.(lambda (x) (cdr x)) a.(a b) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (xcdr a)) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "(B)"

    alist = "(xcdr.(nlambda (x) (cdr x)) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (xcdr (a b))) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "(B)"


def test_mirror(flow, env):
    """
    Original tests:
        * (evaluate '(mirror a) '(mirror.(lambda (x) (cons (cdr x) (car x))) a.(a b) t.t nil.nil)) ; (b a)
        * (evaluate '(mirror (a b)) '(mirror.(nlambda (x) (cons (cdr x) (car x))) t.t nil.nil)) ; (b a) (normal)

    """
    alist = "(mirror.(lambda (x) (cons (cdr x) (car x))) a.(a b) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (mirror a)) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "((B).A)"

    alist = "(mirror.(nlambda (x) (cons (cdr x) (car x))) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (mirror (a b))) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "((B).A)"


def test_zcar(flow, env):
    """
    Original tests:
        * (evaluate '(zcar a) '(zcar.(lambda (x) (cond ((atom x) x) (t (car x)))) a.a t.t nil.nil))      ; a
        * (evaluate '(zcar a) '(zcar.(lambda (x) (cond ((atom x) x) (t (car x)))) a.(a b) t.t nil.nil))  ; a
        * (evaluate '(zcar (a b)) '(zcar.(nlambda (x) (cond ((atom x) x) (t (car x)))) t.t nil.nil)) ; a (normal)
        * (evaluate '(zcar (a)) '(zcar.(nlambda (x) (cond ((atom x) x) (t (car x)))) t.t nil.nil))   ; a (normal)
    """
    alist = "(zcar.(lambda (x) (cond ((atom x) x) (t (car x)))) a.a t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (zcar a)) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "A"

    alist = "(zcar.(lambda (x) (cond ((atom x) x) (t (car x)))) a.(a b) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (zcar a)) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "A"

    alist = "(zcar.(nlambda (x) (cond ((atom x) x) (t (car x)))) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (zcar (a b))) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "A"

    alist = "(zcar.(nlambda (x) (cond ((atom x) x) (t (car x)))) t.t nil.nil)"
    s_expr = f"(evaluate '(evaluate (quote (zcar (a))) (quote {alist})) '({env}))"
    assert flow.feed(s_expr) == "A"
