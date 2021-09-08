const config = require('./Configuration').evaluationError

module.exports = class EvaluationError extends Error {
	constructor(s) {
		super(s.toString())
		this.name = this.constructor.name
		this._s = s
		this._dump = ''
	}

	prependDump(str) {
		this._dump = str + this._dump
	}

	getStack() {
		const errorMessage = config.pattern
				.replace('{car}', this._s.car())
				.replace('{cdr}', this._s.cdr())

		return [
			config.opening, '\n', this._dump, '\t', errorMessage
		].join('')
	}
}