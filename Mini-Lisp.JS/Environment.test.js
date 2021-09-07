const TestUtils = require('./TestUtils')
const Environment = require('./Environment')
const EvaluationError = require('./EvaluationError')
const Atom = require('./Atom')
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

class EngineStub {
	evaluate(s) {
		return Atom.nil
	}
}

const engineStub = new EngineStub()

const testBindLambdaRecord = (nameStr, lambdaStr, argsStr) => {
	const lambdaName = parse(nameStr)
	const lambda = parse(lambdaStr)
	const args = parse(argsStr)

	env.bindLambdaRecords(lambdaName, lambda, args, engineStub)
	testCurrentLambdaRecord(lambdaStr, argsStr)
}
const testLookup = (key, value) => {
	utils.expectEquals(env.lookup(key), value)
}
const testRecurse = lambda => {
	testLookup(Atom.recurse, lambda)
}
const testFormals = (lambda, args) => {
	const tag = lambda.car()
	const shouldEvaluate = tag.eq(Atom.lambda)
	const formalsArray = lambda.cdr().car().getListAsArray()
	const argsArray = args.getListAsArray()

	Array.zip(formalsArray, argsArray).forEach(([formal, arg]) => {
		const actual = shouldEvaluate ? engineStub.evaluate(arg) : arg
		testLookup(formal, actual)
	})
}
const testCurrentLambdaRecord = (lambdaStr, argsStr) => {
	const lambda = parse(lambdaStr)
	const args = parse(argsStr)
	testRecurse(lambda)
	testFormals(lambda, args)
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

test('lambda records', () => {
	env = new Environment()
	const prevAList = env._alist
	testBindLambdaRecord('foo', '(lambda nil nil)', 'nil')
	testBindLambdaRecord('bar', '(nlambda (x y z) nil)', '(a b c)')
	testBindLambdaRecord('baz', '(lambda (x y z) nil)', '(d e f)')
	env.popLambdaRecords()
	testCurrentLambdaRecord('(nlambda (x y z) nil)', '(a b c)')
	env.popLambdaRecords()
	env.popLambdaRecords()
	utils.expectEquals(env._alist, prevAList)
})
