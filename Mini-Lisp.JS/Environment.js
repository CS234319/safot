const Atom = require('./Atom')
const ListCreator = require('./ListCreator')
const EvaluationError = require('./EvaluationError')

module.exports = class Environment {
	constructor() {
		this._alist = Atom.nil
		this._deepBind(Atom.nil, Atom.nil)
		this._separatorNode = this._alist
		this._observers = Array.from(arguments)
	}

	set(key, value) {
		this._separatorNode.insert(key.cons(value))
		this._observers.forEach(o => o.globalAdded(key))
		return value
	}

	defun(name, formals, body) {
		return this._genericDefun(name, formals, body, Atom.lambda)
	}

	ndefun(name, formals, body) {
		return this._genericDefun(name, formals, body, Atom.nlambda)
	}

	_genericDefun(name, formals, body, tag) {
		const lc = new ListCreator()
		const lambda = lc.create(tag, formals, body)
		return this.set(name, lambda)	
	}

	lookup(s) {
		return Environment._lookup(s, this._alist)
	}

	static _lookup(s, list) {
		if (list.null()) {
			 return s.error(Atom.undefined)
		}

		const currPair = list.car()
		return s.eq(currPair.car())
			? currPair.cdr()
			: Environment._lookup(s, list.cdr()) 
	}

	bindLambdaRecords(lambdaName, lambda, args, evaluator) {
		const tag = lambda.car()
		const formals = lambda.cdr().car()
		
		const lc = new ListCreator()
		this._deepBind(Atom.invocation, lc.create(lambdaName, formals, args))
		this._bindFormals(formals, args, tag.eq(Atom.lambda) ? evaluator : null)
		this._bind(Atom.recurse, lambda)
	}

	popLambdaRecords() {
		this._alist = this._getNodeByDeepKey(Atom.invocation).cdr()
	}

	_bindFormals(formals, args, evaluator) {
		const bindedFormalsList = this._bindFormalsOnList(
			Atom.nil, formals, args, evaluator
		)

		this._alist = this._alist.prependList(bindedFormalsList)
	}

	_bindFormalsOnList(list, formals, args, evaluator) {
		if (formals.null() && args.null()) {
			return list
		}

		const arg = args.car()
		this._deepBind(Atom.argument, arg)
		const actual = evaluator ? evaluator.evaluate(arg) : arg
		list = list.prependPair(formals.car(), actual)

		return this._bindFormalsOnList(list, formals.cdr(), args.cdr(), evaluator)
	}

	_bind(key, value) {
		this._alist = this._alist.prependPair(key, value)
	}

	_deepBind(key, value) {
		this._bind(key.cons(value), Atom.nil)
	}

	_getNodeByDeepKey(key) {
		return Environment._getNodeByDeepKey(this._alist, key)
	}

	static _getNodeByDeepKey(list, key) {
		if (list.null()) {
			return key.error(Atom.bug)
		}

		if (!list.car().car().atom() && 
			(list.car().car().car().eq(key))) {
			return list
		}
		
	 	return Environment._getNodeByDeepKey(list.cdr(), key)
	}	
}
