module.exports = class Environment {
	constructor() {
		this.a_list = require("./Atom").nil
	}

	set(key, value) {
		if (!key.isAtom()) {
			throw `SET: ${key} is not an atom`
		}

		const pair = key.cons(value)
		this.a_list = key.cons(value).cons(this.a_list)
		return key.cons(value)
	}
}