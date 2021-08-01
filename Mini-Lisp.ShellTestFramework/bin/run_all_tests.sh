#!/bin/bash
###########################################
# Script to run all the python unit-tests
# of the Mini-Lisp shell.
###########################################

function check_configurations() {
  # Check if python exists:
  if [ -z `which python` ]; then
      echo "ERROR: Can't find python interpreter"
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
    cd ${UNIT_TESTS_DIR}

    # Run all tests:
    pytest -rA --rootdir=${UNIT_TESTS_DIR}

    # Restore pwd:
    cd -
}

check_configurations
run_pytest
