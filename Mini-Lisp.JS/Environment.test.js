const TestUtils = require('./TestUtils')
const Environment = require('./Environment')
const EvaluationError = require('./EvaluationError')
const Atom = require('./Atom')
const p = require('./Parser')

const utils = new TestUtils()

const expectAList = (listStr) => {
	utils.expectEquals(env.getAList(), p.parse(listStr))
}
const testSet = (keyStr, valStr) => {
	const val = p.parse(valStr)
	utils.expectEquals(env.set(p.parse(keyStr), val), val)
}

test('set', () => {	
	env = new Environment()

	testSet('a', '(b . a)')
	expectAList('((a . (b . a)))')

	testSet('a', '(b a x y z)')
	expectAList('((a . (b a x y z)) (a . (b . a)))')
})

test('defun', () => {
	const testDefun = (nameStr, formalsStr, bodyStr) => {
		const name = p.parse(nameStr)
		const formals = p.parse(formalsStr)
		const body = p.parse(bodyStr)
		const lambda = p.parse(`(lambda ${formalsStr} ${bodyStr})`)
		utils.expectEquals(env.defun(name, formals, body), lambda)
	}

	env = new Environment()

	testDefun('foo', 'nil', "'a")
	expectAList("((foo lambda () 'a))")

	testDefun('bar', '(x xs)', '(cons (x (cdr xs)))')
	expectAList("((bar lambda (x xs) (cons (x (cdr xs)))) (foo lambda () 'a))")	
})

test('ndefun', () => {
	const testNdefun = (nameStr, formalsStr, bodyStr) => {
		const name = p.parse(nameStr)
		const formals = p.parse(formalsStr)
		const body = p.parse(bodyStr)
		const lambda = p.parse(`(nlambda ${formalsStr} ${bodyStr})`)
		utils.expectEquals(env.ndefun(name, formals, body), lambda)
	}

	env = new Environment()

	testNdefun('foo', 'nil', "'a")
	expectAList("((foo nlambda () 'a))")

	testNdefun('bar', '(x xs)', '(cons (x (cdr xs)))')
	expectAList("((bar nlambda (x xs) (cons (x (cdr xs)))) (foo nlambda () 'a))")	
})

test('lookup', () => {	
	const testSetLookup = (keyStr, valueStr) => {
		testSet(keyStr, valueStr)
		utils.expectEquals(env.lookup(p.parse(keyStr)), p.parse(valueStr))
	}
	const testLookupException = (keyStr) => {
		const key = p.parse(keyStr)
		utils.expectException(() => env.lookup(key), key, Atom.undefined)
	}

	env = new Environment()
	testLookupException('t')
	testLookupException('nil')
	testLookupException('a')
	
	testSetLookup('a', '(b . a)')
	testSetLookup('a', '(b a x y z)')

	testLookupException('b')
	
	env = new Environment()
	testLookupException('a')
})
