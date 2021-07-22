const S = require("./S")

module.exports = class Atom extends S {
	constructor(value) {
		super()
		this.value = value
	}

	deepCopy() {
		return new Atom(this.value)
	}

	isAtom() {
		return true
	}

	car() {
		if (this.isNil()) {
			return Atom.nil
		}
		throw `CAR: ${this.value} is not a list`
	}

	cdr() {
		if (this.isNil()) {
			return Atom.nil
		}

		throw `CDR: ${this.value} is not a list`
	}	

  // Pull up?
	eq(s) {
		return s.isAtom() && this.value === s.value; 
	}

	isList() {
		return this.isNil()
	}

	getListAsArray() {
		return this.isNil() ? [] : null
	}

	toString() {
		return this.value.toString()
	}

	static nil = new Atom("NIL")
	static t = new Atom("T")
}
