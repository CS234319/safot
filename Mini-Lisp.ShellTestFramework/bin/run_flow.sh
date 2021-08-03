#!/bin/bash
###########################################
# Script to run all the given lisp files.
# For functions files, no output file
# will generate.
#
# Args:
#     lisp files
#
# Usage:
#     > run_flow.sh <file1> <file2> ...
#
# Example:
#     > ./bin/run_flow.sh ./test/inputs/examples/*
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
  python3 ${PROJECT_DIR}/framework/lib//flow_runner.py "$@"
  cd -
}

check_configurations

SCRIPT_PATH=`realpath $0`
SCRIPT_DIR=`dirname ${SCRIPT_PATH}`
UNIT_TESTS_DIR="${SCRIPT_DIR}/../test/unit"
FLOW_TESTS_DIR="${SCRIPT_DIR}/../test/flow"

export PROJECT_DIR=`realpath "${SCRIPT_DIR}/../"`
export PYTHONPATH="${PYTHONPATH}:${PROJECT_DIR}/"

flow_runner `realpath "$@" | tr "\n" " "`
