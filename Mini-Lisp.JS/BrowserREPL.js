const ParserStateWrapper = require('./ParserStateWrapper')
const Engine = require('./Engine')
const GlobalsGatherer = require('./GlobalsGatherer')
const format = require('./Formatter').parse
const TextHighlighter = require('./TextHighlighter')

window.$ = require('jquery')
const terminal = require('jquery.terminal')($)

$('head').append('<link rel="stylesheet" type="text/css" \
		href="jquery.terminal.css"/>')
//TODO: remove
$('body').append('<p id="a"></p>')
$('body').append('<p id="b"></p>')
$('body').append('<p id="c"></p>')
$('body').append('<p id="d"></p>')
$('body').append('<p id="e"></p>')
const printA = str => document.getElementById('a').innerHTML = str
const printB = str => document.getElementById('b').innerHTML = str
const printC = str => document.getElementById('c').innerHTML = str
const printD = str => document.getElementById('d').innerHTML = str
const printE = str => document.getElementById('e').innerHTML = str

$('body').append('<p id="repl"></p>')

const gg = new GlobalsGatherer()
const e = new Engine(gg)
const pw = new ParserStateWrapper()
const th = new TextHighlighter()

const colorText = str => th.highlight(str, '#d7deea')

$.terminal.defaults.formatters.unshift((str, options) => {
	try {
		return format(str)
	} catch (e) {
		printA(e.stack)
		if (e.found !== null) {
			const offset = e.location.start.offset
			const a = format(str.slice(0, offset)) +
				   colorText(str.slice(offset))
			printA('')
			return a
		}
	}
	
	return colorText(str)
})

$(function($, undefined) {
	let commandBuffer = ''
	$('#repl').terminal(function(line) {
	    	commandBuffer += line + '\n'
	    	const parseResult = pw.parse(commandBuffer)
	    	switch (parseResult.type) {
		case ParserStateWrapper.Accept:
			try {
				this.echo(e.evaluate(parseResult.output).toString())	
			} catch (e) {
				this.error(`Error: ${e.s.car()} - ${e.s.cdr()}`)
			}
			this.set_prompt('> ')
			commandBuffer = ''
			break

		case ParserStateWrapper.ExpectMore:
			this.set_prompt(commandBuffer === '' ? '> ' : '- ')
			break

		case ParserStateWrapper.Reject:
			this.echo('?')
			commandBuffer = ''
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

const getGlobals = () => {
	return gg.getGlobals()
}

const getCursorPosition = () => {
	return $('#repl').terminal().cmd()?.position()
}

module.exports = {
	getGlobals: getGlobals,
	getCursorPosition: getCursorPosition
}
