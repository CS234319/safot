#!/bin/bash -f
#
# Run all the python unit-tests of the Mini-Lisp shell.
#
# Synopsis:
#       % run_all_tests.sh unit # Run unit tests:
#       % run_all_tests.sh flow # Run flow tests:
#       % run_all_tests.sh all  # Run both unit and flow tests

function check_configurations() {
  # Check python version > 3:
  which python3 &> /dev/null
  if [ "$?" == "1" ]; then
    echo "ERROR: require Python version > 3"
    exit
  fi

  # Check if pytest exists:
  pip show pytest &> /dev/null
  if [ "$?" == "1" ]; then
    echo "ERROR: Can't find pytest package"
    exit
  fi
}

function run_unit_tests() {
    cd $1
    python3 -m pytest -rA -vv --exitfirst
    cd - &> /dev/null
}

function run_flow_tests() {
    cd $1
    python3 -m pytest -rA -vv --exitfirst
    cd - &> /dev/null
}

check_configurations

SCRIPT_PATH=`realpath $0`
SCRIPT_DIR=`dirname ${SCRIPT_PATH}`
UNIT_TESTS_DIR="${SCRIPT_DIR}/../test/unit"
FLOW_TESTS_DIR="${SCRIPT_DIR}/../test/flow"

PROJECT_DIR=`realpath "${SCRIPT_DIR}/../"`
export PYTHONPATH="${PYTHONPATH}:${PROJECT_DIR}/"

echo "Running run_all_tests.sh ..."

# Compile mini-lisp:
export WORK_AROUND=1
if [[ -z "${MINI_LISP_SHELL}" ]]; then
    export MINI_LISP_SHELL=`realpath ${SCRIPT_DIR}/../../Mini-Lisp.ChicDor/mini-lisp`
fi
make clean all -C `dirname ${MINI_LISP_SHELL}` &> /dev/null

if [ "$1" == "unit" ]; then
  run_unit_tests ${UNIT_TESTS_DIR}
fi

if [ "$1" == "flow" ]; then
  run_flow_tests ${FLOW_TESTS_DIR}
fi

if [ "$1" == "all" ]; then
  run_unit_tests ${UNIT_TESTS_DIR}
  run_flow_tests ${FLOW_TESTS_DIR}
fi
