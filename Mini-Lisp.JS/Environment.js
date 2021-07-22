// Check out and translate a-list.cc
//
module.exports = class Environment {
	constructor() {
		this.a_list = require("./Atom").nil
    // Try to initialize to the list ((t.t) (nil.nil))
    // t.cons(t).cons(nil.cons(nil).cons(nil) 
	}

	set(key, value) {
		if (!key.isAtom()) {
//Another non-compliance			throw `SET: ${key} is not an atom`
		}

		const pair = key.cons(value)
		this.a_list = key.cons(value).cons(this.a_list)
		return key.cons(value)
	}
}
