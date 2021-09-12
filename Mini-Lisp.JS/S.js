require('./ArrayExtension')

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

	reversedList() {
		const ListCreator = require('./ListCreator')
		const lc = new ListCreator()
		const array = this.getListAsArray()
		return array === undefined
			? undefined
			: lc.create(...array.reversed())
	}

	prepend(s) {
		return s.cons(this)
	}

	prependPair(car, cdr) {
		return this.prepend(car.cons(cdr))
	}
}
