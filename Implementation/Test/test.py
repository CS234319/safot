import glob
import logging
import os
import pexpect
import pytest
import re
import sys
import tempfile

from enum import Enum
from pathlib import Path
from time import sleep
from typing import List, Dict, Union
from pathlib import Path

class MiniLispShell:
    """
    This class represents a mini-lisp shell.  It can feed the shell, and get
    the output from it.

    This class supporting the "with" statement,
    thus you don't need to call directly to start_mini_lisp/close_mini_lisp.

    Test file:
        test_mini_lisp_shell.py

    For example:
        >> from framework.lib.mini_lisp_shell import MiniLispShell
        >>
        >> with MiniLispShell("../../Mini-Lisp.ChicDor/mini-lisp") as shell:
        >>     out1 = shell.feed("()")
        >>     out2 = shell.feed("(car '(a b))")
        >>     print(out1)
        >>     NIL
        >>     print(out2)
        >>     A

    The same example, but without using the with statement:
        >> shell = MiniLispShell("./mini-lisp")
        >> shell.start_mini_lisp()
        >> out1 = shell.feed("()")
        >> out2 = shell.feed("(car '(a b))")
        >> print(out1)
        >> NIL
        >> print(out2)
        >> A
        >> shell.close_mini_lisp()
    """

    def __init__(self, mini_lisp: str):
        self._check_if_executable_exists(mini_lisp)
        self.mini_lisp = mini_lisp
        self.shell = None
        self.log_fd, self.log_path = tempfile.mkstemp()
        self.log = Path(self.log_path)

    def __enter__(self):
        return self.start_mini_lisp()

    def __exit__(self, exception_type, exception_value, exception_traceback):
        self.close_mini_lisp()
        if exception_type == AssertionError:
            raise AssertionError(exception_value)

    def __del__(self):
        self.close_mini_lisp()
        os.close(self.log_fd)
        self.log.unlink()

    def start_mini_lisp(self):
        """
        Start mini-lisp shell
        """
        self.shell = pexpect.spawn(
            self.mini_lisp,
            encoding='utf-8',
            echo=False,
            timeout=6,
            maxread=1
        )
        if self.log.exists():
            self.log.unlink()
        self.log.touch()
        self.shell.logfile_read = self.log.open('w')
        return self

    def close_mini_lisp(self):
        """
        Close mini-lisp shell
        """
        if self.shell:
            self.shell.stdin.close()
            self.shell.close()

    def feed(
            self,
            input_str: str,
            filter_pattern=r"\r|- |\?|> ",
            stack_trace_message="Traceback",
            filter_newline=True,
            traceback=False
    ) -> str:
        """
        Feed the shell with 1 line, and get the output.

        :return: stdout + stderr
        """
        if not self.shell:
            raise Exception("Must call start_mini_lisp() first")
        if input_str == "":
            return ""

        logging.debug(f"Feed: {input_str}")
        self.shell.sendline(input_str)
        self.shell.expect("\n", timeout=None)
        if stack_trace_message in self.log.read_text() or "... While applying" in self.log.read_text():
            self._get_all_lines()
        raw = self.log.read_text().replace("\x00", "")
        self.log.write_text("")
        out = re.sub(filter_pattern, "", raw)
        out = out[:-1]
        if (stack_trace_message in out or "... While applying" in out) and traceback is False:
            out = list(out.split("\n"))[-1]
        if out.isspace():
            out = ""
        if filter_newline is False:
            out = out.replace("\n", "")
        return out

    def _get_all_lines(self):
        while "Error" not in self.log.read_text():
            self.shell.expect("\n", timeout=None)

    @staticmethod
    def _check_if_executable_exists(path: str) -> None:
        """
        Check if executable exists, by checking both whether the file
        exists, and is executable 

        :param path: path of the exe
        """
        logging.debug("Check if the interpreter file exists and can be run ...")
        if Path(path).is_file() is False:
            logging.error(f"{path}: File not found")
            raise FileNotFoundError(path)
        if os.access(path, os.X_OK) is False:
            logging.error(f"{path}: is not executable.")
            raise PermissionError(path)


