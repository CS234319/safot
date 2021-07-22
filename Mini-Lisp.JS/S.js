module.exports = class S {
	atom() {
		throw "Not implemented"
	}

	car() {
		throw "Not implemented"		
	}

	cdr() {
		throw "Not implemented"
	}

	cons(s) {
		const Pair = require("./Pair")
		return new Pair(this, s)
	}

	eq(s) {
		return s.atom() && this.value === s.value
	}

	equal(s) {
    	throw "Not implemented"
  	}

	null() {
		const Atom = require("./Atom")
		return this.eq(Atom.nil)
	}

	isList() {
		throw "Not implemented"
	}

	getListAsArray() {
		throw "Not implemented"
	}

	toString() {
		throw "Not implemented"	
	}
}
