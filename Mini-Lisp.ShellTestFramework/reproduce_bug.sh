# Reproduction of memory exhausted bug.
# issue-456

SCRIPT_PATH=`realpath $0`
SCRIPT_DIR=`dirname ${SCRIPT_PATH}`
FLOW_TESTS_DIR="${SCRIPT_DIR}/test/flow"
export PROJECT_DIR=`realpath "${SCRIPT_DIR}"`
export PYTHONPATH="${PYTHONPATH}:${PROJECT_DIR}/"
cd $FLOW_TESTS_DIR &> /dev/null
python3 reproduce_memory_exhaustion.py
cd - &> /dev/null