@pytest.fixture
def shell():
    if "MINI_LISP_SHELL" not in os.environ:
        raise EnvironmentError
    shell = MiniLispShell(os.getenv('MINI_LISP_SHELL'))
    shell.start_mini_lisp()
    return shell

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



class FileType(Enum):
    FUNCTION = 0
    S_EXPR = 1


class FlowRunner:
    @staticmethod
    def run(files: List[str], golden_dir: str) -> bool:
        """
        Run the full flow:
            1. Init FlowTestFramework
            2. Categorize files by name (function or s_expr)
            3. Compile all functions
            4. Run all s_expr
            5. Return output files for each run of s_expr file

        :param files: lisp files to run (can be functions or s_expr files)
        :param golden_dir: dir with the golden outputs
        :return: True if all output files are equal to golden files, else False
        """
        # Check golden dir path:
        golden_path = Path(golden_dir)
        if not golden_path.exists():
            logging.error(f"No such directory: {golden_dir}")
            return False

        # Initialize the interpreter:
        if "MINI_LISP_SHELL" not in os.environ:
            raise EnvironmentError("Error: environment variable MINI_LISP_SHELL undefined")
        flow = FlowTestFramework(os.getenv('MINI_LISP_SHELL'))

        # Categorize files:
        categorized_files = FlowRunner.categorize_files_by_name(files)

        # Compile all functions/lib files:
        for file in categorized_files[FileType.FUNCTION]:
            logging.info(f"Compiling file {file} ...")
            flow.injectFile(file)

        # Running s_expr files and compare:
        for file in categorized_files[FileType.S_EXPR]:
            # Run:
            logging.info(f"Running {file} ...")
            out_file = Path(flow.run_s_expr_file(file))
            logging.info(f"Output file {out_file} ...")

            # Get golden:
            golden_file = golden_path / f"{out_file.name}"
            if not golden_file.exists():
                logging.error(f"Failed to find golden file in: {golden_file}")
                continue

            # Compare:
            logging.info(f"Comparing file {out_file} with {golden_file} ...")
            if Path(out_file).read_text() != golden_file.read_text():
                logging.error(f"Output file and golden file are not equal")
                logging.error(f"Diff:")
                os.system(f"diff {out_file} {golden_file}")
                return False

        logging.info(f"Successfully run and compare all the files.")
        return True

    @staticmethod
    def categorize_files_by_name(files: List[str]) -> Dict[FileType, List[str]]:
        files_dict = {FileType.FUNCTION: [], FileType.S_EXPR: []}
        for file in files:
            if not Path(file).exists():
                logging.error(f"No such file: {file}")
                continue
            if FlowTestFramework.is_function_file(file):
                files_dict[FileType.FUNCTION].append(file)
            else:
                files_dict[FileType.S_EXPR].append(file)
        return files_dict


