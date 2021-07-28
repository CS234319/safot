const S = require('./S')

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

	isList() {
		return this.null()
	}

	getListAsArray() {
		return this.null() ? [] : undefined
	}

	toString() {
		return this.value.toString()
	}

	static nil = new Atom('NIL')
	static t = new Atom('T')
	static quote = new Atom('QUOTE')
	static lambda = new Atom('LAMBDA')
	static nlambda = new Atom('NLAMBDA')
}
