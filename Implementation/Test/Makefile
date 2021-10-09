MAKE_FILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
MAKE_FILE_DIR := $(dir $(MAKE_FILE_PATH))
RUN_SETUP := $(MAKE_FILE_DIR)/setup.sh

install:
	command -v python | sudo apt-get install python 
	command -v pip | sudo apt-get install python3.pip 
	pip3 install --ignore-installed pytest
	@$(RUN_SETUP)

clean:
	rm *~ *log
