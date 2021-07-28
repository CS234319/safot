const Atom = require('./Atom')
const ListCreator = require('./ListCreator')

module.exports = class Environment {
	constructor() {
		this.alist = Atom.nil
	}

	set(key, value) {
		this.alist = key.cons(value).cons(this.alist)
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
		return Environment.#lookup(s, this.alist)
	}

	static #lookup(s, list) {
		if (list.null()) {
			return undefined
		}

		const currPair = list.car()
		return s.eq(currPair.car())
			? currPair.cdr()
			: Environment.#lookup(s, list.cdr()) 
	}

	bind(names, values) {
		if (names.null() && values.null()) {
			return
		}

		if (names.null() || values.null()) {
			throw 'BIND: Names and values lengths does not match'
		}

		if (names.atom() || values.atom()) {
			throw 'BIND: arguments should be lists'
		}

		this.set(names.car(), values.car())
		this.bind(names.cdr(), values.cdr())
	}

	unbind(numPairs) {
		for (let i = 0; i < numPairs; i++) {
			this.alist = this.alist.cdr()	
		}
	}
}
