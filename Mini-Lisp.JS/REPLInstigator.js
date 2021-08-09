const ParserStateWrapper = require('./ParserStateWrapper')
const Engine = require('./Engine')
const readline = require('readline')

module.exports = class REPLInstigator {
	#engine
	#buffer
	#lineReader
	#outputStream

	constructor(inputStream, outputStream, promptStream) {
		this.#engine = new Engine()
		this.#outputStream = outputStream
		this.#lineReader = readline.createInterface({
	  		input: inputStream,
	  		output: promptStream,
	  		crlfDelay: Infinity
		})	

		this.#lineReader.on('line', (line) => {
	  		this.#feedLine(line)
		})

		this.#promptNew()
	}

	#prompt(promptStr) {
		this.#lineReader.setPrompt(promptStr)
		this.#lineReader.prompt()
	}

	#promptNew() {
		this.#buffer = ''
		this.#prompt('> ')
	}

	#feedLine(lineStr) {
		this.#buffer += lineStr
		const pw = new ParserStateWrapper()
		const parseResult = pw.parse(this.#buffer)

		switch (parseResult.type) {
			case ParserStateWrapper.Accept:
				this.#handleParsingResult(parseResult.output)
				break

			case ParserStateWrapper.ExpectMore:
				this.#buffer.length === 0 ? this.#promptNew() : this.#prompt('- ')
				break

			case ParserStateWrapper.Reject:
				this.#println('?')
				this.#promptNew()
				break
		}
	}
	
	#handleParsingResult(s) {
		try {
			this.#println(`${this.#engine.evaluate(s)}`)
		} catch (e) {
			this.#println(`Error: ${e.s.car()} - ${e.s.cdr()}`)
		}

		this.#promptNew()
	}

	#println(str) {
		this.#outputStream.write(str + '\n')
	}
}
