const TestUtils = require('./TestUtils')
const Environment = require('./Environment')
const EvaluationError = require('./EvaluationError')
const Atom = require('./Atom')
const p = require('./Parser')

const utils = new TestUtils()

const expectAList = (alistStr) => {
	utils.expectEquals(env.getAList(), p.parse(alistStr))
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

test('bind', () => {
	const bind = (formalsStr, actualsStr) => {
		env.bind(p.parse(formalsStr), p.parse(actualsStr))
	}
	const testBindException = (formalsStr, actualsStr, culpritStr, kindStr) => {
		const formals = p.parse(formalsStr)
		const actuals = p.parse(actualsStr)
		const culprit = p.parse(culpritStr)
		const kind = p.parse(kindStr)
		utils.expectException(() => env.bind(formals, actuals), culprit, kind)
	}

	env = new Environment()
	bind('(a b c)', '(c (a . b) (b a x y z))')
	expectAList('((c . (b a x y z)) (b . (a . b)) (a . c))')

	bind('(a)', '((t t))')
	expectAList('((a . (t t)) (c . (b a x y z)) (b . (a . b)) (a . c))')

	testBindException('a', 'b', 'a', 'invalid')
	testBindException('a', '()', 'a', 'invalid')
	testBindException('a', '(a)', 'a', 'invalid')
	testBindException('()', 'a', 'a', 'invalid')
	testBindException('(a)', 'a', 'a', 'invalid')
	testBindException('(a . b)', '(a)', '(a . b)', 'invalid')
	testBindException('(a a a)', '(a a t nil)', '(a a t nil)', 'redundant')
	testBindException('(a a a)', '(a b)', '(a b)', 'missing')
})
