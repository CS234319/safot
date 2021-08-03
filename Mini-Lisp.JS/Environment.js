const Atom = require('./Atom')
const ListCreator = require('./ListCreator')
const EvaluationError = require('./EvaluationError')

module.exports = class Environment {
	#alist
	#alistBackup

	constructor() {
		this.#alist = Atom.nil
		this.#alistBackup = Atom.nil
	}

	getAList() {
		return this.#alist
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
		return Environment.#lookup(s, this.#alist)
	}

	static #lookup(s, list) {
		if (list.null()) {
			return s.error(Atom.undefined)
		}

		const currPair = list.car()
		return s.eq(currPair.car())
			? currPair.cdr()
			: Environment.#lookup(s, list.cdr()) 
	}

	bind(keys, values) {
		for (const s of [keys, values]) {
			if (!s.isList()) {
				return s.error(Atom.invalid)
			}
		}

		this.#_bind(keys, values)
	}

	#_bind(keys, values) {
		if (keys.null() && values.null()) {
			return
		}

		if (keys.t() && values.null()) {
			return keys.error(Atom.missing)
		}

		if (keys.null() && values.t()) {
			return values.error(Atom.redundant)
		}

		this.set(keys.car(), values.car())
		this.bind(keys.cdr(), values.cdr())
	}

	unbind(numPairs) {
		if (this.#alist.getListLength() < numPairs) {
			return this.#alist.error(Atom.invalid)
		}

		this.#_unbind(numPairs)
	}

	#_unbind(numPairs) {
		for (let i = 0; i < numPairs; i++) {
			this.#alist = this.#alist.cdr()	
		}
	}

	backup() {
		this.#alistBackup = this.#alist
	}

	restore() {
		this.#alist = this.#alistBackup
		this.#alistBackup = Atom.nil
	}
}
