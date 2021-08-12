const Atom = require('./Atom')
const ListCreator = require('./ListCreator')
const EvaluationError = require('./EvaluationError')

module.exports = class Environment {
	constructor() {
		this._alist = Atom.nil
		this._backupAList = Atom.nil
		this._formalsAList = Atom.nil
	}

	getAList() {
		return this._alist
	}

	getFormalsAList() {
		return this._formalsAList
	}

	set(key, value) {
		this._alist = key.cons(value).cons(this._alist)
		return value
	}

	defun(name, formals, body) {
		return this._genericDefun(name, formals, body, Atom.lambda)
	}

	ndefun(name, formals, body) {
		return this._genericDefun(name, formals, body, Atom.nlambda)
	}

	_genericDefun(name, formals, body, tag) {
		const lc = new ListCreator()
		const lambda = lc.create(tag, formals, body)
		return this.set(name, lambda)	
	}

	lookup(s) {
		for (const list of [this._formalsAList, this._alist]) {
			const result = Environment._lookup(s, list)
			if (result !== null) {
				return result
			}
		}
	
		return s.error(Atom.undefined)
	}

	static _lookup(s, list) {
		if (list.null()) {
			return null
		}

		const currPair = list.car()
		return s.eq(currPair.car())
			? currPair.cdr()
			: Environment._lookup(s, list.cdr()) 
	}

	backup() {
		this._backupAList = this._alist
	}

	restore() {
		this._alist = this._backupAList
		this._backupAList = Atom.nil
	}

	bind(formals, actuals) {
		if (formals.null() && actuals.null()) {
			return
		}

		this._formalsAList = formals.car()
									.cons(actuals.car())
									.cons(this._formalsAList)

		this.bind(formals.cdr(), actuals.cdr())
	}

	unbind(numFormals) {
		for (var i = 0; i < numFormals; i++) {
			this._formalsAList = this._formalsAList.cdr()
		}
	}
}
