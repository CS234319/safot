import pytest
import os
from pathlib import Path
from framework.lib.flow_test_framework import FlowTestFramework


@pytest.fixture
def flow():
    """
    Pre-process function.
    This function occur before all the flow tests.

    Pre-process steps:
        1. Generate the latest lisp files from the book.
        2. Get the relevant functions files for this test
        3. Open flow
        4. Compiled all functions
        5. return flow
    """
    # Define inputs:
    directory = "../../../Mini-Lisp.BookValidator/Mini-Lisp.Inputs/"
    interpreter = "../../../Mini-Lisp.Chic/mini-lisp"

    # Remove lisp files:
    command = f"make clean -C {directory}"
    os.system(command)

    # Generate lisp files:
    command = f"make all -C {directory}"
    os.system(command)

    # Init flow:
    flow = FlowTestFramework(interpreter)

    # Compile all functions:
    files = [
        f"{directory}/exists.lisp",
        f"{directory}/is-atomic.lisp",
        f"{directory}/lookup.lisp",
        f"{directory}/bind.lisp",
        f"{directory}/apply-trivial-atomic.lisp",
        f"{directory}/apply-eager-atomic.lisp",
        f"{directory}/evaluate.lisp",
        f"{directory}/evaluate-list.lisp",
        f"{directory}/apply-atomic.lisp",
        f"{directory}/evaluate-atomic.lisp",
        f"{directory}/evaluate-cond.lisp",
        f"{directory}/apply-decomposed-lambda.lisp",
        f"{directory}/apply.lisp"
    ]

    for file in files:
        flow.load_function_file(file)

    return flow


def test_exists(flow, input_dir, golden_dir):
    """
    Mini-lisp test for: exists

    Using the exists.lisp file,
    auto generated from the Mini-lisp book
    """
    in_file     = input_dir  / "test_exists.lisp.in"
    golden_file = golden_dir / "test_exists.lisp.out"
    out_file    = flow.run_s_expr_file(in_file)
    assert Path(out_file).read_text() == Path(golden_file).read_text()


def test_is_atomic(flow, input_dir, golden_dir):
    """
    Mini-lisp test for: is_atomic

    Using the is-atomic.lisp file,
    auto generated from the Mini-lisp book
    """
    in_file     = input_dir  / "test_is_atomic.lisp.in"
    golden_file = golden_dir / "test_is_atomic.lisp.out"
    out_file    = flow.run_s_expr_file(in_file)
    assert Path(out_file).read_text() == Path(golden_file).read_text()


def test_lookup(flow, input_dir, golden_dir):
    """
    Mini-lisp test for: lookup

    Using the lookup.lisp file,
    auto generated from the Mini-lisp book
    """
    in_file     = input_dir  / "test_lookup.lisp.in"
    golden_file = golden_dir / "test_lookup.lisp.out"
    out_file    = flow.run_s_expr_file(in_file)
    assert Path(out_file).read_text() == Path(golden_file).read_text()


def test_bind(flow, input_dir, golden_dir):
    """
    Mini-lisp test for: bind

    Using the bind.lisp file,
    auto generated from the Mini-lisp book
    """
    in_file     = input_dir  / "test_bind.lisp.in"
    golden_file = golden_dir / "test_bind.lisp.out"
    out_file    = flow.run_s_expr_file(in_file)
    assert Path(out_file).read_text() == Path(golden_file).read_text()


def test_apply_trivial_atomic(flow, input_dir, golden_dir):
    """
    Mini-lisp test for: apply_trivial_atomic

    Using the apply-trivial-atomic.lisp file,
    auto generated from the Mini-lisp book
    """
    in_file     = input_dir  / "test_apply_trivial_atomic.lisp.in"
    golden_file = golden_dir / "test_apply_trivial_atomic.lisp.out"
    out_file    = flow.run_s_expr_file(in_file)
    assert Path(out_file).read_text() == Path(golden_file).read_text()


def test_apply_eager_atomic(flow, input_dir, golden_dir):
    """
    Mini-lisp test for: apply_eager_atomic

    Using the apply-eager-atomic.lisp file,
    auto generated from the Mini-lisp book
    """
    in_file     = input_dir  / "test_apply_eager_atomic.lisp.in"
    golden_file = golden_dir / "test_apply_eager_atomic.lisp.out"
    out_file    = flow.run_s_expr_file(in_file)
    assert Path(out_file).read_text() == Path(golden_file).read_text()


