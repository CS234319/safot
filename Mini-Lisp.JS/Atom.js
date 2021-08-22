const S = require('./S')

module.exports = class Atom extends S {
	constructor(value) {
		super()
		this._value = value
	}

	getValue() {
		return this._value
	}

	atom() {
		return true
	}

	car() {
		return this.error(Atom.car)
	}

	cdr() {
		return this.error(Atom.cdr)
	}	

	eq(s) {
		return s.atom() && this._value === s._value}

	equals(s) {
		return this.eq(s)
	}

	isList() {
		return this.null()
	}

	getListAsArray() {
		return this.null() ? [] : null
	}

	toString() {
		return this._value.toString()
	}

	static nil 			= new Atom('NIL')
	static t 			= new Atom('T')
	static quote 		= new Atom('QUOTE')
	static lambda 		= new Atom('LAMBDA')
	static nlambda 		= new Atom('NLAMBDA')
	static SET 			= new Atom('SET')
	static defun 		= new Atom('DEFUN')
	static ndefun 		= new Atom('NDEFUN')
	static atom 		= new Atom('ATOM')
	static car 			= new Atom('CAR')
	static cdr 			= new Atom('CDR')
	static cond 		= new Atom('COND')
	static cons 		= new Atom('CONS')
	static error 		= new Atom('ERROR')
	static eval 		= new Atom('EVAL')
	static eq 			= new Atom('EQ')
	static undefined 	= new Atom('UNDEFINED')
	static invalid 		= new Atom('INVALID')
	static bug 			= new Atom('BUG')
	static missing 		= new Atom('MISSING')
	static redundant 	= new Atom('REDUNDANT')
}
