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
		return config.pattern
			.replace('{dump}', this._dump)
			.replace('{car}', this._s.car())
			.replace('{cdr}', this._s.cdr())
	}
}