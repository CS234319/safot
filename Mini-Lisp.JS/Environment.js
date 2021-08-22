const Atom = require('./Atom')
const ListCreator = require('./ListCreator')
const EvaluationError = require('./EvaluationError')

module.exports = class Environment {
	constructor(observer) {
		this._separatorNode = Atom.nil.cons(Atom.nil)
		this._alist = this._separatorNode
		this._observer = observer
	}

	getAList() {
		return this._alist
	}

	setAList(alist) {
		this._alist = alist
	}

	set(key, value) {
		this._separatorNode.insert(key.cons(value))
		
		if (this._observer) {
			this._observer.globalAdded(key)	
		}
		
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

		if (Environment._isSeparator(list)) {
			return Environment._lookup(s, list.cdr()) 
		}

		const currPair = list.car()
		return s.eq(currPair.car())
			? currPair.cdr()
			: Environment._lookup(s, list.cdr()) 
	}

	static _isSeparator(node) {
		return node.car().null()
	}

	bind(formals, actuals) {
		this._alist = Environment._bind(formals, actuals, this._alist)
		return this._alist
	}

	static _bind(formals, actuals, list) {
		if (formals.null() && actuals.null()) {
			return list
		}

		return Environment._bind(formals.cdr(), actuals.cdr(), 
						  		 formals.car().cons(actuals.car()).cons(list))
	}
}
