const REPLInstigator = require('./REPLInstigator')
const PEGParserStateWrapper = require('./PEGParserStateWrapper')
const TextHighlighter = require('./TextHighlighter')
const primitiveKeywords = require('./PrimitiveKeywords')
const config = require('./Configuration').browserTerminal
const defaultColor = require('./Configuration').format.color.default
const formatter = require('./Formatter')
require('./ArrayExtension')

window.$ = require('jquery')
require('jquery.terminal')($)

$('body').append('<p id="a"></p>')
$('body').append('<p id="b"></p>')
$('body').append('<p id="c"></p>')
$('body').append('<p id="d"></p>')
$('body').append('<p id="e"></p>')
const printA = str => document.getElementById('a').innerHTML = 'a ' + str
const printB = str => document.getElementById('b').innerHTML = 'b ' + str
const printC = str => document.getElementById('c').innerHTML = 'c ' + str
const printD = str => document.getElementById('d').innerHTML = 'd ' + str
const printE = str => document.getElementById('e').innerHTML = 'e ' + str

//TODO: remove

module.exports = class BrowserTerminal {
	static CompletionPrefixes = "()[]".split('').append('')
	static ParagraphId = 'repl_terminal'

	constructor() {
		this.globals = []
		this.initCompletions()
		
		this.repl = new REPLInstigator(this, this)	
		this.highlighter = new TextHighlighter()
		this.formatterWrapper = new PEGParserStateWrapper(formatter)

		this.initFormatters()
		this.initTerminal()
	}

	initTerminal() {
		const id = BrowserTerminal.ParagraphId
		$('head').append('<link rel="stylesheet" type="text/css"\
							href="jquery.terminal.css"/>')
		$('body').append(`<p id="${id}"></p>`)	

		const self = this
		$(function($, undefined) {
			self.terminal = $(`#${id}`).terminal(function(line) { 
				self.repl.feedLine(line) 
			}, config)
		})
	}

	initFormatters() {
		$.terminal.new_formatter(str => {
			// str = $.terminal.unescape_brackets(str)
			const formatResult = this.formatterWrapper.apply(str)
			switch (formatResult.type) {
				case PEGParserStateWrapper.Accepted:
					return formatResult.output

				case PEGParserStateWrapper.ExpectedMore:
					return this.applyDefaultColor(str)

				case PEGParserStateWrapper.Rejected:
					const offset = formatResult.offset
					return 	formatter.parse(str.slice(0, offset)) +
							this.applyDefaultColor(str.slice(offset))
			}
		})	
	}

	initCompletions() {
		$.terminal.defaults.completion = []
		this.completions = $.terminal.defaults.completion
		primitiveKeywords.forEach(w => this.addCompletion(w))
	}

	applyDefaultColor(str) {
		return this.highlighter.apply(str, defaultColor)
	}

	addCompletion(word) {
		BrowserTerminal.CompletionPrefixes.forEach(p => {
			this.completions.push(p + word)	
		})
	}

	getCursorPosition()  {
		return this.terminal?.cmd()?.position()
	}

	/* REPLInstigator delegate */
	prompt(promptStr) {
		this.terminal?.set_prompt(promptStr)
	}

	echo(str) {
		this.terminal?.echo(str)
	}

	/* Formatter Delegate */
	matchEnclosures(lEncPos, rEncPos) {
		const cursorPos = this.getCursorPosition()

		if (isNaN(cursorPos) 		||
			cursorPos < lEncPos 	|| 
			cursorPos > rEncPos) {
			return null
		}
		
		const isInner = ![
			lEncPos - 1, lEncPos, rEncPos, lEncPos + 1
		].includes(cursorPos)

		return { isInner: isInner }
	}

	getGlobals() {
		return this.globals
	}

	/* REPLInstigator Observer */
	globalAdded(globalValue) {
		this.globals.push(globalValue)
		this.addCompletion(globalValue)
	}
}
