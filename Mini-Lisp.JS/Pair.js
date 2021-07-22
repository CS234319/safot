const S = require("./S")

module.exports = class Pair extends S {
	constructor(l, r) {
		super() 
		this.l = l
		this.r = r
	}

	atom() {
		return false
	}

	car() {
		return this.l
	}

	cdr() {
		return this.r
	}

	eq(s) {
    	return false
	}

	equal(s) {
		return (!s.atom() && 
				this.l.equal(s.l) &&
				this.r.equal(s.r))
  	}

	isList() {
		return this.r.isList()
	}

	getListAsArray() {
		var list = this.r.getListAsArray()
		list?.unshift(this.l)
		return list
	}

	toString() {
		const list = this.getListAsArray()
		if (list) {
			return "(" + list.join(" ") + ")"
		}

		return "(" + [this.l, this.r].join(" . ") + ")"
	}
}
