MAKE_FILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
MAKE_FILE_DIR := $(dir $(MAKE_FILE_PATH))
RUN_SETUP := $(MAKE_FILE_DIR)/setup.sh

test:

install:
	command -v python | sudo apt-get install python 
	command -v pip | sudo apt-get install python3.pip 
	pip3 install --ignore-installed pytest

# Compile mini-lisp:
export WORK_AROUND=1
if [[ -z "${MINI_LISP_SHELL}" ]]; then
    export MINI_LISP_SHELL=`realpath ${SCRIPT_DIR}/../../Mini-Lisp.ChicDor/mini-lisp`
fi
make all -C `dirname ${MINI_LISP_SHELL}` 

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


clean:
	rm *~ *log
