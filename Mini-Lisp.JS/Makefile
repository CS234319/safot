.PHONY: install, parser, test

parser: 
	pegjs Parser.pegjs

test:
	make parser
	npm test

install:
	npm uninstall jest
	npm install --save-dev jest
	npm install -g pegjs
