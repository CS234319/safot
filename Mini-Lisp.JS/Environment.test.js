const p = require('./Parser')
const Environment = require('./Environment')

const t = p.parse('t')
const nil = p.parse('nil')
const a = p.parse('a')

test('set', () => {	
	const env = new Environment()
	var expected_list = p.parse('((t . t) (nil . nil))')
	expect(Reflect.get(env, 'alist')).toStrictEqual(expected_list)
	
	expect(env.set(a, p.parse('(b . a)'))).toStrictEqual(p.parse('(b . a)'))
	expected_list = p.parse('((a . (b . a)) (t . t) (nil . nil))')
	expect(Reflect.get(env, 'alist')).toStrictEqual(expected_list)

	expect(env.set(a, p.parse('(b a x y z)'))).toStrictEqual(p.parse('(b a x y z)'))
	expected_list = p.parse('((a . (b a x y z)) (a . (b . a)) (t . t) (nil . nil))')
	expect(Reflect.get(env, 'alist')).toStrictEqual(expected_list)
})

test('lookup', () => {	
	const env = new Environment()
	expect(env.lookup(t)).toStrictEqual(t)
	expect(env.lookup(nil)).toStrictEqual(nil)
	expect(env.lookup(a)).toStrictEqual(undefined)
	Reflect.set(env, 'alist', p.parse('((a . (b . a)) (t . t) (nil . nil))'))
	expect(env.lookup(a)).toStrictEqual(p.parse('(b . a)'))
	Reflect.set(env, 'alist', p.parse('((a . (b a x y z)) (a . (b . a)) (t . t) (nil . nil))'))
	expect(env.lookup(a)).toStrictEqual(p.parse('(b a x y z)'))
})

test('bind', () => {
	const env = new Environment()
	env.bind(p.parse('(a b c)'), p.parse('(c (a . b) (b a x y z))'))
	const expected_list = p.parse('((c . (b a x y z)) (b . (a . b)) (a . c) (t . t) (nil . nil))')
	expect(Reflect.get(env, 'alist')).toStrictEqual(expected_list)
})
