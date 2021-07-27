const Atom = require('./Atom')
const ListCreator = require('./ListCreator')

module.exports = class Environment {
	constructor() {
		const nil = Atom.nil
		const t = Atom.t

		const lc = new ListCreator()

		this.alist = lc.create(t.cons(t), nil.cons(nil))
	}

	set(key, value) {
		this.alist = key.cons(value).cons(this.alist)
		return value
	}

	lookup(s) {
		return Environment.#lookup(s, this.alist)
	}

	static #lookup(s, list) {
		if (list.null()) {
			return undefined
		}

		const curr_pair = list.car()
		return s.eq(curr_pair.car())
			? curr_pair.cdr()
			: Environment.#lookup(s, list.cdr()) 
	}

	bind(names, values) {
		if (names.null() && values.null()) {
			return
		}

		if (names.null() || values.null()) {
			throw 'BIND: Names and values lengths does not match'
		}

		if (names.atom() || values.atom()) {
			throw 'BIND: arguments should be lists'
		}

		this.set(names.car(), values.car())
		this.bind(names.cdr(), values.cdr())
	}
}
