const p = require('./Parser')
const Environment = require('./Environment')

const t = p.parse('t')
const nil = p.parse('nil')
const a = p.parse('a')
const qa = p.parse("'a")

var env = new Environment()
const init = () => {
	env = new Environment()
	env.set(nil, nil)
	env.set(t, t)
}

test('init', () => {
	init()
	expectedList = p.parse('((t . t) (nil . nil))')
	expect(env.getAList()).toStrictEqual(expectedList)
})

test('set', () => {	
	init()
	expect(env.set(a, p.parse('(b . a)'))).toStrictEqual(p.parse('(b . a)'))
	expectedList = p.parse('((a . (b . a)) (t . t) (nil . nil))')
	expect(env.getAList()).toStrictEqual(expectedList)

	expect(env.set(a, p.parse('(b a x y z)'))).toStrictEqual(p.parse('(b a x y z)'))
	expectedList = p.parse('((a . (b a x y z)) (a . (b . a)) (t . t) (nil . nil))')
	expect(env.getAList()).toStrictEqual(expectedList)
})

test('defun', () => {
	init()
	expect(env.defun(p.parse('foo'), nil, qa)).toStrictEqual(p.parse("(lambda () 'a)"))
	expectedList = p.parse("((foo lambda () 'a) (t . t) (nil . nil))")

	body = p.parse('(cons (x (cdr xs)))')
	expect(env.defun(p.parse('bar'), p.parse('(x xs)'), body))
		.toStrictEqual(p.parse("(lambda (x xs) (cons (x (cdr xs))))"))
	expectedList = p.parse("((bar lambda (x xs) (cons (x (cdr xs)))) " +
							"(foo lambda () 'a) (t . t) (nil . nil))")
})

test('ndefun', () => {
	init()
	expect(env.ndefun(p.parse('foo'), nil, qa)).toStrictEqual(p.parse("(nlambda () 'a)"))
	expectedList = p.parse("((foo nlambda () 'a) (t . t) (nil . nil))")
	expect(env.getAList()).toStrictEqual(expectedList)

	body = p.parse('(cons (x (cdr xs)))')
	expect(env.ndefun(p.parse('bar'), p.parse('(x xs)'), body))
		.toStrictEqual(p.parse("(nlambda (x xs) (cons (x (cdr xs))))"))
	expectedList = p.parse("((bar nlambda (x xs) (cons (x (cdr xs)))) " +
							"(foo nlambda () 'a) (t . t) (nil . nil))")
	expect(env.getAList()).toStrictEqual(expectedList)
})

test('lookup', () => {	
	init()
	expect(env.lookup(t)).toStrictEqual(t)
	expect(env.lookup(nil)).toStrictEqual(nil)
	expect(env.lookup(a)).toStrictEqual(undefined)
	env.set(a, p.parse('(b . a)'))
	expect(env.lookup(a)).toStrictEqual(p.parse('(b . a)'))
	env.set(a, p.parse('(b a x y z)'))
	expect(env.lookup(a)).toStrictEqual(p.parse('(b a x y z)'))
})

test('bind', () => {
	init()
	env.bind(p.parse('(a b c)'), p.parse('(c (a . b) (b a x y z))'))
	expectedList = p.parse('((c . (b a x y z)) (b . (a . b)) (a . c) (t . t) (nil . nil))')
	expect(env.getAList()).toStrictEqual(expectedList)
})

test('unbind', () => {
	init()
	env.unbind(1)
	expect(env.getAList()).toStrictEqual(p.parse('((nil . nil))'))
	init()
	env.unbind(2)
	expect(env.getAList()).toStrictEqual(nil)
})
