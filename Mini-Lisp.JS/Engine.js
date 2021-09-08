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
			[Atom.car,		1, s => s.car()],
			[Atom.cdr,		1, s => s.cdr()],
			[Atom.atom,		1, s => Engine._boolToS(s.atom())],
			[Atom.eval,		1, s => this.evaluate(s)],
			[Atom.cons,		2, (s, t) => s.cons(t)],
			[Atom.eq,		2, (s, t) => Engine._boolToS(s.eq(t))],
			[Atom.SET,		2, (s, t) => this._env.set(s, t)],
			[Atom.lambda,	2, (s, t) => lc.create(Atom.lambda, s, t)],
			[Atom.nlambda,	2, (s, t) => lc.create(Atom.nlambda, s, t)],
			[Atom.defun,	3, (s, t, u) => this._env.defun(s, t, u)],
			[Atom.ndefun,	3, (s, t, u) => this._env.ndefun(s, t, u)],
			[Atom.cond,		undefined, s => this._evaluateCond(s)],
			[Atom.error, 	undefined, s => s.error()],
		].map(params => new Primitive(...params))
	}

	_initPredefinedFunctions() {
		this._env.set(Atom.nil, Atom.nil)
		this._env.set(Atom.t, Atom.t)
		this.evaluate(parse("(ndefun quote (x) x)"))
		this.evaluate(parse("(defun null (x) (eq x nil))"))
	}

	evaluate(s) {
		if (s.atom()) {
			return this._env.lookup(s)
		}

		if (!s.isList()) {
			s.error(Atom.invalid)
		}

		const primitive = this._primitives.find(p => p.isWithName(s.car()))
		if (primitive) {
			const lc = new ListCreator()
			const args = primitive.isWithName(Atom.error)
				? lc.create(Atom.quote, Atom.error.cons(s.cdr())).cons(s.cdr())
				: s.cdr()
			return this._env.applyPrimitive(primitive, args, this)
		}

		return this._env.applyLambda(s.car(), this.evaluate(s.car()), s.cdr(), this)
	}

	_evaluateCond(testForms) {
		if (testForms.null()) {
			return Atom.nil
		}

		const currPair = testForms.car()
			
		if (currPair.atom()) {
			return currPair.error(Atom.cond)
		}

		if (this.evaluate(currPair.car()).t()) {
			return this.evaluate(currPair.cdr().car())
		}

		return this._evaluateCond(testForms.cdr())
	}

	static _boolToS(bool) {
		return bool ? Atom.t : Atom.nil
	}

	/* EnvironmentObserver */
	globalAdded(globalAtom) {
		this._observers.forEach(o => o.globalAdded(globalAtom))
	}
}
