const TestUtils = require('./TestUtils')
const Environment = require('./Environment')
const EvaluationError = require('./EvaluationError')
const Atom = require('./Atom')
const p = require('./Parser')

const utils = new TestUtils()

const t = p.parse('t')
const nil = p.parse('nil')
const a = p.parse('a')
const b = p.parse('b')
const qa = p.parse("'a")


test('set', () => {	
	env = new Environment()
	expect(env.set(a, p.parse('(b . a)'))).toStrictEqual(p.parse('(b . a)'))
	expectedList = p.parse('((a . (b . a)))')
	expect(env.getAList()).toStrictEqual(expectedList)

	expect(env.set(a, p.parse('(b a x y z)'))).toStrictEqual(p.parse('(b a x y z)'))
	expectedList = p.parse('((a . (b a x y z)) (a . (b . a)))')
	expect(env.getAList()).toStrictEqual(expectedList)
})

test('defun', () => {
	env = new Environment()
	expect(env.defun(p.parse('foo'), nil, qa)).toStrictEqual(p.parse("(lambda () 'a)"))
	expectedList = p.parse("((foo lambda () 'a))")

	body = p.parse('(cons (x (cdr xs)))')
	expect(env.defun(p.parse('bar'), p.parse('(x xs)'), body))
		.toStrictEqual(p.parse("(lambda (x xs) (cons (x (cdr xs))))"))
	expectedList = p.parse("((bar lambda (x xs) (cons (x (cdr xs)))) " +
							"(foo lambda () 'a))")
})

test('ndefun', () => {
	env = new Environment()
	expect(env.ndefun(p.parse('foo'), nil, qa)).toStrictEqual(p.parse("(nlambda () 'a)"))
	expectedList = p.parse("((foo nlambda () 'a))")
	expect(env.getAList()).toStrictEqual(expectedList)

	body = p.parse('(cons (x (cdr xs)))')
	expect(env.ndefun(p.parse('bar'), p.parse('(x xs)'), body))
		.toStrictEqual(p.parse("(nlambda (x xs) (cons (x (cdr xs))))"))
	expectedList = p.parse("((bar nlambda (x xs) (cons (x (cdr xs)))) " +
							"(foo nlambda () 'a))")
	expect(env.getAList()).toStrictEqual(expectedList)
})

test('lookup', () => {	
	env = new Environment()
	utils.expectException(() => env.lookup(t), t, Atom.undefined)
	utils.expectException(() => env.lookup(nil), nil, Atom.undefined)
	utils.expectException(() => env.lookup(a), a, Atom.undefined)
	
	env.set(a, p.parse('(b . a)'))
	expect(env.lookup(a)).toStrictEqual(p.parse('(b . a)'))
	
	env.set(a, p.parse('(b a x y z)'))
	expect(env.lookup(a)).toStrictEqual(p.parse('(b a x y z)'))
	utils.expectException(() => env.lookup(b), b, Atom.undefined)
	
	env = new Environment()
	utils.expectException(() => env.lookup(a), a, Atom.undefined)
})

test('bind', () => {
	formals = p.parse('(a b c)')
	actuals =  p.parse('(c (a . b) (b a x y z))')	

	env = new Environment()
	env.bind(formals, actuals)
	expectedList = p.parse('((c . (b a x y z)) (b . (a . b)) (a . c))')
	expect(env.getAList()).toStrictEqual(expectedList)

	utils.expectException(() => env.bind(a, nil), a, Atom.invalid)
	utils.expectException(() => env.bind(a, p.parse('(a)')), a, Atom.invalid)
	utils.expectException(() => env.bind(nil, a), a, Atom.invalid)
	utils.expectException(() => env.bind(p.parse('(a)'), a), a, Atom.invalid)
	utils.expectException(() => env.bind(p.parse('(a . b)'), p.parse('(a)')), 
		p.parse('(a . b)'), Atom.invalid)
	utils.expectException(() => env.bind(p.parse('(a a a)'), 
		p.parse('(a a t nil)')), p.parse('(nil)'), Atom.redundant)
	utils.expectException(() => env.bind(p.parse('(a a a)'), 
		p.parse('(a b)')), p.parse('(a)'), Atom.missing)
})

test('unbind', () => {
	env = new Environment()
	utils.expectException(() => env.unbind(1), nil, Atom.invalid)

	formals = p.parse('(a b c)')
	actuals =  p.parse('(c (a . b) (b a x y z))')
	
	env.bind(formals, actuals)
	env.unbind(3)
	expect(env.getAList()).toStrictEqual(nil)
	
	env.bind(formals, actuals)
	env.unbind(2)
	expect(p.parse('((a . c))')).toStrictEqual(p.parse('((c . (b a x y z)))'))
	
	// utils.expectException(() => env.unbind(2), p.parse('(c . (b a x y z))'), Atom.invalid)
})

test('backup', () => {
		
})
