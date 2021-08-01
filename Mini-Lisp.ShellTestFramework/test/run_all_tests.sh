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
    # Enter unit-test directory:
    SCRIPT=`realpath $0`
    SCRIPT_PATH=`dirname $SCRIPT`
    cd ${SCRIPT_PATH}/unit

    # Run all tests:
    pytest -rA

    # Go back to directory:
    cd -
}

check_configurations
run_pytest
