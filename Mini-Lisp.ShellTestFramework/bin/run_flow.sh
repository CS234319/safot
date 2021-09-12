#!/bin/bash
###########################################
# Script to run all the given lisp files,
# and compare the results with golden.
#
# For functions files, no output file
# will generate.
#
# Args:
#     * golden dir
#     * lisp files
#
# Returns:
#     1 if all the output files are equal to
#     golden files, else if not will print the diffs,
#     and return 0.
#
# Usage:
#     % run_flow.sh <golden_dir> <file1> <file2> ...
#
# Example:
#     % ./bin/run_flow.sh \
#           ./test/golden/examples/ \
#           ./test/inputs/examples/*
#
# Example with an error (diff):
#     % ./bin/run_flow.sh \
#           ./test/golden/examples_with_diff/ \
#           ./test/inputs/examples/*
#
###########################################

function check_configurations() {
  # Check python version > 3:
  which python3 &> /dev/null
  if [ "$?" == "1" ]; then
    echo "ERROR: require python interpreter with version > 3"
    exit
  fi
}

function flow_runner() {
  cd ${PROJECT_DIR}/framework/lib/
  python3 ${PROJECT_DIR}/framework/lib//flow_runner.py $1 "${@:2}"
  cd - &> /dev/null
}

check_configurations

SCRIPT_PATH=`realpath $0`
SCRIPT_DIR=`dirname ${SCRIPT_PATH}`
UNIT_TESTS_DIR="${SCRIPT_DIR}/../test/unit"
FLOW_TESTS_DIR="${SCRIPT_DIR}/../test/flow"

export PROJECT_DIR=`realpath "${SCRIPT_DIR}/../"`
export PYTHONPATH="${PYTHONPATH}:${PROJECT_DIR}/"

echo "Running run_flow.sh ..."

# Compile mini-lisp:
export WORK_AROUND=1
make clean all -C ${SCRIPT_DIR}/../../Mini-Lisp.Chic/ &> /dev/null

flow_runner `realpath $1` `realpath "${@:2}" | tr "\n" " "`