def test_evaluate_1(flow, input_dir, golden_dir):
    """
    Mini-lisp test for: evaluate
    Part 1: evaluate atoms, atomic functions, cond, and errors.

    Using the evaluate.lisp file,
    auto generated from the Mini-lisp book
    """
    in_file     = input_dir  / "test_evaluate_1.lisp.in"
    golden_file = golden_dir / "test_evaluate_1.lisp.out"
    out_file    = flow.run_s_expr_file(in_file)
    assert Path(out_file).read_text() == Path(golden_file).read_text()


def test_evaluate_2(flow, input_dir, golden_dir):
    """
    Mini-lisp test for: evaluate
    Part 2: evaluate lambda/nlambda functions.

    Using the evaluate.lisp file,
    auto generated from the Mini-lisp book
    """
    in_file     = input_dir  / "test_evaluate_2.lisp.in"
    golden_file = golden_dir / "test_evaluate_2.lisp.out"
    out_file    = flow.run_s_expr_file(in_file)
    assert Path(out_file).read_text() == Path(golden_file).read_text()


def test_evaluate_list(flow, input_dir, golden_dir):
    """
    Mini-lisp test for: evaluate_list

    Using the evaluate-list.lisp file,
    auto generated from the Mini-lisp book
    """
    in_file     = input_dir  / "test_evaluate_list.lisp.in"
    golden_file = golden_dir / "test_evaluate_list.lisp.out"
    out_file    = flow.run_s_expr_file(in_file)
    assert Path(out_file).read_text() == Path(golden_file).read_text()


def test_apply_atomic(flow, input_dir, golden_dir):
    """
    Mini-lisp test for: apply_atomic

    Using the apply-atomic.lisp file,
    auto generated from the Mini-lisp book
    """
    in_file     = input_dir  / "test_apply_atomic.lisp.in"
    golden_file = golden_dir / "test_apply_atomic.lisp.out"
    out_file    = flow.run_s_expr_file(in_file)
    assert Path(out_file).read_text() == Path(golden_file).read_text()


def test_evaluate_atomic(flow, input_dir, golden_dir):
    """
    Mini-lisp test for: evaluate_atomic

    Using the evaluate-atomic.lisp file,
    auto generated from the Mini-lisp book
    """
    in_file     = input_dir  / "test_evaluate_atomic.lisp.in"
    golden_file = golden_dir / "test_evaluate_atomic.lisp.out"
    out_file    = flow.run_s_expr_file(in_file)
    assert Path(out_file).read_text() == Path(golden_file).read_text()


def test_evaluate_cond(flow, input_dir, golden_dir):
    """
    Mini-lisp test for: evaluate_cond

    Using the evaluate-cond.lisp file,
    auto generated from the Mini-lisp book
    """
    in_file     = input_dir  / "test_evaluate_cond.lisp.in"
    golden_file = golden_dir / "test_evaluate_cond.lisp.out"
    out_file    = flow.run_s_expr_file(in_file)
    assert Path(out_file).read_text() == Path(golden_file).read_text()


def test_apply_decomposed_lambda(flow, input_dir, golden_dir):
    """
    Mini-lisp test for: apply_decomposed_lambda

    Using the apply-decomposed-lambda.lisp file,
    auto generated from the Mini-lisp book
    """
    in_file     = input_dir  / "test_apply_decomposed_lambda.lisp.in"
    golden_file = golden_dir / "test_apply_decomposed_lambda.lisp.out"
    out_file    = flow.run_s_expr_file(in_file)
    assert Path(out_file).read_text() == Path(golden_file).read_text()


def test_apply(flow, input_dir, golden_dir):
    """
    Mini-lisp test for: apply

    Using the apply.lisp file,
    auto generated from the Mini-lisp book
    """
    in_file     = input_dir  / "test_apply.lisp.in"
    golden_file = golden_dir / "test_apply.lisp.out"
    out_file    = flow.run_s_expr_file(in_file)
    assert Path(out_file).read_text() == Path(golden_file).read_text()


@pytest.fixture
def input_dir():
    """
    return the input directory
    """
    directory = "../inputs/test_book_evaluate/"
    return Path(directory)


@pytest.fixture
def golden_dir():
    """
    return the golden directory
    """
    directory = "../golden/test_book_evaluate/"
    return Path(directory)
