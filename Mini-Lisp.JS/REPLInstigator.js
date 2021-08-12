const ParserStateWrapper = require('./ParserStateWrapper')
const Engine = require('./Engine')
const readline = require('readline')

module.exports = class REPLInstigator {
	constructor(inputStream, outputStream, promptStream) {
		this._engine = new Engine()
		this._outputStream = outputStream
		this._lineReader = readline.createInterface({
	  		input: inputStream,
	  		output: promptStream,
	  		crlfDelay: Infinity
		})	

		this._lineReader.on('line', (line) => {
	  		this._feedLine(line)
		})

		this._promptNew()
	}

	_prompt(promptStr) {
		this._lineReader.setPrompt(promptStr)
		this._lineReader.prompt()
	}

	_promptNew() {
		this._buffer = ''
		this._prompt('> ')
	}

	_feedLine(lineStr) {
		this._buffer += lineStr
		const pw = new ParserStateWrapper()
		const parseResult = pw.parse(this._buffer)

		switch (parseResult.type) {
			case ParserStateWrapper.Accept:
				this._handleParsingResult(parseResult.output)
				break

			case ParserStateWrapper.ExpectMore:
				this._buffer.length === 0 ? this._promptNew() : this._prompt('- ')
				break

			case ParserStateWrapper.Reject:
				this._println('?')
				this._promptNew()
				break
		}
	}
	
	_handleParsingResult(s) {
		try {
			this._println(this._engine.evaluate(s).toString())
		} catch (e) {
			this._println(`Error: ${e.s.car()} - ${e.s.cdr()}`)
		}

		this._promptNew()
	}

	_println(str) {
		this._outputStream.write(str + '\n')
	}
}
