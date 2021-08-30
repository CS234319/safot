import pytest
import glob
from pathlib import Path
from framework.lib.flow_test_framework import FlowTestFramework
from framework.lib.utils import get_flow


@pytest.fixture
def flow() -> FlowTestFramework:
    """
    Return a flow loaded with all the functions
    from the latest auto-generated files from the Mini-lisp book
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
    """
    input_files = sorted(glob.glob(f"{input_dir}/*.lisp.in"))
    golden_files = sorted(glob.glob(f"{golden_dir}/*.lisp.out"))
    for in_file, golden_file in zip(input_files, golden_files):
        print(f"Running: {in_file}")
        out_file = flow.run_s_expr_file(in_file)
        assert Path(out_file).read_text() == Path(golden_file).read_text()
        print(f"Passed.")
