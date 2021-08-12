const ParserStateWrapper = require('./ParserStateWrapper.js')
const Engine = require('./Engine.js')
window.$ = require('jquery')
const terminal = require('jquery.terminal')($)

const e = new Engine()
const pw = new ParserStateWrapper()

$('head').append('<link rel="stylesheet" type="text/css" \
		href="./node_modules/jquery.terminal/css/jquery.terminal.min.css"/>')
$('body').append('<p id="repl"></p>')
	
$(function($, undefined) {
	var buffer = ''
	$('#repl').terminal(function(line) {
    	buffer += line
    	const parseResult = pw.parse(buffer)
    	switch (parseResult.type) {
			case ParserStateWrapper.Accept:
				try {
					this.echo(e.evaluate(parseResult.output).toString())	
				} catch (e) {
					this.echo(`Error: ${e.s.car()} - ${e.s.cdr()}`)
				}
				this.set_prompt('> ')
				buffer = ''
				break

			case ParserStateWrapper.ExpectMore:
				this.set_prompt(buffer.length === 0 ? '> ' : '- ')
				break

			case ParserStateWrapper.Reject:
				this.echo('?')
				buffer = ''
				break
		}
	}, {
        greetings: 'Mini-LISP REPL',
        name: 'Mini-LISP',
        height: 500,
        width: 400,
        prompt: '> '
	})
})
