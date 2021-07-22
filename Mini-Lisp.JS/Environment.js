const ListCreator = require("./ListCreator")

module.exports = class Environment {
	constructor() {
		const Atom = require("./Atom")
		const nil = Atom.nil
		const t = Atom.t

		const lc = new ListCreator()

		this.a_list = lc.create(t.cons(t), nil.cons(nil))
	}

	set(key, value) {
		this.a_list = key.cons(value).cons(this.a_list)
		return value
	}

	aList() {
		return this.a_list
	}
}
