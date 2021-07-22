const S = require("./S")

module.exports = class Atom extends S {
	constructor(value) {
		super()
		this.value = value
	}

	atom() {
		return true
	}

	car() {
		throw `CAR: ${this.value} is not a list`
	}

	cdr() {
		throw `CDR: ${this.value} is not a list`
	}	

	equal(s) {
    	return this.eq(s)
  	}

	isList() {
		return this.null()
	}

	getListAsArray() {
		return this.null() ? [] : null
	}

	toString() {
		return this.value.toString()
	}

	static nil = new Atom("NIL")
	static t = new Atom("T")
}
