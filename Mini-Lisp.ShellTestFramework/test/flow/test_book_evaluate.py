import pytest
import glob
from pathlib import Path
from framework.lib.flow_test_framework import FlowTestFramework
from framework.lib.utils import get_flow


@pytest.fixture
def flow() -> FlowTestFramework:
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
    return get_flow()


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


def test_book_evaluate(flow, input_dir, golden_dir):
    """
    All the tests for all the Lisp evaluate functions,
    which auto generated from the Mini-lisp book.

    `flow` already loaded with all the functions from the books
    (mini-lisp process is running).

    Read more about this flow here:
        https://github.com/yossigil/safot/tree/master/Mini-Lisp.ShellTestFramework#evaluate
    """
    input_files = sorted(glob.glob(f"{input_dir}/*.lisp.in"))
    golden_files = sorted(glob.glob(f"{golden_dir}/*.lisp.out"))
    for in_file, golden_file in zip(input_files, golden_files):
        print(f"Running: {in_file}")
        out_file = flow.run_s_expr_file(in_file)
        assert Path(out_file).read_text() == Path(golden_file).read_text()
        print(f"Passed.")
