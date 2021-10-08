#!/bin/bash
###########################################
# Setup script.
# * Download python3 and pip3.
# * Download all the relevant packages.
#
# You can run this script directly,
# or via `make install`
#
###########################################

SCRIPT=`realpath $0`
SCRIPT_PATH=`dirname $SCRIPT`

# Check python version > 3:
which python3 &> /dev/null
if [ "$?" == "1" ]; then
  echo "============================================================="
  echo "INFO: Installing python3 and pip3 ..."
  sudo apt-get install python3.8 python3-pip
fi

echo "============================================================="
echo "INFO: Install all requirements ..."
pip3 install -r ${SCRIPT_PATH}/requirements.txt

echo "============================================================="
echo "INFO: Run 'source env.sh' to define PYTHONPATH"

