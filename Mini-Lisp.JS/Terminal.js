const ParserStateWrapper = require('./ParserStateWrapper')
const Engine = require('./Engine')
const format = require('./Formatter').parse
const TextHighlighter = require('./TextHighlighter')
const primitiveKeywords = require('./PrimitiveKeywords')

window.$ = require('jquery')
require('jquery.terminal')($)

require('./ArrayExtension')

$('head').append('<link rel="stylesheet" type="text/css" href="jquery.terminal.css"/>')

//TODO: remove
$('body').append('<p id="a"></p>')
$('body').append('<p id="b"></p>')
$('body').append('<p id="c"></p>')
const printA = str => document.getElementById('a').innerHTML = str
const printB = str => document.getElementById('b').innerHTML = str
const printC = str => document.getElementById('c').innerHTML = str

module.exports = class Terminal {
	static CompletionPrefixes = "()[]".split('').append('')

	constructor() {
		this.initRepl()
		this.initFormatters()

		this.globals = []

		$.terminal.defaults.completion = []
		this.completions = $.terminal.defaults.completion
		primitiveKeywords.forEach(w => this.addCompletion(w))

		this.pw = new ParserStateWrapper()
		this.th = new TextHighlighter()
		this.engine = new Engine(this)
	}

	getGlobals() {
		return this.globals
	}

	getCursorPosition()  {
		return $('#repl').terminal().cmd()?.position()
	}

	initRepl() {
		const wrapper = this
		$('body').append('<p id="repl"></p>')

		$(function($, undefined) {
			let commandBuffer = ''
			$('#repl').terminal(function(line) {
			    commandBuffer += line + '\n'
			    const parseResult = wrapper.pw.parse(commandBuffer)
			 	switch (parseResult.type) {
				case ParserStateWrapper.Accept:
					try {
						this.echo(wrapper.engine.evaluate(parseResult.output).toString())	
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
				prompt: '> ',
				caseSensitiveAutocomplete : false
			})
		})
	}

	initFormatters() {
		$.terminal.defaults.formatters.unshift((str, options) => {
			try {
				const f = format(str)
				printA('')
				return f
			} catch (e) {
				printA(e.stack)
				if (e.found !== null) {
					const offset = e.location.start.offset
					return 	format(str.slice(0, offset)) +
							this.applyDefaultColor(str.slice(offset))
				}

				return this.applyDefaultColor(str)
			}
		})	
	}

	applyDefaultColor(str) {
		return this.th.highlight(str, '#d7deea')
	}

	addCompletion(word) {
		Terminal.CompletionPrefixes.forEach(p => {
			this.completions.push(p + word)	
		})
	}

	/* Engine Observer */
	globalAdded(globalAtom) {
		const value = globalAtom.getValue()
		this.globals.push(value)
		this.addCompletion(value)
	}
}

