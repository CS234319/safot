const S = require("./S")

module.exports = class Pair extends S {
	constructor(s, t) {
		super()
		this.s = s
		this.t = t
	}

	deepCopy() {
		return new Pair(this.s.deepCopy(), this.t.deepCopy())
	}

	isAtom() {
		return false
	}

	car() {
		return this.s
	}

	cdr() {
		return this.t
	}

	eq(s) {
		return s === this
	}

	isList() {
		return this.t.isList()
	}

	getListAsArray() {
		var list = this.t.getListAsArray()
		list?.unshift(this.s)
		return list
	}

	toString() {
		const list = this.getListAsArray()
		if (list) {
			return "(" + list.join(" ") + ")"
		}

		return "(" + [this.s, this.t].join(" . ") + ")"
	}
}
