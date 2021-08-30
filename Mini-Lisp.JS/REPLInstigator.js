const PEGParserStateWrapper = require('./PEGParserStateWrapper')
const parser = require('./Parser')
const Engine = require('./Engine')
const config = require('./Configuration').repl

module.exports = class REPLInstigator {
	constructor(delegate) {
		this._delegate = delegate
		this._observers = Array.from(arguments).slice(1)
		this._engine = new Engine(this)
		this._parserWrapper = new PEGParserStateWrapper(parser)
		this._prepareForNewCommand()
	}

	feedLine(line) {
		this._commandString += line + '\n'
		const parseResult = this._parserWrapper.parse(this._commandString)

		switch (parseResult.type) {
			case PEGParserStateWrapper.Accepted:
				this._handleParsingResult(parseResult.output)
				break

			case PEGParserStateWrapper.ExpectedMore:
				this._commandString === ''
					? this._prepareForNewCommand() 
					: this._prompt(config.prompt.duringCommand)
				break

			case PEGParserStateWrapper.Rejected:
				this._echo(config.unknownCommand)
				this._prepareForNewCommand()
				break
		}
	}

	_prepareForNewCommand() {
		this._commandString = ''
		this._prompt(config.prompt.newCommand)	
	}

	_prompt(promptStr) {
		this._delegate.prompt(promptStr)
	}
	
	_handleParsingResult(s) {
		try {
			this._echo(this._engine.evaluate(s).toString())
		} catch (e) {
			this._echo(`Error: ${e.s.car()} - ${e.s.cdr()}`)
		}

		this._prepareForNewCommand()
	}

	_echo(str) {
		this._delegate.echo(str)
	}

	/* Engine Observer */
	globalAdded(globalAtom) {
		const value = globalAtom.getValue()
		this._observers.forEach(o => o.globalAdded(value))
	}
}
