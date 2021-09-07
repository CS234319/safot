const S = require('./S')
const Atom = require('./Atom')
require('./ArrayExtension')

module.exports = class Pair extends S {
	constructor(car, cdr) {
		super() 
		this._car = car
		this._cdr = cdr
	}

	atom() {
		return false
	}

	car() {
		return this._car
	}

	cdr() {
		return this._cdr
	}

	eq(s) {
    	return false
	}

	equals(s) {
		return !s.atom() &&
				this._car.equals(s._car) && 
				this._cdr.equals(s._cdr)
	}

	isList() {
		return this._cdr.isList()
	}

	getListAsArray() {
		return this._cdr.getListAsArray()?.prepend(this._car)
	}

	toString() {
		const list = this.getListAsArray()
		if (list) {
			return '(' + list.join(' ') + ')'
		}

		return '[' + [this._car, this._cdr].join(' . ') + ']'
	}

	/* Exclusive Pair Methods */
	insert(s) {
		this._cdr = s.cons(this._cdr)
	}
}
