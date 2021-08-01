import sys
import logging
from enum import Enum
from pathlib import Path
from typing import List, Dict
from flow_test_framework import FlowTestFramework


class FileType(Enum):
    FUNCTION = 0
    S_EXPR = 1


class FlowRunner:

    @staticmethod
    def run(files: List[str]) -> List[str]:
        """
        Run the full flow:
            1. Init FlowTestFramework
            2. Categorize files by name (function or s_expr)
            3. Compile all functions
            4. Run all s_expr
            5. Return output files for each run of s_expr file

        :param files: lisp files to run (can be functions or s_expr files)
        :return: list of output files
        """
        # Init interpreter:
        flow = FlowTestFramework("../../../Mini-Lisp.Chic/mini-lisp")

        # Categorize files:
        categorized_files = FlowRunner.categorize_files_by_name(files)

        # Compile all functions/lib files:
        for file in categorized_files[FileType.FUNCTION]:
            logging.info(f"Compiling file {file} ...")
            flow.load_function_file(file)

        # Running s_expr files:
        out_files = []
        for file in categorized_files[FileType.S_EXPR]:
            logging.info(f"Running {file} ...")
            out_file = flow.run_s_expr_file(file)
            logging.info(f"Output file {out_file} ...")
            out_files.append(out_file)

        return out_files

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


if __name__ == '__main__':
    files = sys.argv[1:]
    logging.root.setLevel(logging.INFO)
    FlowRunner.run(files)
