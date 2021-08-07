const TestUtils = require('./TestUtils')
const Environment = require('./Environment')
const EvaluationError = require('./EvaluationError')
const Atom = require('./Atom')
const parse = require('./Parser').parse

const utils = new TestUtils()

const expectAList = (listStr) => {
	utils.expectEquals(env.getAList(), parse(listStr))
}
const expectFormalsAList = (listStr) => {
	utils.expectEquals(env.getFormalsAList(), parse(listStr))
}
const testSet = (keyStr, valStr) => {
	const val = parse(valStr)
	utils.expectEquals(env.set(parse(keyStr), val), val)
}
const parseBind = (formalsStr, actualsStr) => {
	utils.expectEquals(env.bind(parse(formalsStr), parse(actualsStr)), undefined)
}
const parseBindException = (formalsStr, actualsStr, s) => {
	utils.parseExpectException(() => parseBind(formalsStr, actualsStr), s, 'car')
}
const testUnbind = (numFormals) => {
	utils.expectEquals(env.unbind(numFormals), undefined)
}
const expectUnbindException = (numFormals) => {
	utils.expectException(() => env.unbind(numFormals), Atom.nil, Atom.cdr)
	
}
const testSetLookup = (keyStr, valueStr) => {
	testSet(keyStr, valueStr)
	utils.expectEquals(env.lookup(parse(keyStr)), parse(valueStr))
}
const testLookupException = (keyStr) => {
	const key = parse(keyStr)
	utils.expectException(() => env.lookup(key), key, Atom.undefined)
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
		const name = parse(nameStr)
		const formals = parse(formalsStr)
		const body = parse(bodyStr)
		const lambda = parse(`(lambda ${formalsStr} ${bodyStr})`)
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
		const name = parse(nameStr)
		const formals = parse(formalsStr)
		const body = parse(bodyStr)
		const lambda = parse(`(nlambda ${formalsStr} ${bodyStr})`)
		utils.expectEquals(env.ndefun(name, formals, body), lambda)
	}

	env = new Environment()

	testNdefun('foo', 'nil', "'a")
	expectAList("((foo nlambda () 'a))")

	testNdefun('bar', '(x xs)', '(cons (x (cdr xs)))')
	expectAList("((bar nlambda (x xs) (cons (x (cdr xs)))) (foo nlambda () 'a))")	
})

test('lookup', () => {	
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

test('backup and restore', () => {	
	env = new Environment()
	expectAList("()")
	env.backup()
	expectAList("()")
	testSet('a', 'b')
	expectAList("((a . b))")
	env.restore()
	expectAList("()")
	testSet('a', 'b')
	testSet('c', 'd')
	env.backup()
	testSet('e', 'f')
	env.restore()
	expectAList("((c . d) (a . b))")
})

test('bind', () => {	
	env = new Environment()
	expectFormalsAList('()')
	parseBind('()', '()')
	expectFormalsAList('()')
	parseBind('(a b)', '(c d)')
	expectFormalsAList('((b . d) (a . c))')
	parseBind('(a a)', '(b c)')
	expectFormalsAList('((a . c) (a . b) (b . d) (a . c))')
	testSetLookup('a', 'c')
	testSetLookup('b', 'd')
	testLookupException('c')
	parseBindException('a', '(b)', 'a')
	parseBindException('(b)', 'a', 'a')
	parseBindException('(b)', 'a', 'a')
	parseBindException('()', 'a', '()')
	parseBindException('a', '()', 'a')
	parseBindException('(a)', '(b c)', '()')
	parseBindException('(a b)', '(c)', '()')
	parseBindException('(a b c)', '(d)', '()')
	parseBindException('(a b)', '(c d e)', '()')
})

test('unbind', () => {
	env = new Environment()
	expectFormalsAList('()')
	expectUnbindException(1)
	testUnbind(0)
	parseBind('(a b)', '(c d)')
	testUnbind(2)
	expectFormalsAList('()')
	parseBind('(a b)', '(c d)')
	testUnbind(1)
	expectFormalsAList('((a . c))')
	testUnbind(1)
	expectFormalsAList('()')
	parseBind('(a b)', '(c d)')
	expectUnbindException(3)
})