class FlowTestFramework:
    """
    This class represents a test framework to run lisp files, using the
    interpreter, compile functions and evaluate S-expression, compare the
    results with golden output files.
    """
    def __init__(self, mini_lisp: str, filter_newline=True):
        self.shell = MiniLispShell(mini_lisp)
        self.shell.start_mini_lisp()
        self.filter_newline = filter_newline

    def __del__(self):
        if self.shell:
            self.shell.close_mini_lisp()

    def injectFile(self, file: str) -> None:
        """
        Feed the mini-lisp interpreter with functions declaration. (1 or more)

        :param file: input file with the functions declarations
        """
        for line in self.split_file(file):
            self.shell.feed(line)

    def run_s_expr_file(self, file: str) -> str:
        """
        Feed the mini-lisp interpreter with s_expression (1 or more),
        and write the results in temp file.

        :param file: input file with the s_expression
        :return: tmp file path
        """
        out_path = Path(tempfile.gettempdir()) / f"{Path(file).name}.out"
        if out_path.exists():
            out_path.unlink()
        out_path.touch()
        with open(out_path, mode='a') as stream:
            for line in self.split_file(file):
                out = self.feed(line)
                if out == "":
                    continue
                stream.write(out)
                stream.write('\n')
        return str(out_path)

    def feed(self, line) -> str:
        """
        Wrapper to MiniLispShell feed.

        :return: output string
        """
        return self.shell.feed(line, filter_newline=self.filter_newline)

    def interactive(self):
        """
        Interactive shell mode:
        communicate with the mini-lisp interpreter in real-time
        """
        logging.info("Interactive shell mode running ...")
        while True:
            try:
                line = input("> ")
                print(self.shell.feed(line))
            except EOFError:
                break
            except KeyboardInterrupt:
                break
        logging.info("Interactive shell mode finished ...")

    @staticmethod
    def split_file(file: str) -> List[str]:
        return list(filter(None, Path(file).read_text().splitlines()))

    @staticmethod
    def is_function_file(file: Union[str, Path]) -> bool:
        """
        Check if file is a lisp function file or not, by it's name.

        :param file: str or Path
        :return: True if file name represents function file, else False
        """
        # Convert to Path:
        if isinstance(file, str):
            file = Path(file)

        # Warn if suffix is not lisp:
        if file.suffix != '.lisp':
            logging.warning(f"Input file: {file} does not have endswith of '.lisp'")

        # Categorize file:
        s_expr_file_pattern = re.compile("(^lisp[0-9]+$)")
        file_name = file.name.split(".")[0]
        if s_expr_file_pattern.search(file_name):
            return False
        return True

    @staticmethod
    def update_golden(gold_path: str, out_path: str) -> None:
        """
        Update golden file for a test
        """
        Path(gold_path).write_text(Path(out_path).read_text())





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
"""
Mini-Lisp-evaluate on Mini-Lisp-evaluate
"""


@pytest.fixture
def flow() -> FlowTestFramework:
    """
    Return a flow loaded with all the functions
    from the latest auto-generated files from the Mini-lisp book
    """
    return get_flow(filter_newline=False)


@pytest.fixture
def files_dir():
    """
    return the directory with the input & expected files.
    """
    directory = "./evaluate_on_evaluate/"
    return Path(directory)


def test_evaluate_on_evaluate(flow, files_dir):
    """
    All the tests for all the Lisp evaluate on Lisp evaluate,
    which auto generated from the Mini-lisp book.

    `flow` already loaded with all the functions from the books
    (mini-lisp process is running)
    Meaning that the outer evaluate will use the C alist which already loaded.

    Read more about this flow here:
        https://github.com/yossigil/safot/tree/master/Mini-Lisp.ShellTestFramework#evaluateonevaluate
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
        Path(out_file).write_text("\n".join(Path(out_file).read_text().splitlines()[4::3]))  # filter results
        assert Path(out_file).read_text() == Path(expected).read_text()
        print(f"Passed.")


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
    assert shell.feed("(cdr (car 'a))") == "Error [CAR] in A"
    assert shell.feed("(bla)") == "Error [UNDEFINED] in BLA"
    assert shell.feed("(error)") == "Error [NIL] in (ERROR)"
    assert shell.feed("(error 'A)") == "Error [A] in (ERROR (QUOTE A))"
    assert shell.feed("(error 'message)") == "Error [MESSAGE] in (ERROR (QUOTE MESSAGE))"


def test_error_traceback(shell):
    """
    Check errors outputs with traceback
    """
    assert shell.feed("(car 'a)", traceback=True) == """\
Traceback (most recent call last):
\tFrom function CAR:
\t\tArgs: A
Error [CAR] in A"""
    assert shell.feed("(cdr 'a)", traceback=True) == """\
