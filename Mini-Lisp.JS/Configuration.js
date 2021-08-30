module.exports = {
	format: {
		color: {
			default: 		'#d7deea',
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
		height: 500,
		width: 400,
		prompt: '> ',
		caseSensitiveAutocomplete : false,
	},
}