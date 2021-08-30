.PHONY: install, parser, formatter, test, repl, bundle, open_browser, website

parser: 
	pegjs Parser.pegjs

formatter:
	pegjs Formatter.pegjs

test:
	make parser
	npm test

repl:
	make parser
	node TerminalREPL.js

bundle:
	browserify index.js > bundle.js

open_browser:
	open -a "Google Chrome" index.html

website:
	make parser
	make formatter
	make bundle
	make open_browser

install:
	npm install --save-dev jest
	npm install --save memory-streams
	npm install --save jquery
	npm install --save jquery.terminal
	npm install -g pegjs
	npm install -g browserify
	