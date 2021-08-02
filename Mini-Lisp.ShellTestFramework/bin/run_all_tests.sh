#!/bin/bash
###########################################
# Script to run all the python unit-tests
# of the Mini-Lisp shell.

# Usage:
#   Run all unit-tests:
#       > run_all_tests.sh unit
#
#   Run all flow-tests:
#       > run_all_tests.sh flow
#
#   Run all both:
#       > run_all_tests.sh all
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

function run_unit_tests() {
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

function run_flow_tests() {
    # Get flow-test directory:
    SCRIPT=`realpath $0`
    SCRIPT_PATH=`dirname $SCRIPT`
    FLOW_TESTS_DIR=${SCRIPT_PATH}/../test/flow
    export PYTHONPATH="${PYTHONPATH}:${SCRIPT_PATH}/../"
    cd ${FLOW_TESTS_DIR}

    # Run all tests:
    pytest -rA

    # Restore pwd:
    cd - &> /dev/null
}

check_configurations

if [ "$1" == "unit" ]; then
  run_unit_tests
fi

if [ "$1" == "flow" ]; then
  run_flow_tests
fi

if [ "$1" == "all" ]; then
  run_unit_tests
  run_flow_tests
fi

