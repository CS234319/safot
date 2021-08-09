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
	npm install --save-dev jest
	npm install -g pegjs
	npm install memory-streams --save
