
MAKE_FILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
MAKE_FILE_DIR := $(dir $(MAKE_FILE_PATH))
RUN_SETUP := $(MAKE_FILE_DIR)/setup.sh

install:
	@$(RUN_SETUP)
