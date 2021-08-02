#!/bin/bash
###########################################
# Script to run all the given lisp files.
# For functions files, no output file
# will generate.
#
# Args:
#   lisp files
#
# Usage:
#     run_flow.sh <file1> <file2> ...
#
# Example:
#     ./bin/run_flow.sh ./test/inputs/*
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
  # Get src directory:
  SCRIPT=`realpath $0`
  SCRIPT_PATH=`dirname $SCRIPT`
  SRC_DIR=${SCRIPT_PATH}/../framework/lib/
  export PYTHONPATH="${PYTHONPATH}:${SCRIPT_PATH}/../"
  cd ${SRC_DIR}

  # Run flow:
  python3 ${SRC_DIR}/flow_runner.py "$@"

  # Restore pwd:
  cd - &> /dev/null
}

check_configurations
flow_runner `realpath "$@" | tr "\n" " "`
