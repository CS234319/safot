module.exports = {
	format: {
		color: {
			comment: 		'#296d98',
			symbol: {
				global: 	'#ff5261',
				primitive: 	'#39b6b5',
			},
			quote: 			'#ffab42',
			formals: 		'#cf91c9',
			defunName:      '#ff724c',
		},

		style: {
			comment: 'i',
		},
	},

	evaluationError: {
		pattern: 'Traceback (most recent call last):\n{dump}\t** Error {cdr} in {car}',
	},

	dump: {
		args: {
			failedPrefix: 	'^',
			delim: 			', ',
		},

		pattern: `\t{name}[{args}]\n`,
	},

	repl: {
		prompt: {
			newCommand: 	'> ',
			duringCommand: 	'- ',
		},

		unknownCommand: '?',
	},

	browserTerminal: {
		greetings: 'Mini-LISP REPL',
		name: 'Mini-LISP',
		height: 750,
		width: 600,
		prompt: '> ',
		caseSensitiveAutocomplete: false,
	},

	highlightingBrackets: {
		left: 	'\x01',
		right: 	'\x02',
	},
}