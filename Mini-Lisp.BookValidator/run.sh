#!/bin/bash
###########################################
# Script to generate lisp files from
# the Mini-lisp book, compile them,
# run, and validate them with the expected.
#
# In case of diffs between out and expected,
# the diffs will be print and the flow will stop
# and return 0.
#
# Steps:
#   1. Remove all the lisp files from the
#      input dir.
#
#   2. Generate all the lisp files
#      from the book into the input dir.
#
#   3. Compile all the functions files.
#
#   4. Run each s-expression file, and
#      compare the results with the expected
#      file.
#      (stop the flow if there are any diffs).
#
#   5. Finish.
#      (meaning all the outputs equal to expected)
#
# Usage:
#    %  run.sh
#
# Returns:
#    1 if all the output files are equal to
#    expected files, else 0.
#
# Notes:
#    The script is using the script:
#       ./Mini-Lisp.ShellTestFramework/run_flow.sh
#
#    Thus it requires python3.
#    Install:
#        % make install -C ./Mini-Lisp.ShellTestFramework/build/
#
###########################################
# Define paths:
SCRIPT_PATH=`realpath $0`
SCRIPT_DIR=`dirname ${SCRIPT_PATH}`
MINI_LISP_INPUTS_DIR=${SCRIPT_DIR}/Mini-Lisp.Inputs/
MINI_LISP_EXPECTED_DIR=${SCRIPT_DIR}/Mini-Lisp.Expected/
RUN_FLOW_SCRIPT=${SCRIPT_DIR}/../Mini-Lisp.ShellTestFramework/bin/run_flow.sh

echo "========================================================="
echo "INFO: Generate lisp files from the book ... "

echo "INFO: Clean old lisp files ... "
make clean -C ${MINI_LISP_INPUTS_DIR}

echo "INFO: Generate new lisp files from the book ... "
make all -C ${MINI_LISP_EXPECTED_DIR}

echo "========================================================="
echo "INFO: Input directory  : ${MINI_LISP_INPUTS_DIR}"
echo "INFO: Expected directory : ${MINI_LISP_EXPECTED_DIR}"
echo "INFO: Start the flow ... "

${RUN_FLOW_SCRIPT} ${MINI_LISP_EXPECTED_DIR} ${MINI_LISP_INPUTS_DIR}/*.lisp
