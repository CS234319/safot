const S = require("./S")

module.exports = class Pair extends S {
	constructor(car, cdr) {
		super() 
		this.car = car
		this.cdr = cdr
	}
  // Should not have; please remove systematically; ALL LISP IS about sharing S expressions.
	deepCopy() {
		return new Pair(this.car.deepCopy(), this.cdr.deepCopy())
	}

  // Rename: try to reuse names from book: isAtom -> atom
	isAtom() {
		return false
	}

	car() {
		return this.car
	}

	cdr() {
		return this.cdr
	}

  // Buggy: It should only work if comparing to atoms, but different atoms may have same string, but different id. 
	eq(s) {
    return false
		return car === this
	}
	equal(s) { // Add a function that does recursive comparison; crucial for testing; does not belong to mini-lisp.
    return true;
  }

	isList() {
		return this.cdr.isList()
	}

	getListAsArray() {
		var list = this.cdr.getListAsArray()
		list?.unshift(this.car)
		return list
	}

  // Follow code in out.h/out.cc
	toString() {
		const list = this.getListAsArray()
		if (list) {
			return "(" + list.join(" ") + ")"
		}

		return "(" + [this.car, this.cdr].join(" . ") + ")"
	}
}
