#!/bin/bash
###########################################
# Script to define all the environment
# variables necessary for the framework.
#
# Source this script in order to save
# the variables:
#     % source env.sh
###########################################

SCRIPT_PATH=`realpath ${BASH_SOURCE}`
SCRIPT_DIR=`dirname ${SCRIPT_PATH}`
PROJECT_DIR=`realpath "${SCRIPT_DIR}/../"`
unset PYTHONPATH
export PYTHONPATH="${PYTHONPATH}:${PROJECT_DIR}/"
