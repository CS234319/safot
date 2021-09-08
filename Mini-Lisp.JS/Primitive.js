const Atom = require('./Atom')

module.exports = class Primitive {		
	constructor(name, expectedNumArgs, closure) {
		this._name = name
		this._expectedNumArgs = expectedNumArgs
		this._closure = closure
	}

	checkNumberOfArgs(args) {
		const s = this._name.cons(args)
		const argsArray = args.getListAsArray()

		if (argsArray === undefined) {
			s.error(Atom.invalid)
		}		

		if (this._expectedNumArgs === undefined) {
			return
		}

		const recievedNumArgs = argsArray.length

		if (recievedNumArgs < this._expectedNumArgs) {
			s.error(Atom.missing)
		}

		if (recievedNumArgs > this._expectedNumArgs) {
			s.error(Atom.redundant)
		}
	}

	run(actuals) {
		try {
			this.checkNumberOfArgs(actuals)
		} catch {
			throw this._name.cons(actuals).error(Atom.bug)
		}

		if (this._expectedNumArgs) {
			return this._closure(...actuals.getListAsArray())
		}

		return this._closure(actuals)
	}

	getName() {
		return this._name
	}

	isWithName(name) {
		return this._name.eq(name)
	}

	isNormal() {
		return 	[
					Atom.cond, Atom.lambda, Atom.nlambda, Atom.defun, Atom.ndefun
				].some(name => this.isWithName(name))
	}

	isEager() {
		return !this.isNormal()
	}
}
