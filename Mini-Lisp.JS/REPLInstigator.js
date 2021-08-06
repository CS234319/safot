const p = require('./Parser')
const Engine = require('./Engine')
const readline = require('readline')

module.exports = class REPLInstigator {
	#engine
	#buffer
	#rl

	constructor() {
		this.#engine = new Engine()
		this.#rl = readline.createInterface({
		 	input: process.stdin,
		 	output: process.stdout
		})

		this.#readNew()
	}

	#read(cursorStr) {
		this.#rl.question(cursorStr, (lineStr) => {
			this.#feedLine(lineStr)
		})
	}

	#readNew() {
		this.#buffer = ''
		this.#read('> ')
	}

	#feedLine(lineStr) {
		try {
			this.#buffer += lineStr
			this.#handleParsingResult(p.parse(this.#buffer))
		} catch (e) {
			if (e.found === null) {
				this.#read((this.#buffer.length === 0) ? '> ' : '- ')
				return
			}

			console.log('?')
			this.#readNew()
		}
	}

	#handleParsingResult(parsingResult) {
		try {
			console.log(`${this.#engine.evaluate(parsingResult)}`)
		} catch (e) {
			console.log(`Error: ${e.s.car()} - ${e.s.cdr()}`)
		}

		this.#readNew()
	}
}
