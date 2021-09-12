const TestUtils = require('./TestUtils')
const Environment = require('./Environment')
const EvaluationError = require('./EvaluationError')
const Atom = require('./Atom')
const Primitive = require('./Primitive')
const parse = require('./Parser').parse

const utils = new TestUtils()

const testSetLookup = (keyStr, valStr) => {
	const key = parse(keyStr)
	const val = parse(valStr)
	utils.expectEquals(env.set(key, val), val)
	utils.expectEquals(env.lookup(key), val)
}
const parseSet = (keyStr, valStr) => {
	env.set(parse(keyStr), parse(valStr))
}
const testDefunLookup = (nameStr, formalsStr, bodyStr) => {
	testGenericDefunLookup('lambda', nameStr, formalsStr, bodyStr, (name, formals, body) => {
		return env.defun(name, formals, body)
	})
}
const testNdefunLookup = (nameStr, formalsStr, bodyStr) => {
	testGenericDefunLookup('nlambda', nameStr, formalsStr, bodyStr, (name, formals, body) => {
		return env.ndefun(name, formals, body)
	})
}
const testGenericDefunLookup = (tagStr, nameStr, formalsStr, bodyStr, defunFunc) => {
	const name = parse(nameStr)
	const formals = parse(formalsStr)
	const body = parse(bodyStr)
	const lambda = parse(`(${tagStr} ${formalsStr} ${bodyStr})`)
	utils.expectEquals(defunFunc(name, formals, body), lambda)
	utils.expectEquals(env.lookup(name), lambda)
}
const testLookupException = (keyStr) => {
	const key = parse(keyStr)
	utils.expectException(() => env.lookup(key), key, Atom.undefined)
}

test('set and lookup', () => {	
	env = new Environment()
	testSetLookup('a', '[b . a]')
	testSetLookup('a', '(b a x y z)')
})

test('defun and lookup', () => {
	env = new Environment()
	testDefunLookup('foo', 'nil', "'a")
	testDefunLookup('bar', '(x xs)', '(cons (x (cdr xs)))')
})

test('ndefun and lookup', () => {
	env = new Environment()
	testNdefunLookup('foo', 'nil', "'a")
	testNdefunLookup('bar', '(x xs)', '(cons (x (cdr xs)))')
})

test('lookup exception', () => {	
	env = new Environment()
	testLookupException('t')
	testLookupException('nil')
	testLookupException('a')
	
	testSetLookup('a', '[b . a]')
	testSetLookup('a', '(b a x y z)')

	testLookupException('b')
	
	env = new Environment()
	testLookupException('a')
})
