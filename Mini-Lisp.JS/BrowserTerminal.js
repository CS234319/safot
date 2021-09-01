const REPLInstigator = require('./REPLInstigator')
const PEGParserStateWrapper = require('./PEGParserStateWrapper')
const primitiveKeywords = require('./PrimitiveKeywords')
const config = require('./Configuration').browserTerminal
const highlightingBrackets = require('./Configuration').highlightingBrackets
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
		this.formatterWrapper = new PEGParserStateWrapper(formatter)

		this.initFormatters()
		this.initTerminal()
	}

	initTerminal() {
		const id = BrowserTerminal.ParagraphId
		$('body').append(`<p id="${id}"></p>`)	
		$('head').append('<link rel="stylesheet" type="text/css"\
							href="jquery.terminal.css"/>')

		const self = this
		$(function($, undefined) {
			self.terminal = $(`#${id}`).terminal(function(line) { 
				self.repl.feedLine(line) 
			}, config)
		})
	}

	initFormatters() {
		const formatters = $.terminal.defaults.formatters

		// Adding highlight formatter before the nesting formatter
		const format = str => this.handleSpecialCharacters(this.format(str))
		formatters.unshift(format)	

		const formatPartition = str => {
			return $.terminal.partition(str).join('')
		}
		formatPartition.__meta__ = true

		// Adding format partitioning after the nesting formatter
		formatters.push(formatPartition)
	}

	initCompletions() {
		$.terminal.defaults.completion = []
		this.completions = $.terminal.defaults.completion
		primitiveKeywords.forEach(w => this.addCompletion(w))

		$.terminal.defaults.doubleTab = (_, rawCompletions) => {
			this.showPossibleCompletions(rawCompletions)
		}
	}

	showPossibleCompletions(rawCompletions) {
		const rawPrefixes = BrowserTerminal.CompletionPrefixes.filter(p => p !== '')
		const prefixes = rawPrefixes.concat(rawPrefixes.map(p => '\\' + p))
		const words = rawCompletions.map(c => {
			const prefix = prefixes.find(p => c.startsWith(p))
			return prefix ? c.slice(prefix.length) : c
		}).distinct()

		const wordsListStr = `(${words.join(' ')})`
		this.echo(wordsListStr)
	}

	format(str) {
		str = $.terminal.unescape_brackets(str)

		const formatResult = this.formatterWrapper.apply(str)
		switch (formatResult.type) {
			case PEGParserStateWrapper.Accepted:
				return formatResult.output

			case PEGParserStateWrapper.ExpectedMore:
				return str

			case PEGParserStateWrapper.Rejected:
				const offset = formatResult.offset
				const acceptedStr = str.slice(0, offset)
				const theRest = str.slice(offset)
				return formatter.parse(acceptedStr) + theRest 
		}
	}

	handleSpecialCharacters(str) {
		const { left, right } = highlightingBrackets
		
		return $.terminal.escape_brackets(str)
			.replace(new RegExp(`${left}`, 'g'), '[')
			.replace(new RegExp(`${right}`, 'g'), ']')
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
