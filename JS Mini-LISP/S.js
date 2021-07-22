module.exports = class S {
	deepCopy() {
		throw "Not implemented"
	}

	isAtom() {
		throw "Not implemented"
	}

	car() {
		throw "Not implemented"		
	}

	cdr() {
		throw "Not implemented"
	}

	isNil() {
		const Atom = require("./Atom")
		return this.eq(Atom.nil)
	}

	cons(s) {
		const Pair = require("./Pair")
		return new Pair(this, s)
	}

	eq(s) {
		throw "Not implemented"
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
