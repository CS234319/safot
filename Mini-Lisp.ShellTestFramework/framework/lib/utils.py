import re
import os
import glob
import logging
import tempfile
from typing import List
from pathlib import Path
from framework.lib.flow_runner import FlowRunner, FileType
from framework.lib.flow_test_framework import FlowTestFramework


def generate_book_files(verbose=True) -> None:
    """
    Auto-generated the files from the book (+ remove all the existing before)
    """
    redirect = ""
    if verbose:
        redirect = " > /dev/null"
    directory = "../../../Mini-Lisp.BookValidator/Mini-Lisp.Inputs/"
    command = f"make clean -C {directory} {redirect}"  # delete old lisp files:
    os.system(command)
    command = f"make all -C {directory} {redirect}"  # generate new lisp files:
    os.system(command)


def get_evaluate_functions_names() -> List[str]:
    return [
        "quote",
        "null",
        "exists",
        "is-atomic",
        "lookup",
        "bind",
        "apply-trivial-atomic",
        "apply-eager-atomic",
        "evaluate",
        "evaluate-list",
        "apply-atomic",
        "evaluate-atomic",
        "evaluate-cond",
        "apply-decomposed-lambda",
        "apply",
    ]


def get_functions_files() -> List[str]:
    """
    Get all the files from the book, which are represents function definitions

    :return: list of paths
    """
    directory = "../../../Mini-Lisp.BookValidator/Mini-Lisp.Inputs/"
    files = [f for f in glob.glob(f"{directory}/*.lisp")]
    return FlowRunner.categorize_files_by_name(files)[FileType.FUNCTION]


def get_env(flow) -> str:
    """
    Build an alist string, using the loaded flow

    :return: alist string
    """
    names = get_evaluate_functions_names()
    alist = "t.t nil.nil "
    for name in names:
        lambda_expr = flow.feed(f"(eval '{name})")
        alist += f"{name}.{lambda_expr} "
    return alist


def get_flow(compile_book=True, filter_newline=True) -> FlowTestFramework:
    """
    Returns a new flow, loaded with all the book, by the following steps:
        1. Generate the latest lisp files from the book.
        2. Open the flow and start the communication with the interpreter
        4. Compiled all the lisp functions from the book
        5. return the new flow

    :return: flow loaded with all the book
    """
    if compile_book is True:
        generate_book_files()
    flow = FlowTestFramework(mini_lisp="../../../Mini-Lisp.ChicDor/mini-lisp", filter_newline=filter_newline)
    for file in get_functions_files():
        flow.load_function_file(file)
    return flow


def generate_input_file(s_expr: str) -> Path:
    """
    Helper function, which create a single file,
    with all the mini-lisp book + 1 s_expr.

    Using this function, mostly for debugging:
        py:
            > in_file = generate_input_file("(car '(a b))")

        bash:
            % ./mini-lisp < in_file
            A

    :param s_expr: string represents s-expression
    :return: Path object
    """
    _, in_file = tempfile.mkstemp(".in.lisp")
    logging.debug(f"Creating input file: {in_file}")
    with open(in_file, mode='a') as stream:
        # Write all functions from the book:
        for file in get_functions_files():
            stream.write(Path(file).read_text())
            stream.write("\n")

        # Add the s-expr:
        stream.write(s_expr)
        stream.write("\n")

    return Path(in_file)
