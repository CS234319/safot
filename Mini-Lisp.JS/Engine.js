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
		].map(tup => new Primitive(tup[0], tup[1], tup[2]))
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
		if (lambda.getListLength() !== 3) {
			return this._throwInvalidLambdaError(lambda)
		}

		const tag = lambda.car()
		const formals = lambda.cdr().car()

		if ((!tag.eq(Atom.lambda) && !tag.eq(Atom.nlambda)) ||
			(!formals.isList())) {
			return this._throwInvalidLambdaError(lambda)
		}

		this._checkArgsInLambdaCall(lambda, args)

		const actuals = tag.eq(Atom.lambda) ? this._evaluateList(args) : args
		const body = lambda.cdr().cdr().car()
		
		const alist = this._env.getAList()
		this._env.bind(formals, actuals)

		try {
			const result = this._evaluate(body)
			return result
		} finally {
			this._env.setAList(alist)
		}
	}

	_checkArgsInLambdaCall(lambda, args) {
		const argsLength = args.getListLength()
		
		if (argsLength === undefined) {
			return lambda.cons(args).error(Atom.invalid)
		}

		const formalsLength = lambda.cdr().car().getListLength()

		if (argsLength < formalsLength) {
			return lambda.cons(args).error(Atom.missing)
		}

		if (argsLength > formalsLength) {
			return lambda.cons(args).error(Atom.redundant)
		}
	}

	_throwInvalidLambdaError(lambda) {
		return lambda.error(Atom.invalid)
	}

	static _boolToS(bool) {
		return bool ? Atom.t : Atom.nil
	}

	/* EnvironmentObserver */
	globalAdded(globalAtom) {
		this._observers.forEach(o => o.globalAdded(globalAtom))
	}
}
