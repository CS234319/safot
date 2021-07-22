all: 
	npm test

clean:
	rm yarn.lock

install:
	@if [[ ! -x "$(shell jest -v ghead)" ]]; then \
      echo 'jest does not exist. Please install it.'; \
      exit -1; \
  fi
