const REPLInstigator = require('./REPLInstigator')
const PEGParserStateWrapper = require('./PEGParserStateWrapper')
const primitiveKeywords = require('./PrimitiveKeywords')
const config = require('./Configuration').browserTerminal
const promptConfig = require('./Configuration').repl.prompt
const highlightingBrackets = require('./Configuration').highlightingBrackets
const formatter = require('./Formatter')
require('./ArrayExtension')

window.$ = require('jquery')
require('jquery.terminal')($)

module.exports = class BrowserTerminal {
	static CompletionPrefixes = "()[]".split('').append('')
	static ParagraphId = 'repl_terminal'
	static NumSpacesInTabAlternative = 4

	constructor() {
		this.globals = []

		this.initCompletions()
		this.initFormatting()
		this.initTerminal()
		this.initKeyboardEvents()
	}

	/* Terminal */
	initTerminal() {
		const id = BrowserTerminal.ParagraphId
		$('body').append(`<p id="${id}"></p>`)	
		$('head').append('<link rel="stylesheet" type="text/css"\
							href="jquery.terminal.css"/>')

		this.repl = new REPLInstigator(this, this)

		const self = this
		$(function($, undefined) {
			self.terminal = $(`#${id}`).terminal(function(line) {
				self.repl.feedLine(line)
			}, config)
		})
	}

	getCommand() {
		return this.shouldIgnoreCommand ? undefined : this.repl.getCommand()
	}

	/* Formatting */
	initFormatting() {
		this.formatterWrapper = new PEGParserStateWrapper(formatter)

		$.terminal.defaults.formatters = [str => {
			const command = this.getCommand()
			if (!command || !this.terminal) {
				return this.format(str)
			}

			return this.updateCommandFormat(str, command)
		}]
	}

	updateCommandFormat(str, command) {
			const fullCommand = command + str
			const numLines = fullCommand.split('\n').length
			const firstIndex = this.terminal.last_index() - numLines + 2
			const formatted = this.format(fullCommand).split(/\[\[[^\]]*\]\n\]/)
			const formattedCommandLines = formatted.slice(0, numLines - 1)
			const formattedStr = formatted[numLines - 1]
			
			formattedCommandLines.forEach((line, i) => {
				const lineIndex = firstIndex + i
				const prompt = i
					? promptConfig.duringCommand 
					: promptConfig.newCommand
				this.terminal.update(lineIndex, prompt + line, { formatters: false })
			})

			return formattedStr
	}

	format(str) {
		return [
			this.highlight, this.handleSpecialCharacters,
			this.applyNesting, this.partition
		].reduce((input, func) => func.call(this, input), str)
	}

	highlight(str) {
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

	applyNesting(str) {
		return $.terminal.nested_formatting(str)	
	} 

	partition(str) {
		return $.terminal.partition(str).join('')
	}

	/* Keyboard Events */
	initKeyboardEvents() {
		$.terminal.defaults.completion = (_, complete) => {
			this.handleTab(complete)
		}

		$.terminal.defaults.doubleTab = (_, rawCompletions) => {
			this.showPossibleCompletions(rawCompletions)
		}

		$.terminal.defaults.keydown = event => {
			if (event.code === 'Backspace') {
				this.handleBackspace()
			}
		}
	}

	getTabAlternative() {
		return Array
			.range(BrowserTerminal.NumSpacesInTabAlternative)
			.reduce(input => input + ' ', '')
	}

	handleTab(complete) {
		const beforeCursor = this.terminal.before_cursor()
		beforeCursor === '' || beforeCursor.endsWith(' ')
			? this.terminal.insert(this.getTabAlternative())
			: complete(this.completions)
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

	handleBackspace() {
		const beforeCursor = this.terminal.before_cursor()
		const tabAlternative = this.getTabAlternative()
		
		if (!beforeCursor.endsWith(tabAlternative)) {
			return
		}

		const command = this.terminal.get_command()
		const finalCursorPosition = beforeCursor.length - tabAlternative.length + 1
		
		this.terminal.set_command(
			beforeCursor.slice(0, finalCursorPosition) +
			command.slice(beforeCursor.length)
		)

		this.terminal.set_position(finalCursorPosition)
	}

	/* Completions */
	initCompletions() {
		this.completions = []
		primitiveKeywords.forEach(w => this.addCompletion(w))
	}

	addCompletion(word) {
		BrowserTerminal.CompletionPrefixes.forEach(p => {
			this.completions.push(p + word)	
		})
	}

	/* REPLInstigator Delegate */
	prompt(promptStr) {
		this.shouldIgnoreCommand = true
		this.terminal?.set_prompt(promptStr)
		this.shouldIgnoreCommand = false
	}

	echo(str) {
		this.shouldIgnoreCommand = true
		this.terminal?.echo(str)
		this.shouldIgnoreCommand = false
	}

	/* Formatter Delegate Auxiliary */
	getCursorPositionInCommand()  {
		return 	(this.getCommand()?.length ?? 0) + 
				(this.terminal.cmd().position())
				
	}

	/* Formatter Delegate */
	matchEnclosures(lEncPos, rEncPos) {
		const cursorPos = this.getCursorPositionInCommand()
		if (cursorPos < lEncPos || 
			cursorPos > rEncPos) {
			return null
		}
		
		const isInner = ![
			lEncPos, lEncPos + 1, rEncPos - 1, rEncPos
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
