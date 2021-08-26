import re
import os
import glob
import logging
import tempfile
from typing import List
from pathlib import Path
from framework.lib.flow_runner import FlowRunner, FileType
from framework.lib.flow_test_framework import FlowTestFramework


def generate_book_files() -> None:
    """
    Auto-generated the files from the book (+ remove all the existing before)
    """
    directory = "../../../Mini-Lisp.BookValidator/Mini-Lisp.Inputs/"
    command = f"make clean -C {directory}"  # delete old lisp files:
    os.system(command)
    command = f"make all -C {directory}"  # generate new lisp files:
    os.system(command)


def get_evaluate_files() -> List[str]:
    """
    Get the list of the files for evaluate functions (including quote, null),
    which auto-generated from the book.

    :return: list of paths
    """
    directory = "../../../Mini-Lisp.BookValidator/Mini-Lisp.Inputs/"
    evaluate_functions = [
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
        # Includes quote + null:
        "quote",
        "null"
    ]
    return [f"{directory}/{f_name}.lisp" for f_name in evaluate_functions]


def get_functions_files() -> List[str]:
    """
    Get all the files from the book, which are represents function definitions

    :return: list of paths
    """
    directory = "../../../Mini-Lisp.BookValidator/Mini-Lisp.Inputs/"
    files = [f for f in glob.glob(f"{directory}/*.lisp")]
    return FlowRunner.categorize_files_by_name(files)[FileType.FUNCTION]


def get_lambda(file: str) -> str:
    """
    Given an input file which auto-generated from the book,
    which includes a function definitions, this function convert
    the function to lambda/nlambda definitions, used by the alist.

    For example:
        The following expression:
            "(defun my_fun (args ...) (body ...))"

        Will be converted by this function to:
            "my_fun.(lambda (args ...) (body ...))"

    :param file: lisp file
    :return: lambda/nlambda definition of the function
    """
    fun_str = Path(file).read_text()
    if "defun" in fun_str:
        fun_type = "defun"
        lambda_type = "lambda"
    elif "ndefun" in fun_str:
        fun_type = "ndefun"
        lambda_type = "nlambda"
    else:
        logging.warning(f"File: {file} has no function definitions. Skip.")
        return ""

    regex = rf"(\()(\s*)({fun_type})(\s+)(.*?)(\s*)(\()"
    subst = f"\\5.({lambda_type} \\6\\7"
    res = re.search(regex, fun_str, re.MULTILINE)
    if res:
        pair = re.sub(regex, subst, fun_str, 0, re.MULTILINE)
        return f"{pair} \n"

    # Pattern didn't match:
    logging.warning(f"Failed to parse: {file}")
    return ""


def get_env() -> str:
    """
    Build an alist string, using the functions from the book.

    :return: alist string (without parantheses)
    """
    files = get_evaluate_files()
    alist = "t.t nil.nil "
    for file in files:
        alist += f"{get_lambda(file)} "
    return f"{alist}"


def get_flow(polling=False, filter_newline=True) -> FlowTestFramework:
    """
    Returns a new flow, loaded with all the book, by the following steps:
        1. Generate the latest lisp files from the book.
        2. Open the flow and start the communication with the interpreter
        4. Compiled all the lisp functions from the book
        5. return the new flow

    :return: flow loaded with all the book
    """
    generate_book_files()
    flow = FlowTestFramework(mini_lisp="../../../Mini-Lisp.Chic/mini-lisp", polling=polling, filter_newline=filter_newline)
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
