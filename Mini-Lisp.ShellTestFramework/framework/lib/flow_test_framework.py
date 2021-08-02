import re
import tempfile
import logging
from pathlib import Path
from typing import List, Union
from framework.lib.mini_lisp_shell import MiniLispShell


class FlowTestFramework:
    """
    This class represents a test framework to run lisp files,
    using the interpreter, compile functions and evaluate s-expr,
    compare the results with golden output files.
    """

    def __init__(self, mini_lisp: str):
        self.shell = MiniLispShell(mini_lisp)
        self.shell.start_mini_lisp()

    def __del__(self):
        self.shell.close_mini_lisp()

    def load_function_file(self, file: str) -> None:
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
        _, out_file = tempfile.mkstemp(suffix=f"__{Path(file).name}.out")
        with open(out_file, mode='a') as stream:
            for line in self.split_file(file):
                out = self.shell.feed(line)
                if out == "":
                    continue
                stream.write(out)
                stream.write('\n')
        return out_file

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
