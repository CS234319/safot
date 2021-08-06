const Atom = require('./Atom')
const ListCreator = require('./ListCreator')
const EvaluationError = require('./EvaluationError')

module.exports = class Environment {
	#alist
	#backupAList
	#formalsAList

	constructor() {
		this.#alist = Atom.nil
		this.#backupAList = Atom.nil
		this.#formalsAList = Atom.nil
	}

	getAList() {
		return this.#alist
	}

	getFormalsAList() {
		return this.#formalsAList
	}

	set(key, value) {
		this.#alist = key.cons(value).cons(this.#alist)
		return value
	}

	defun(name, formals, body) {
		return this.#genericDefun(name, formals, body, Atom.lambda)
	}

	ndefun(name, formals, body) {
		return this.#genericDefun(name, formals, body, Atom.nlambda)
	}

	#genericDefun(name, formals, body, tag) {
		const lc = new ListCreator()
		const lambda = lc.create(tag, formals, body)
		return this.set(name, lambda)	
	}

	lookup(s) {
		for (const list of [this.#formalsAList, this.#alist]) {
			const result = Environment.#lookup(s, list)	
			if (result !== null) {
				return result
			}
		}
	
		return s.error(Atom.undefined)
	}

	static #lookup(s, list) {
		if (list.null()) {
			return null
		}

		const currPair = list.car()
		return s.eq(currPair.car())
			? currPair.cdr()
			: Environment.#lookup(s, list.cdr()) 
	}

	backup() {
		this.#backupAList = this.#alist
	}

	restore() {
		this.#alist = this.#backupAList
		this.#backupAList = Atom.nil
	}

	bind(formals, actuals) {
		if (formals.null() && actuals.null()) {
			return
		}

		this.#formalsAList = formals.car()
									.cons(actuals.car())
									.cons(this.#formalsAList)

		this.bind(formals.cdr(), actuals.cdr())
	}

	unbind(numFormals) {
		for (var i = 0; i < numFormals; i++) {
			this.#formalsAList = this.#formalsAList.cdr()
		}
	}
}
