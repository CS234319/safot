const Atom = require('./Atom')

module.exports = class Primitive {
	#name
	#expectedNumArgs
	#closure

	constructor(name, expectedNumArgs, closure) {
		this.#name = name
		this.#expectedNumArgs = expectedNumArgs
		this.#closure = closure
	}

	checkNumberOfArgs(args) {
		const s = this.#name.cons(args)
		const argsArray = args.getListAsArray()

		if (argsArray === undefined) {
			return s.error(Atom.invalid)
		}		

		if (this.#expectedNumArgs === undefined) {
			return
		}

		const recievedNumArgs = argsArray.length

		if (recievedNumArgs < this.#expectedNumArgs) {
			return s.error(Atom.missing)
		}

		if (recievedNumArgs > this.#expectedNumArgs) {
			return s.error(Atom.redundant)
		}
	}

	run(actuals) {
		try {
			this.checkNumberOfArgs(actuals)
		} catch {
			throw this.#name.cons(actuals).error(Atom.bug)
		}

		if (this.#expectedNumArgs) {
			return this.#closure(...actuals.getListAsArray())
		}

		return this.#closure(actuals)
	}

	isWithName(name) {
		return this.#name.eq(name)
	}

	isNormal() {
		return 	[
					Atom.cond, Atom.quote, Atom.lambda,
					Atom.nlambda, Atom.defun, Atom.ndefun
				].some(name => this.isWithName(name))
	}
}
