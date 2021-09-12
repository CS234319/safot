const REPLInstigator = require('./REPLInstigator')
const readline = require('readline')

module.exports = class StreamREPL {
	constructor(inputStream, outputStream, promptStream) {
		this._outputStream = outputStream
		this._lineReader = readline.createInterface({
	  		input: inputStream,
	  		output: promptStream,
	  		crlfDelay: Infinity
		})	

		this._lineReader.on('line', (line) => {
	  		this._replInstigator.feedLine(line)
		})

		this._replInstigator = new REPLInstigator(this)
	}

	/*  REPLInstigatorDelegate */
	prompt(promptStr) {
		this._lineReader.setPrompt(promptStr)
		this._lineReader.prompt()
	}

	echo(str) {
		this._outputStream.write(str + '\n')
	}
}
