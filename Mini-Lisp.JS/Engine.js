const Environment = require('./Environment')
const Atom = require('./Atom')
const Primitive = require('./Primitive')
const ListCreator = require('./ListCreator')
const parse = require('./Parser').parse

module.exports = class Engine {		
	constructor() {
		this._observers = Array.from(arguments)
		this._env = new Environment(this)
		
		this._initPrimitives()
		this._initPredefinedFunctions()
	}

	_initPrimitives() {
		const lc = new ListCreator()
		
		this._primitives = [
			[Atom.car,			1, s => s.car()],
			[Atom.cdr,			1, s => s.cdr()],
			[Atom.atom,			1, s => Engine._boolToS(s.atom())],
			[Atom.eval,			1, s => this._evaluate(s)],
			[Atom.cons,			2, (s, t) => s.cons(t)],
			[Atom.eq,			2, (s, t) => Engine._boolToS(s.eq(t))],
			[Atom.SET,			2, (s, t) => this._env.set(s, t)],
			[Atom.lambda,		2, (s, t) => lc.create(Atom.lambda, s, t)],
			[Atom.nlambda,		2, (s, t) => lc.create(Atom.nlambda, s, t)],
			[Atom.defun,		3, (s, t, u) => this._env.defun(s, t, u)],
			[Atom.ndefun,		3, (s, t, u) => this._env.ndefun(s, t, u)],
			[Atom.cond,			undefined, s => this._evaluateCond(s)],
		].map(params => new Primitive(...params))
	}

	_initPredefinedFunctions() {
		this._env.set(Atom.nil, Atom.nil)
		this._env.set(Atom.t, Atom.t)
		this._evaluate(parse("(ndefun quote (x) x)"))
		this._evaluate(parse("(defun null (x) (eq x nil))"))
	}

	evaluate(s) {
		return this._evaluate(s)
	}

	_evaluate(s) {
		if (s.atom()) {
			return this._env.lookup(s)
		}

		if (!s.isList()) {
			return s.error(Atom.invalid)
		}

		const primitive = this._primitives.find(p => p.isWithName(s.car()))
		if (primitive) {
			return this._applyPrimitive(primitive, s.cdr())
		}

		if (s.car().eq(Atom.error)) {
			return s.error(this._evaluateList(s.cdr()))
		}

		return this._apply(s.car(), this._evaluate(s.car()), s.cdr())
	}

	_evaluateList(list) {
		if (list.null()) {
			return Atom.nil
		}

		return this._evaluate(list.car()).cons(this._evaluateList(list.cdr()))
	}

	_evaluateCond(testForms) {
		if (testForms.null()) {
			return Atom.nil
		}

		const currPair = testForms.car()
			
		if (currPair.atom()) {
			return currPair.error(Atom.cond)
		}

		if (this._evaluate(currPair.car()).t()) {
			return this._evaluate(currPair.cdr().car())
		}

		return this._evaluateCond(testForms.cdr())
	}

	_applyPrimitive(primitive, args) {
		primitive.checkNumberOfArgs(args)
		const actuals = primitive.isNormal() ? args : this._evaluateList(args)
		return primitive.run(actuals)
	}

	_apply(lambdaName, lambda, args) {
		Engine._checkLambda(lambda, args)

		try {
			this._env.bindLambdaRecords(lambdaName, lambda, args, this)
			const body = lambda.cdr().cdr().car()
			return this._evaluate(body)
		} catch(e) {
			throw e
		} finally {
			this._env.popLambdaRecords()	
		}
	}

	static _checkLambda(lambda, args) {
		const lambdaLength = lambda.getListLength()
		if (!lambdaLength || lambdaLength < 3) {
			return lambda.cons(args).error(Atom.invalid)
		}
		
		const tag = lambda.car()
		if (!tag.eq(Atom.lambda) && !tag.eq(Atom.nlambda)) {
			return Engine._throwInvalidLambdaError(lambda, args)
		}

		const argsLength = args.getListLength()
		if (argsLength === undefined) {
			return Engine._throwInvalidLambdaError(lambda, args)
		}

		const formalsLength = lambda.cdr().car().getListLength()

		if (argsLength < formalsLength) {
			return lambda.cons(args).error(Atom.missing)
		}

		if (argsLength > formalsLength) {
			return lambda.cons(args).error(Atom.redundant)
		}
	}

	static _throwInvalidLambdaError(lambda, args) {
		return lambda.cons(args).error(Atom.invalid)
	}

	static _boolToS(bool) {
		return bool ? Atom.t : Atom.nil
	}

	/* EnvironmentObserver */
	globalAdded(globalAtom) {
		this._observers.forEach(o => o.globalAdded(globalAtom))
	}
}
