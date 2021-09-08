const Atom = require('./Atom')

module.exports = class Lambda {
	constructor(s, args) {
		this.s = s
		this._checkLength(args)
		this.tag = s.car()
		this._checkTag(args)
		this.formals = s.cdr().car()
		this._compareArgsAndFormalsLength(args)
		this.body = s.cdr().cdr().car()
	}

	_checkLength(args) {
		const lambdaLength = this.s.getListLength()
		if (!lambdaLength || lambdaLength !== 3) {
			this._throwInvalid(args)
		}
	}

	_checkTag(args) {
		if (![Atom.lambda, Atom.nlambda].some(t => this.tag.eq(t))) {
			this._throwInvalid(args)
		}
	}

	_compareArgsAndFormalsLength(args) {
		const argsLength = args.getListLength()
		const formalsLength = this.formals.getListLength()

		if (argsLength === undefined || formalsLength === undefined) {
			this._throwInvalid(args)
		}

		if (argsLength < formalsLength) {
			this.s.cons(args).error(Atom.missing)
		}

		if (argsLength > formalsLength) {
			this.s.cons(args).error(Atom.redundant)
		}		
	}

	_throwInvalid(args) {
		return this.s.cons(args).error(Atom.invalid)
	}
}
