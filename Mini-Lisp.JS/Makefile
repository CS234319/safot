.PHONY: install, parser, formatter, test, repl, bundle, browser, website

parser: 
	pegjs Parser.pegjs

formatter:
	pegjs Formatter.pegjs

test:
	make parser
	npm test

repl:
	make parser
	node repl.js

bundle:
	browserify index.js > bundle.js

browser:
	open -a "Google Chrome" index.html

website:
	make parser
	make formatter
	make bundle
	make browser

install:
	npm install --save-dev jest
	npm install --save memory-streams
	npm install --save jquery
	npm install --save jquery.terminal
	npm install -g pegjs
	npm install -g browserify
	