import pytest
import os
from lib.flow_test_framework import FlowTestFramework


@pytest.fixture
def flow():
    """
    Pre-process function.
    This function occur before the flow tests.

    Pre-process steps:
        1. Generate the latest lisp files from the book.
        2. Get the relevant functions files for this test
        3. Open flow
        4. Compiled all functions
        5. return flow
    """
    # Define inputs:
    directory = "../../../Mini-Lisp.Inputs/"
    interpreter = "../../../Mini-Lisp.Chic/mini-lisp"

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


def test_exists(flow, input_dir, golden_dir):
    """
    Mini-lisp test for: exists

    Using the exists.lisp file,
    auto generated from the Mini-lisp book
    """
    raise NotImplementedError


def test_is_atomic(flow, input_dir, golden_dir):
    """
    Mini-lisp test for: is_atomic

    Using the isAtomic.lisp file,
    auto generated from the Mini-lisp book
    """
    raise NotImplementedError


def test_lookup(flow, input_dir, golden_dir):
    """
    Mini-lisp test for: lookup

    Using the lookup.lisp file,
    auto generated from the Mini-lisp book
    """
    raise NotImplementedError


def test_bind(flow, input_dir, golden_dir):
    """
    Mini-lisp test for: bind

    Using the bind.lisp file,
    auto generated from the Mini-lisp book
    """
    raise NotImplementedError


def test_apply_trivial_atomic(flow, input_dir, golden_dir):
    """
    Mini-lisp test for: apply_trivial_atomic

    Using the applyTrivialAtomic.lisp file,
    auto generated from the Mini-lisp book
    """
    raise NotImplementedError


def test_apply_eager_atomic(flow, input_dir, golden_dir):
    """
    Mini-lisp test for: apply_eager_atomic

    Using the applyEagerAtomic.lisp file,
    auto generated from the Mini-lisp book
    """
    raise NotImplementedError


def test_evaluate(flow, input_dir, golden_dir):
    """
    Mini-lisp test for: evaluate

    Using the eval.lisp file,
    auto generated from the Mini-lisp book
    """
    raise NotImplementedError


def test_evaluate_list(flow, input_dir, golden_dir):
    """
    Mini-lisp test for: evaluate_list

    Using the evaluateList.lisp file,
    auto generated from the Mini-lisp book
    """
    raise NotImplementedError


def test_apply_atomic(flow, input_dir, golden_dir):
    """
    Mini-lisp test for: apply_atomic

    Using the applyAtomic.lisp file,
    auto generated from the Mini-lisp book
    """
    raise NotImplementedError


def test_evaluate_atomic(flow, input_dir, golden_dir):
    """
    Mini-lisp test for: evaluate_atomic

    Using the evaluateAtomic.lisp file,
    auto generated from the Mini-lisp book
    """
    raise NotImplementedError


def test_evaluate_cond(flow, input_dir, golden_dir):
    """
    Mini-lisp test for: evaluate_cond

    Using the evaluateCond.lisp file,
    auto generated from the Mini-lisp book
    """
    raise NotImplementedError


def test_apply_decomposed_lambda(flow, input_dir, golden_dir):
    """
    Mini-lisp test for: apply_decomposed_lambda

    Using the applydecomposedLambda.lisp file,
    auto generated from the Mini-lisp book
    """
    raise NotImplementedError


def test_apply(flow, input_dir, golden_dir):
    """
    Mini-lisp test for: apply

    Using the apply.lisp file,
    auto generated from the Mini-lisp book
    """
    raise NotImplementedError


@pytest.fixture
def input_dir():
    """
    return the input directory
    """
    directory = "../../../Mini-Lisp.Inputs/"
    return directory


@pytest.fixture
def golden_dir():
    """
    return the golden directory
    """
    directory = "../lisp_files/"
    return directory
