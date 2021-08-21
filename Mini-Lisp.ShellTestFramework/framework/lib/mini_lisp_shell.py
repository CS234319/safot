import sys

import pexpect
import logging
import os
import re
from time import sleep
from pathlib import Path
import tempfile

class MiniLispShell:
    """
    This class represents a mini-lisp shell.
    It can feed the shell, and get the output from it.

    This class supporting the "with" statement,
    thus you don't need to call directly to start_mini_lisp/close_mini_lisp.

    Test file:
        ./test/unit/test_mini_lisp_shell.py

    For example:
        >> from framework.lib.mini_lisp_shell import MiniLispShell
        >>
        >> with MiniLispShell("../../Mini-Lisp.Chic/mini-lisp") as shell:
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
        self.log_idx = 0

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
            timeout=2,
            maxread=1)
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

    def feed(self, input_str: str) -> str:
        """
        Feed the shell and get the output

        :param input_str: input for mini-lisp shell
        :return: stdout + stderr
        """
        if not self.shell:
            raise Exception("Must call start_mini_lisp() first")
        if input_str == "":
            return ""

        logging.debug(f"Feed: {input_str}")
        self.shell.sendline(input_str)
        sleep(0.001)
        self.shell.read_nonblocking(size=1, timeout=None)
        raw = self.log.read_text().replace("\x00", "")
        self.log.write_text("")
        out = re.sub(r"\r|- |\?|> ", "", raw)
        out = out[:-1]
        if out.isspace():
            out = ""
        return out

    @staticmethod
    def _check_if_executable_exists(path: str) -> None:
        """
        Check if executable exists, by checking if the file
        exists + checking if permission mode is X

        :param path: path of the exe
        """
        logging.debug("Check if the interpreter file exists and can be run ...")
        if Path(path).is_file() is False:
            logging.error(f"No such file: {path}")
            raise FileNotFoundError(path)
        if os.access(path, os.X_OK) is False:
            logging.error(f"File {path} can't be run as mini-lisp interpreter (file mode is not x).")
            raise PermissionError(path)
