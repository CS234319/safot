module.exports = class S {
	atom() {
		return this.#errorNotImplemented()
	}

	car() {
		return this.#errorNotImplemented()
	}

	cdr() {
		return this.#errorNotImplemented()
	}

	cons(s) {
		const Pair = require('./Pair')
		return new Pair(this, s)
	}

	eq(s) {
		return this.#errorNotImplemented()
	}

	null() {
		const Atom = require('./Atom')
		return this.eq(Atom.nil)
	}

	t() {
		return !this.null()	
	}

	error(kind) {
		const EvaluationError = require('./EvaluationError')
		throw new EvaluationError(kind ? this.cons(kind) : this)
	}

	isList() {
		return this.#errorNotImplemented()
	}

	getListAsArray() {
		return this.#errorNotImplemented()
	}

	getListLength() {
		return this.getListAsArray()?.length
	}

	toString() {
		return this.#errorNotImplemented()
	}

	#errorNotImplemented() {
		return this.error(Atom.bug)		
	}
}
