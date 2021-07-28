.PHONY: test

test: Parser.pegjs
	npm test

Parser.js: Parser.pegjs

install:
	npm uninstall jest
	npm install --save-dev jest
	npm install -g pegjs
