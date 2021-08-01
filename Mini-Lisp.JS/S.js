module.exports = class S {
	atom() {
		throw 'Not implemented'
	}

	car() {
		throw 'Not implemented'		
	}

	cdr() {
		throw 'Not implemented'
	}

	cons(s) {
		const Pair = require('./Pair')
		return new Pair(this, s)
	}

	eq(s) {
		throw 'Not implemented'
	}

	null() {
		const Atom = require('./Atom')
		return this.eq(Atom.nil)
	}

	isList() {
		throw 'Not implemented'
	}

	getListAsArray() {
		throw 'Not implemented'
	}

	getListLength() {
		return this.getListAsArray()?.length
	}

	toString() {
		throw 'Not implemented'	
	}
}