Traceback (most recent call last):
\tFrom function CDR:
\t\tArgs: A
Error [CDR] in A"""
    assert shell.feed("(cdr (car 'a))", traceback=True) == """\
Traceback (most recent call last):
\tFrom function CDR:
\t\tArgs: (CAR (QUOTE A))
\tFrom function CAR:
\t\tArgs: A
Error [CAR] in A"""
    assert shell.feed("(bla)", traceback=True) == "Error [UNDEFINED] in BLA"
    assert shell.feed("(error)", traceback=True) == """\
Traceback (most recent call last):
\tFrom function ERROR:
\t\tArgs: NIL
Error [NIL] in (ERROR)"""
    assert shell.feed("(error 'A)", traceback=True) == """\
Traceback (most recent call last):
\tFrom function ERROR:
\t\tArgs: A
Error [A] in (ERROR (QUOTE A))"""
    assert shell.feed("(error 'message)", traceback=True) == """\
Traceback (most recent call last):
\tFrom function ERROR:
\t\tArgs: MESSAGE
Error [MESSAGE] in (ERROR (QUOTE MESSAGE))"""


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


def test_injectFile(flow, input_dir):
    """
    Compile 2 functions: exists + id
    Run to s_expr files, which includes s_expr that use those functions.
    """
    # Define inputs:
    functions_file = f"{input_dir}/fun.lisp"
    s_expr_file_1 = f"{input_dir}/lisp01.lisp"
    s_expr_file_2 = f"{input_dir}/lisp02.lisp"

    # Compile functions:
    flow.injectFile(functions_file)

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
    if "MINI_LISP_SHELL" not in os.environ:
        raise EnvironmentError
    return FlowTestFramework(os.getenv('MINI_LISP_SHELL'))


@pytest.fixture
def input_dir():
    return "./examples"


def generate_book_files(verbose=True) -> None:
    """
    Auto-generated the files from the book (+ remove all the existing before)
    """
    redirect = ""
    if not verbose:
        redirect = " > /dev/null"
    directory = "Inputs/"
    command = f"make clean -C {directory} {redirect}"  # delete old lisp files:
    os.system(command)
    command = f"make all -C {directory} {redirect}"  # generate new lisp files:
    os.system(command)


def get_functions_files() -> List[str]:
    """
    Get all the files from the book, which represents function definitions

    :return: list of paths
    """
    directory = "../../../Mini-Lisp.BookValidator/Mini-Lisp.Inputs/"
    files = [f for f in glob.glob(f"{directory}/*.lisp")]
    return FlowRunner.categorize_files_by_name(files)[FileType.FUNCTION]


def get_flow(compile_book=True, filter_newline=True) -> FlowTestFramework:
    """
    Returns a new flow, loaded with all the book, by the following steps:
        1. Generate the latest lisp files from the book.
        2. Open the flow and start the communication with the interpreter
        4. Compile all the lisp functions from the book
        5. return the new flow

    :return: flow loaded with all the book
    """
    if compile_book is True:
        generate_book_files()
    if "MINI_LISP_SHELL" not in os.environ:
        raise EnvironmentError("Error: environment variable MINI_LISP_SHELL undefined")
    flow = FlowTestFramework(mini_lisp=os.getenv('MINI_LISP_SHELL'), filter_newline=filter_newline)
    for file in get_functions_files():
        flow.injectFile(file)
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



if __name__ == '__main__':
    if len(sys.argv) == 1:
        logging.error("Must provide golden dir and lisp files")
        exit()
    if len(sys.argv) == 2:
        logging.error("Must provide lisp files")
        exit()
    golden_dir = sys.argv[1]
    files = sys.argv[2:]
    logging.root.setLevel(logging.INFO)
    res = 1 if FlowRunner.run(files, golden_dir) is True else 0
    print(res)


