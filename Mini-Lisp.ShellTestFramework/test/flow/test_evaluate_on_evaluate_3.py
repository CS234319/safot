"""
Mini-Lisp-evaluate on Mini-Lisp-evaluate

The following file includes all the tests for evaluate on evaluate,
which based on the test: test_evaluate_3.in.lisp

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
from framework.lib.utils import get_flow, get_env


@pytest.fixture
def flow() -> FlowTestFramework:
    """
    Return a flow loaded with all the functions
    from the latest auto-generated files from the Mini-lisp book
    """
    return get_flow(polling=True, filter_newline=False)


@pytest.fixture
def env() -> str:
    """
    Return an a-list string.
    Calculated once before the tests.
    """
    return get_env()


def test_car(flow, env):
    """
    Original tests:
        * (evaluate '(xcar a) '(xcar.(lambda (x) (car x)) a.(a b) t.t nil.nil)) ; a
        * (evaluate '(xcar (a b)) '(xcar.(nlambda (x) (car x)) t.t nil.nil)) ; a (normal)
    """
    raise NotImplementedError


def test_cdr(flow, env):
    """
    Original tests:
        * (evaluate '(xcdr a) '(xcdr.(lambda (x) (cdr x)) a.(a b) t.t nil.nil)) ; b
        * (evaluate '(xcdr (a b)) '(xcdr.(nlambda (x) (cdr x)) t.t nil.nil)) ; b (normal)
    """
    raise NotImplementedError


def test_mirror(flow, env):
    """
    Original tests:
        * (evaluate '(mirror a) '(mirror.(lambda (x) (cons (cdr x) (car x))) a.(a b) t.t nil.nil)) ; (b a)
        * (evaluate '(mirror (a b)) '(mirror.(nlambda (x) (cons (cdr x) (car x))) t.t nil.nil)) ; (b a) (normal)

    """
    raise NotImplementedError


def test_zcar(flow, env):
    """
    Original tests:
        * (evaluate '(zcar a) '(zcar.(lambda (x) (cond ((atom x) x) (t (car x)))) a.a t.t nil.nil))      ; a
        * (evaluate '(zcar a) '(zcar.(lambda (x) (cond ((atom x) x) (t (car x)))) a.(a b) t.t nil.nil))  ; a
        * (evaluate '(zcar (a b)) '(zcar.(nlambda (x) (cond ((atom x) x) (t (car x)))) t.t nil.nil)) ; a (normal)
        * (evaluate '(zcar (a)) '(zcar.(nlambda (x) (cond ((atom x) x) (t (car x)))) t.t nil.nil))   ; a (normal)
    """
    raise NotImplementedError
