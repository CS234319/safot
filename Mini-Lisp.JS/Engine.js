const Environment = require('./Environment')
const Atom = require('./Atom')
const Primitive = require('./Primitive')
const ListCreator = require('./ListCreator')
const p = require('./Parser')

module.exports = class Engine {
	constructor() {
		this.env = new Environment()
		this.env.set(Atom.nil, Atom.nil)
		this.env.set(Atom.t, Atom.t)

		this.#initPrimitives()
		this.#initLibraryFunctions()
	}

	#initPrimitives() {
		const lc = new ListCreator()
		
		this.primitives = [
			['CAR',			1, s => s.car()],
			['CDR',			1, s => s.cdr()],
			['QUOTE',		1, s => s],
			['ATOM',		1, s => Engine.#boolToS(s.atom())],
			['ERROR',		1, s => this.#evaluateError(s)],
			['EVAL',		1, s => s],
			['CONS',		2, (s, t) => s.cons(t)],
			['EQ',			2, (s, t) => Engine.#boolToS(s.eq(t))],
			['SET',			2, (s, t) => this.env.set(s, t)],
			['LAMBDA',		2, (s, t) => lc.create(Atom.lambda, s, t)],
			['NLAMBDA',		2, (s, t) => lc.create(Atom.nlambda, s, t)],
			['DEFUN',		3, (s, t, u) => this.env.defun(s, t, u)],
			['NDEFUN',		3, (s, t, u) => this.env.ndefun(s, t, u)],
			['COND',		undefined, s => this.#evaluateCond(s)],
		].map(tup => new Primitive(new Atom(tup[0]), tup[1], tup[2]))
	}

	#initLibraryFunctions() {
		this.evaluate(p.parse("(defun null (x) (eq x nil))"))
	}

	evaluate(s) {
		if (s.atom()) {
			const binded = this.env.lookup(s)
			if (binded === undefined) {
				throw `EVAL: variable ${s} has no value`
			}

			return binded
		}

		const primitive = this.primitives.find(p => p.isWithName(s.car()))
		if (primitive) {
			return this.#applyPrimitive(primitive, s.cdr())
		}

		return this.#apply(s.car(), s.cdr())
	}

	#evaluateError(s) {
		//TODO: handle error correctly
		throw `ERROR: ${s}`
	}

	#evaluateList(list) {
		if (list.null()) {
			return Atom.nil
		}

		if (list.atom()) {
			throw 'evaluateList: argument must be a list'
		}

		return this.evaluate(list.car()).cons(this.#evaluateList(list.cdr()))
	}

	#evaluateCond(testForms) {
		if (testForms.null()) {
			return Atom.nil
		}

		if (testForms.atom()) {
			throw 'COND: test forms must be a list'
		}

		const currPair = testForms.car()
			
		if (currPair.atom()) {
			throw 'COND: all expressions in test forms must be pairs'
		}

		if (this.#evaluateToBool(currPair.car())) {
			return this.evaluate(currPair.cdr().car())
		}

		return this.#evaluateCond(testForms.cdr())
	}

	#evaluateToBool(s) {
		return !this.evaluate(s).null()
	}

	#apply(lambdaName, actuals) {
		const lambda = this.evaluate(lambdaName)
		if (lambda === undefined || lambda.atom()) {
			throw `EVAL: undefined function ${lambdaName}`
		}

		const tag = lambda.car()
		if (!tag.eq(Atom.lambda) && !tag.eq(Atom.nlambda)) {
			throw `EVAL: lambda-expression tag is expected`
		}

		const lambdaExpActuals = lambda.cdr()
		if (lambdaExpActuals.atom() || lambdaExpActuals.cdr().atom()) {
			throw `EVAL: incorrect actuals for lambda-expression`	
		}

		return this.#applyDecomposedLambda(tag, lambdaExpActuals.car(), 
										   lambdaExpActuals.cdr().car(), actuals)
	}

	#applyDecomposedLambda(tag, formals, body, actuals) {
		const lambdaActuals = tag.eq(Atom.lambda) ? this.#evaluateList(actuals) : actuals
		
		this.env.bind(formals, lambdaActuals)
		const result = this.evaluate(body)
		this.env.unbind(formals.getListLength())

		return result
	}

	#applyPrimitive(primitive, actuals) {
		const args = ['COND', 'QUOTE', 'LAMBDA', 'NLAMBDA', 'DEFUN', 'NDEFUN']
			.some(name => primitive.isWithName(new Atom(name)))
			? actuals 
			: this.#evaluateList(actuals)
		
		return primitive.run(args)
	}

	static #boolToS(bool) {
		return bool ? Atom.t : Atom.nil
	}
}
