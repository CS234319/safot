.PHONY: install, parser, test, repl

parser: 
	pegjs Parser.pegjs

test:
	make parser
	npm test

repl:
	make parser
	node repl.js

install:
	npm uninstall jest
	npm install --save-dev jest
	npm install -g pegjs
