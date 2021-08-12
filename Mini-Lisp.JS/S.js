module.exports = class S {
	atom() {
		return this._errorNotImplemented()
	}

	car() {
		return this._errorNotImplemented()
	}

	cdr() {
		return this._errorNotImplemented()
	}

	cons(s) {
		const Pair = require('./Pair')
		return new Pair(this, s)
	}

	eq(s) {
		return this._errorNotImplemented()
	}

	equals(s) {
		return this._errorNotImplemented()
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
		return this._errorNotImplemented()
	}

	getListAsArray() {
		return this._errorNotImplemented()
	}

	getListLength() {
		return this.getListAsArray()?.length
	}

	toString() {
		return this._errorNotImplemented()
	}

	_errorNotImplemented() {
		return this.error(Atom.bug)		
	}
}
