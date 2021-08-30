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
const printA = str => document.getElementById('a').innerHTML = 'a ' + str
const printB = str => document.getElementById('b').innerHTML = 'b ' + str
const printC = str => document.getElementById('c').innerHTML = 'c ' + str
const printD = str => document.getElementById('d').innerHTML = 'd ' + str

//TODO: remove

module.exports = class BrowserTerminal {
	static CompletionPrefixes = "()[]".split('').append('')
	static ParagraphId = 'repl_terminal'

	constructor() {
		try {
		this.globals = []
		this.initCompletions()
		
		this.repl = new REPLInstigator(this, this)	
		this.highlighter = new TextHighlighter()
		this.formatterWrapper = new PEGParserStateWrapper(formatter)

		this.initFormatters()
		this.initTerminal()
		
		} catch (e) {
			printA(e.stack)
		}
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
		$.terminal.defaults.formatters.unshift(str => {
			try {
			const formatResult = this.formatterWrapper.parse(str)
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
		}catch (e) {
			printA(e.stack)
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
	matchParentheses(lparenPos, rparenPos) {
		const cursorPos = this.getCursorPosition()

		if (isNaN(cursorPos) 		||
			cursorPos < lparenPos 	|| 
			cursorPos > rparenPos) {
			return null
		}
		
		const isInner = ![
			lparenPos - 1, lparenPos, rparenPos, lparenPos + 1
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
