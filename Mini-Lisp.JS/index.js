const ParserStateWrapper = require('./ParserStateWrapper')
const Engine = require('./Engine')
const ParenthesesMatcher = require('./ParenthesesMatcher')
const Atom = require('./Atom')

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

class GlobalAdder {
	constructor() {
		this._globals = []
	}

	getGlobals() {
		return this._globals
	}

	/* Engine Observer */
	globalAdded(globalAtom) {
		this._globals.push(globalAtom.getValue())
	}
}

const ga = new GlobalAdder()
const e = new Engine(ga)
const pw = new ParserStateWrapper()
const pm = new ParenthesesMatcher()

let keywords = [
		'atom', 'car', 'cdr', 'cons', 'cond', 'defun', 'ndefun', 'eval',
		'eq', 'lambda', 'nlambda', 'null', 'quote', 'set'
	]

const highlightWithStyle = (str, style, color) => {
	return `[[${style};${color};]${str}]`
}

const highlightWithClass = (str, color, spanClass) => {
	return `[[;${color};;${spanClass};]${str}]`
}

const highlight = (str, color) => {
	return highlightWithStyle(str, '', color)
}

const highlightItalian = (str, color) => {
	return highlightWithStyle(str, 'i', color)
}

const textInFormatRegex = /(?<=\])([^\]]*)(?=\])/
const formatBeforeTextRegex = /\[\[[@!gbiuso]*(;[^;\]]*)*\]/
const colorRegex = /(?<=;)([^;]*)(?=(;[^;\]]*)*\])/
const getFormatsData = str => {
	let start = 0
	return $.terminal.format_split(str).map(format => {
		const text = format.match(textInFormatRegex)[0]
		const end = start + format.length
		const result = {
			format: format,
			text: text,
			start: start,
			end: end
		}

		start = end

		return result
	})
}

const getPositionsInFormattedString = (formatsData, positionsInText) => {
	return formatsData.reduce((input, data) => {
		const textLength = input.textLength + data.text.length

		const foundPositions = positionsInText
		.filter(posInText => posInText < textLength)
		.map(posInText => {
			const currTextStartPos = data.format.match(formatBeforeTextRegex)[0].length
			const lengthOfFormatWithoutText = input.formatLength + 
											  currTextStartPos -
											  input.textLength

			const absolute = posInText + lengthOfFormatWithoutText
			
			return {
				absolute: absolute,
				relative: absolute - input.formatLength
			}
		})

		positionsInText = positionsInText.filter(posInText => {
			return posInText >= textLength
		})

		return {
				textLength: textLength,
				formatLength: input.formatLength + data.format.length,
				positions: input.positions.concat(foundPositions)
		}
	}, { textLength: 0, formatLength: 0, positions: [] } ).positions
}

const getFormatAtPos = (formatsData, pos) => {
	return formatsData.find(data => data.start <= pos && pos < data.end).format
}

const highlightParentheses = (formatsData, openPos, closePos, isInner) => {
	const formatToPositions = getPositionsInFormattedString(
		formatsData, [openPos, closePos]
	).reduce((dict, position) => {
		const format = getFormatAtPos(formatsData, position.absolute)
		
		if (dict[format] === undefined) {
			dict[format] = []
		}

		dict[format].push(position.relative)

		return dict
	}, {})

	const spanClass = isInner ? 'parenHighlightIn' : 'parenHighlight'

	return formatsData.map(data => data.format).map(format => {
		const positions = formatToPositions[format]
		if (positions === undefined) {
			return format
		}

		const color = format.match(colorRegex)[0]
		const formatBeforeText = format.match(formatBeforeTextRegex)[0]
		
		const rawResult = positions.reduce((input, pos) => {
			const str = input.str + format.slice(input.last, pos) + ']' +
						highlightWithClass(format[pos], color, spanClass) +
						formatBeforeText
			return { str: str, last: pos + 1}
		}, { str: '', last: 0 })

		return rawResult.str + format.slice(rawResult.last)
	}).join('')
}

const getEnclosingParenthesesPositions = (text, cursorPos) => {
	const candidatePositions = [cursorPos - 1, cursorPos]

	for (const pos of candidatePositions) {
		const result = pm.match(text, pos, false)
		if (result !== undefined) {
			return result
		}
	}

	return pm.match(text, cursorPos, true)
}

const highlightParenthesesFormatter = (str, options) => {
	const formatsData = getFormatsData(str)
	const text = formatsData.map(data => data.text).join('')
	const positionsResult = getEnclosingParenthesesPositions(text, options.position)

	if (positionsResult === undefined) {
		return str
	}

	return highlightParentheses(formatsData, ...positionsResult)
}

highlightParenthesesFormatter.__meta__ = true

$.terminal.defaults.formatters = [
	str => {
		return str.replace(/;[^\n\r]*/g, highlightItalian('$&', '#296d98'))
	},

	str => {
		const highlightQuote = qStr => highlight(qStr, '#ffab42')
		const trimQuote = qStr => {
			const qStrTrimmed = qStr.trimEnd()
			return {
				trimmed: qStrTrimmed,
				removed: qStr.slice(qStrTrimmed.length)
			}
		}

		return str.replace(/'+[^']+/g, match => {
			const parseResult = pw.parse(match)
			if (parseResult.type !== ParserStateWrapper.Reject) {
				const trimResult = trimQuote(match)
				return highlightQuote(trimResult.trimmed) + trimResult.removed
			}

			const quote = match.slice(0, parseResult.offset)
			
			if (pw.parse(quote).type === ParserStateWrapper.Accept) {
				const trimResult = trimQuote(quote)
				const rest = trimResult.removed + match.slice(parseResult.offset)
				return highlightQuote(trimResult.trimmed) + rest
			}
			
			return match
		})
	},

	str => {
		return str.replace(
			/(?<=n?defun\s+)([^.'()\[\]\s]+)(\s*)((\([^.'()\[\]]*\)?)?)/gi, 
			highlight('$1', '#ff724c') + '$2' + highlight('$4', '#cf91c9')
		)
	},

	str => {
		return str.replace(
			/(?<=n?lambda\s+)(\([^.'()\[\]]*\)?)/gi, 
			highlight('$&', '#cf91c9')
		)
	},

	str => {
		return str.replace(/[^.'()\[\]\s]+/g, match => {
			return keywords.includes(match.toLowerCase())
				? highlight(match, '#39b6b5')
				: match
		})
	},

	str => {
		return str.replace(/[^.'()\[\]\s]+/g, match => {
			return ga.getGlobals().includes(match.toUpperCase())
				? highlight(match, '#ff5261')
				: match
		})
	},

	str => {
		return str.replace(/.+/g, highlight('$&', '#d7deea'))
	},

	highlightParenthesesFormatter
]

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
		prompt: '> ',
		// onPositionChange: (a, b, terminal) => {
			
		// }
	})
})
