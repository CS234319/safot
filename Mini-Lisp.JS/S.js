module.exports = class S {
	cons(s) {
		const Pair = require('./Pair')
		return new Pair(this, s)
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

	getListLength() {
		return this.getListAsArray()?.length
	}

	prepend(s) {
		return s.cons(this)
	}

	prependPair(car, cdr) {
		return this.prepend(car.cons(cdr))
	}

	prependList(list) {
		if (list.null()) {
			return this
		}

		const cdr = list.cdr().null()
			? this
			: this.prependList(list.cdr())

		return list.car().cons(cdr)
	}
}
