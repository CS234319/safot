import pytest
from framework.lib.mini_lisp_shell import MiniLispShell


def test_basic(shell):
    """
    Check the mini-lisp interpreter stdout (using the examples from the book)
    """
    assert shell.feed("nil") == "NIL"
    assert shell.feed("()") == "NIL"
    assert shell.feed("(car '(a b))") == "A"
    assert shell.feed("(cdr '(a b))") == "(B)"
    assert shell.feed("(atom 'a)") == "T"
    assert shell.feed("(atom T)") == "T"
    assert shell.feed("(null t)") == "NIL"
    assert shell.feed("(null nil)") == "T"
    assert shell.feed("(null 'a)") == "NIL"
    assert shell.feed("(null '(a a))") == "NIL"
    assert shell.feed("(eq nil t)") == "NIL"
    assert shell.feed("(eq 'a 'a)") == "T"
    assert shell.feed("(eq 'a 'b)") == "NIL"
    assert shell.feed("(quote a)") == "A"
    assert shell.feed("(quote (m o))") == "(M O)"
    assert shell.feed("'a") == "A"
    assert shell.feed("'(n j)") == "(N J)"
    assert shell.feed("(cons 'p '(i u))") == "(P I U)"
    assert shell.feed("(cond (nil 'A) (t 'B))") == "B"
    assert shell.feed("((lambda (x) (car (cdr x))) '(a b))") == "B"


def test_functions(shell):
    """
    Compile functions and run s-expr
    """
    # Compile functions:
    assert shell.feed("(defun mirror (x) (cons (cdr x) (car x)))") == "MIRROR"
    assert shell.feed("(defun zcar(x) (cond ((atom x) x) (t (car x))))") == "ZCAR"

    # Use the functions:
    assert shell.feed("(mirror '(a b))") == "((B).A)"
    assert shell.feed("(zcar '(a b))") == "A"
    assert shell.feed("(zcar '(a b c))") == "A"


def test_error(shell):
    """
    Check errors outputs
    """
    assert shell.feed("(car 'a)") == "Error [CAR] in A"
    assert shell.feed("(cdr 'a)") == "Error [CDR] in A"
    assert shell.feed("(bla)") == "Error [UNDEFINED] in BLA"
    assert shell.feed("(error)") == "Error [NIL] in (ERROR)"
    assert shell.feed("(error 'A)") == "Error [A] in (ERROR (QUOTE A))"
    assert shell.feed("(error 'message)") == "Error [MESSAGE] in (ERROR (QUOTE MESSAGE))"


def test_multi_line(shell):
    """
    Check multi-lines inputs
    """
    # Test: (\n)
    assert shell.feed("(") == ""
    assert shell.feed(")") == "NIL"

    # Test: (\n\n)
    assert shell.feed("(") == ""
    assert shell.feed("") == ""
    assert shell.feed(")") == "NIL"

    # Test: (car\n'(\na b\n)\n)
    assert shell.feed("(car") == ""
    assert shell.feed("") == ""
    assert shell.feed("'(") == ""
    assert shell.feed("") == ""
    assert shell.feed("a b") == ""
    assert shell.feed("") == ""
    assert shell.feed(")") == ""
    assert shell.feed("") == ""
    assert shell.feed(")") == "A"


@pytest.fixture
def shell():
    shell = MiniLispShell("../../../Mini-Lisp.Chic/mini-lisp")
    shell.start_mini_lisp()
    return shell
