import sys
import logging
import os
from enum import Enum
from pathlib import Path
from typing import List, Dict
from framework.lib.flow_test_framework import FlowTestFramework


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

        # Init interpreter:
        if "MINI_LISP_SHELL" not in os.environ:
            raise EnvironmentError("Error: environment variable MINI_LISP_SHELL undefined")
        flow = FlowTestFramework(os.getenv('MINI_LISP_SHELL'))

        # Categorize files:
        categorized_files = FlowRunner.categorize_files_by_name(files)

        # Compile all functions/lib files:
        for file in categorized_files[FileType.FUNCTION]:
            logging.info(f"Compiling file {file} ...")
            flow.load_function_file(file)

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
