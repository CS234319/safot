const Environment = require('./Environment')
const Atom = require('./Atom')
const Primitive = require('./Primitive')
const ListCreator = require('./ListCreator')

module.exports = class Engine {
	constructor() {
		const lc = new ListCreator()

		this.env = new Environment()
		this.primitives = [
			['CAR',			1, s => s.car()],
			['CDR',			1, s => s.cdr()],
			['QUOTE',		1, s => s],
			['ATOM',		1, s => Engine.#boolToS(s.atom())],
			['NULL',		1, s => Engine.#boolToS(s.null())],
			['ERROR',		1, s => this.#evaluateError(s)],
			['EVAL',		1, s => s],
			['CONS',		2, (s, t) => s.cons(t)],
			['EQ',			2, (s, t) => Engine.#boolToS(s.eq(t))],
			['SET',			2, (s, t) => this.env.set(s, t)],
			['COND',		undefined, s => this.#evaluateCond(s)]
		].map(tup => new Primitive(new Atom(tup[0]), tup[1], tup[2]))
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

		//TODO: replace with 'apply' method
		return Atom.nil
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

	#evaluateCond(test_forms) {
		if (test_forms.null()) {
			return Atom.nil
		}

		if (test_forms.atom()) {
			throw 'COND: test forms must be a list'
		}

		const curr_pair = test_forms.car()
			
		if (curr_pair.atom()) {
			throw 'COND: all expressions in test forms must be pairs'
		}

		if (this.#evaluateToBool(curr_pair.car())) {
			return this.evaluate(curr_pair.cdr().car())
		}

		return this.#evaluateCond(test_forms.cdr())
	}

	#evaluateToBool(s) {
		return !this.evaluate(s).null()
	}

	#applyPrimitive(primitive, actuals) {
		const args = ['COND', 'QUOTE'].some(name => primitive.isWithName(new Atom(name)))
			? actuals 
			: this.#evaluateList(actuals)
		
		return primitive.run(args)
	}

	static #boolToS(bool) {
		return bool ? Atom.t : Atom.nil
	}
}
