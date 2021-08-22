.PHONY: install, parser, test, repl, website

parser: 
	pegjs Parser.pegjs

test:
	make parser
	npm test

repl:
	make parser
	node repl.js

website:
	make parser
	browserify index.js -o bundle.js
	open -a "Google Chrome" index.html 

install:
	npm install --save-dev jest
	npm install --save memory-streams
	npm install --save jquery
	npm install --save jquery.terminal
	npm install -g pegjs
	npm install -g browserify
	