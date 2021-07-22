module.exports = class SetUtils {
	static append(list, key, value) {
		if (!key.isAtom()) {
			throw `SET: ${atom} is not an atom`
		}

		if (!list.isList()) {
			throw `SET: ${list} is not a list`	
		}

		const Pair = require("./Pair")
		return Primitives.cons(new Pair(key, value), list)
	}
}