const List = require("./List")

module.exports = class Environment {
	constructor() {
		const Atom = require("./Atom")
		const nil = Atom.nil
		const t = Atom.t

		this.a_list = List.create(t.cons(t), nil.cons(nil))
	}

	set(key, value) {
		const pair = key.cons(value)
		this.a_list = pair.cons(this.a_list)
		return pair
	}
}
