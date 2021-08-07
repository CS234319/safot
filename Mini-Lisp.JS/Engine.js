const Environment = require('./Environment')
const Atom = require('./Atom')
const Primitive = require('./Primitive')
const ListCreator = require('./ListCreator')
const p = require('./Parser')

module.exports = class Engine {
	#env
	#primitives

	constructor() {
		this.#env = new Environment()

		this.#initPrimitives()
		this.#initPredefinedFunctions()
	}

	#initPrimitives() {
		const lc = new ListCreator()
		
		this.#primitives = [
			[Atom.car,			1, s => s.car()],
			[Atom.cdr,			1, s => s.cdr()],
			[Atom.atom,			1, s => Engine.#boolToS(s.atom())],
			[Atom.eval,			1, s => this.#_evaluate(s)],
			[Atom.cons,			2, (s, t) => s.cons(t)],
			[Atom.eq,			2, (s, t) => Engine.#boolToS(s.eq(t))],
			[Atom.set,			2, (s, t) => this.#env.set(s, t)],
			[Atom.lambda,		2, (s, t) => lc.create(Atom.lambda, s, t)],
			[Atom.nlambda,		2, (s, t) => lc.create(Atom.nlambda, s, t)],
			[Atom.defun,		3, (s, t, u) => this.#env.defun(s, t, u)],
			[Atom.ndefun,		3, (s, t, u) => this.#env.ndefun(s, t, u)],
			[Atom.cond,			undefined, s => this.#evaluateCond(s)],
		].map(tup => new Primitive(tup[0], tup[1], tup[2]))
	}

	#initPredefinedFunctions() {
		this.#env.set(Atom.nil, Atom.nil)
		this.#env.set(Atom.t, Atom.t)
		this.evaluate(p.parse("(ndefun quote (x) x)"))
		this.evaluate(p.parse("(defun null (x) (eq x nil))"))
	}

	evaluate(s) {
		this.#env.backup()

		try {
			return this.#_evaluate(s)		
		} catch (e) {
			this.#env.restore()
			throw e
		}
	}

	#_evaluate(s) {
		if (s.atom()) {
			return this.#env.lookup(s)
		}

		if (!s.isList()) {
			return s.error(Atom.invalid)
		}

		const primitive = this.#primitives.find(p => p.isWithName(s.car()))
		if (primitive) {
			return this.#applyPrimitive(primitive, s.cdr())
		}

		if (s.car().eq(Atom.error)) {
			return s.error(this.#evaluateList(s.cdr()))
		}

		return this.#apply(this.#_evaluate(s.car()), s.cdr())
	}

	#evaluateList(list) {
		if (list.null()) {
			return Atom.nil
		}

		return this.#_evaluate(list.car()).cons(this.#evaluateList(list.cdr()))
	}

	#evaluateCond(testForms) {
		if (testForms.null()) {
			return Atom.nil
		}

		const currPair = testForms.car()
			
		if (currPair.atom()) {
			return currPair.error(Atom.cond)
		}

		if (this.#_evaluate(currPair.car()).t()) {
			return this.#_evaluate(currPair.cdr().car())
		}

		return this.#evaluateCond(testForms.cdr())
	}

	#applyPrimitive(primitive, args) {
		primitive.checkNumberOfArgs(args)
		const actuals = primitive.isNormal() ? args : this.#evaluateList(args)	
		return primitive.run(actuals)
	}

	#apply(lambda, args) {
		if (lambda.getListLength() !== 3) {
			return this.#throwInvalidLambdaError(lambda)
		}

		const tag = lambda.car()
		const formals = lambda.cdr().car()

		if ((!tag.eq(Atom.lambda) && !tag.eq(Atom.nlambda)) ||
			(!formals.isList())) {
			return this.#throwInvalidLambdaError(lambda)
		}

		this.#checkArgsInLambdaCall(lambda, args)

		const actuals = tag.eq(Atom.lambda) ? this.#evaluateList(args) : args
		const body = lambda.cdr().cdr().car()
		
		this.#env.bind(formals, actuals)

		try {
			return this.#_evaluate(body)
		} finally {
			this.#env.unbind(formals.getListLength())	
		}
	}

	#checkArgsInLambdaCall(lambda, args) {
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

	#throwInvalidLambdaError(lambda) {
		return lambda.error(Atom.invalid)
	}

	static #boolToS(bool) {
		return bool ? Atom.t : Atom.nil
	}
}
