const Atom = require('./Atom')
const Lambda = require('./Lambda')
const ListCreator = require('./ListCreator')
const StackDumper = require('./StackDumper')

module.exports = class Environment {
	constructor() {
		this._alist = Atom.nil
		this._push(Atom.separator, Atom.nil)
		this._separatorNode = this._alist
		this._observers = Array.from(arguments)
		this._stackDumper = new StackDumper(this)
	}

	_push(key, value) {
		this._alist = this._alist.prependPair(key, value)
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

	lookup(key) {
		return this._getNodeByKey(key).car().cdr()
	}

	_getNodeByKey(key) {
		return Environment._getNodeByKey(key, this._alist)
	}

	static _getNodeByKey(key, list) {
		if (list.null()) {
			key.error(Atom.undefined)
		}

		return list.car().car().eq(key)
			? list
			: Environment._getNodeByKey(key, list.cdr())
	}

	applyPrimitive(primitive, args, evaluator) {
		const savedAList = this._alist
		this._pushInvocation(primitive.getName(), args)

		try {
			primitive.checkNumberOfArgs(args)
			const actuals = this._pushPrimitiveRecords(primitive, args, evaluator)
			return this._applyAndPopInvocation(() => primitive.run(actuals))
		} catch (e) {
			this._stackDumper.apply(e)
		}
	}

	applyLambda(name, lambdaS, args, evaluator) {
		this._pushInvocation(name, args)

		try {
			const lambda = new Lambda(lambdaS, args)
			this._pushLambdaRecords(lambda, args, evaluator)
			return this._applyAndPopInvocation(() => evaluator.evaluate(lambda.body))
		} catch (e) {
			this._stackDumper.apply(e)
		}
	}

	_applyAndPopInvocation(apply) {
		const result = apply()
		this._popInvocation()
		return result		
	}

	_getActuals(args, shouldEvaluateArgs, evaluator) {
		return this._pushArgsAndGetActuals(
			args, Atom.nil, shouldEvaluateArgs, evaluator
		)
	}

	_pushPrimitiveRecords(primitive, args, evaluator) {
		return this._getActuals(args, primitive.isEager(), evaluator)
	}

	_pushLambdaRecords(lambda, args, evaluator) {
		const actuals = this._getActuals(args, lambda.tag.eq(Atom.lambda), evaluator)
		this._push(Atom.recurse, lambda.s)
		this._pushLists(lambda.formals, actuals)
	}

	_pushArgsAndGetActuals(args, actuals, shouldEvaluateArgs, evaluator) {
		if (args.null()) {
			actuals.reverseList()
			this._pushArgs(args, actuals)
			return actuals
		}

		const arg = args.car()
		try {
			const actual = shouldEvaluateArgs ? evaluator.evaluate(arg) : arg
			actuals = actual.cons(actuals)
		} catch (e) {
			this._pushArgs(args, actuals.reversedList())
			throw e
		}
		
		return this._pushArgsAndGetActuals(
			args.cdr(), actuals, shouldEvaluateArgs, evaluator
		)
	}

	_pushLists(keys, values) {
		if (keys.null() || values.null()) {
			return
		}

		this._push(keys.car(), values.car())
		this._pushLists(keys.cdr(), values.cdr())
	}

	_pushInvocation(name, args) {
		this._push(Atom.invocation, name.cons(args))
	}

	_pushArgs(args, actuals) {
		this._push(Atom.arguments, args.cons(actuals))
	}

	_popInvocation() {
		this.popUntilReachingInvocation()
		this.pop()
	}

	/* Stack Dumper Delegate */
	pop() {
		this._alist = this._alist.cdr()
	}

	popUntilReachingRecord() {
		const recordKeys = [Atom.invocation, Atom.arguments]
		for (; !recordKeys.includes(this._topKey()); this.pop());
	}

	popUntilReachingInvocation() {
		this._alist = this._getNodeByKey(Atom.invocation)
	}

	top() {
		return this._topValue()
	}

	checkTop(key) {
		return this._topKey().eq(key)
	}

	_topPair() {
		return this._alist.car()
	}

	_topKey() {
		return this._topPair().car()
	}

	_topValue() {
		return this._topPair().cdr()
	}
}
