const Atom = require('./Atom')
const ListCreator = require('./ListCreator')
const EvaluationError = require('./EvaluationError')

module.exports = class Environment {
	#alist
	#alistStack

	constructor() {
		this.#alist = Atom.nil
		this.#alistStack = Atom.nil
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
		const keysLength = keys.getListLength()
		if (keysLength === undefined) {
			return keys.error(Atom.invalid)
		}
		
		const valuesLength = values.getListLength()
		if (valuesLength === undefined) {
			return values.error(Atom.invalid)
		}

		if (keysLength < valuesLength) {
			return values.error(Atom.redundant)
		}

		if (keysLength > valuesLength) {
			return values.error(Atom.missing)
		}

		this.#_bind(keys, values)
	}

	#_bind(keys, values) {
		if (keys.null() && values.null()) {
			return
		}

		this.set(keys.car(), values.car())
		this.#_bind(keys.cdr(), values.cdr())
	}

	push() {
		this.#alistStack = this.#alist.cons(this.#alistStack)
	}

	pop() {
		this.#alist = this.#alistStack.car()
		this.#alistStack = this.#alistStack.cdr()
	}

	clearStack() {
		this.#alistStack = Atom.nil
	}
}
