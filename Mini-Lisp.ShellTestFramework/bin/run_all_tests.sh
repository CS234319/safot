#!/bin/bash
###########################################
# Script to run all the python unit-tests
# of the Mini-Lisp shell.
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
  # Check if python exists:
  if [ -z `which python` ]; then
      echo "ERROR: Can't find python interpreter"
      exit
  fi

  # Check python version > 3:
  which python3 &> /dev/null
  if [ "$?" == "1" ]; then
    echo "ERROR: require python version > 3"
    exit
  fi

  # Check if pytest exists:
  pip show pytest &> /dev/null
  if [ "$?" == "1" ]; then
    echo "INFO: Installing pytest ..."
    pip install pytest
  fi
}

function run_pytest() {
    # Get unit-test directory:
    SCRIPT=`realpath $0`
    SCRIPT_PATH=`dirname $SCRIPT`
    UNIT_TESTS_DIR=${SCRIPT_PATH}/../test/unit
    export PYTHONPATH="${PYTHONPATH}:${SCRIPT_PATH}/../"
    cd ${UNIT_TESTS_DIR}

    # Run all tests:
    pytest -rA

    # Restore pwd:
    cd - &> /dev/null
}

check_configurations
run_pytest
