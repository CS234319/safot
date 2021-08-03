const S = require('./S')
const Atom = require('./Atom')

module.exports = class Pair extends S {
	#car
	#cdr

	constructor(l, r) {
		super() 
		this.#car = l
		this.#cdr = r
	}

	atom() {
		return false
	}

	car() {
		return this.#car
	}

	cdr() {
		return this.#cdr
	}

	eq(s) {
    	return false
	}

	equals(s) {
		return !s.atom() &&
				this.#car.equals(s.car()) && 
				this.#cdr.equals(s.cdr())
	}

	isList() {
		return this.#cdr.isList()
	}

	getListAsArray() {
		var list = this.#cdr.getListAsArray()
		list?.unshift(this.#car)
		return list
	}

	toString() {
		const list = this.getListAsArray()
		if (list) {
			return '(' + list.join(' ') + ')'
		}

		return '(' + [this.#car, this.#cdr].join(' . ') + ')'
	}
}
