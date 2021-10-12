import logging
import pytest
import glob
from pathlib import Path
from flow_test_framework import FlowTestFramework
from utils import get_flow


@pytest.fixture
def flow() -> FlowTestFramework:
    """
    Return a flow loaded with all the functions
    from the latest auto-generated files from the Mini-lisp book
    """
    return get_flow()


@pytest.fixture
def files_dir():
    """
    return the directory with the input & expected files.
    """
    directory = "./book_evaluate/"
    return Path(directory)


def test_book_evaluate(flow, files_dir):
    """
    All the tests for all the Lisp evaluate functions,
    which auto generated from the Mini-lisp book.

    `flow` already loaded with all the functions from the books
    (mini-lisp process is running).

    Read more about this flow here:
        https://github.com/yossigil/safot/tree/master/Mini-Lisp.ShellTestFramework#evaluate
    """
    input_files = sorted(glob.glob(f"{files_dir}/*.lisp.in"))
    for in_file in input_files:
        # Check if this input file has expected file with the same name:
        expected = f'{in_file.split(".")[0]}.lisp.out'
        if not Path(expected).exists():
            print(f"Failed to find expected output file for: {in_file}")
            continue

        # Run the input file and compare output with expected:
        print(f"Running: {in_file}")
        out_file = flow.run_s_expr_file(in_file)
        assert Path(out_file).read_text() == Path(expected).read_text()
        print(f"Passed.")
