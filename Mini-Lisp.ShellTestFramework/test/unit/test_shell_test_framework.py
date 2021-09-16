import pytest
from pathlib import Path
from framework.lib.flow_test_framework import FlowTestFramework


def test_run_s_expr_file(flow, input_dir):
    """
    Test the following file:

    lisp00.lisp:
        '''
        ()

        (car '(a b))

        (car

              '(
                   b a
               )

        )

        '''

    Expected results:
        NIL
        A
        B
    """
    # Define inputs:
    s_expr_file = f"{input_dir}/lisp00.lisp"

    # Run s_expr:
    out_file = flow.run_s_expr_file(s_expr_file)
    assert Path(out_file).read_text() == "NIL\n" \
                                         "A\n" \
                                         "B\n"


def test_load_function_file(flow, input_dir):
    """
    Compile 2 functions: exists + id
    Run to s_expr files, which includes s_expr that use those functions.
    """
    # Define inputs:
    functions_file = f"{input_dir}/fun.lisp"
    s_expr_file_1 = f"{input_dir}/lisp01.lisp"
    s_expr_file_2 = f"{input_dir}/lisp02.lisp"

    # Compile functions:
    flow.load_function_file(functions_file)

    # Run s_expr:
    out_file = flow.run_s_expr_file(s_expr_file_1)
    assert Path(out_file).read_text() == "T\n" \
                                         "T\n" \
                                         "A\n"

    out_file = flow.run_s_expr_file(s_expr_file_2)
    assert Path(out_file).read_text() == "T\n" \
                                         "NIL\n" \
                                         "A\n"


def test_is_function_file(flow):
    """
    Categorize file by it's name
    """
    assert flow.is_function_file("/tmp/lisp01.lisp") is False
    assert flow.is_function_file("/tmp/lisp41.lisp") is False
    assert flow.is_function_file("/tmp/lisp777.lisp") is False
    assert flow.is_function_file("/tmp/lisp1111.lisp") is False
    assert flow.is_function_file("/tmp/lisp41.txt") is False
    assert flow.is_function_file("/tmp/lisp41") is False
    assert flow.is_function_file("/tmp/eval.lisp") is True
    assert flow.is_function_file("/tmp/blalbalbaab.lisp") is True
    assert flow.is_function_file("/tmp/ppplisp01ppp.lisp") is True
    assert flow.is_function_file("/tmp/blalbalbaab.txt") is True
    assert flow.is_function_file("/tmp/blalbalbaab") is True


@pytest.fixture
def flow():
    return FlowTestFramework("../../../Mini-Lisp.ChicDor/mini-lisp")


@pytest.fixture
def input_dir():
    return "./examples"
