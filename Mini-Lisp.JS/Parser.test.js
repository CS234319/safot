const p = require('./Parser')
const ListCreator = require('./ListCreator')
const Atom = require('./Atom')
const Pair = require('./Pair')

const lc = new ListCreator()
const a = new Atom('A')
const b = new Atom('B')
const c = new Atom('C')
const set = new Atom('SET')
const quote = new Atom('QUOTE')
const some_function = new Atom('SOME_FUNCTION')

test('parse', () => {
	expect(p.parse('a')).toStrictEqual(a)
	expect(p.parse('(a . b)')).toStrictEqual(new Pair(a, b))
	expect(p.parse('(a b c)')).toStrictEqual(lc.create(a, b ,c))
	expect(p.parse("(set 'b '(a . b))"))
		.toStrictEqual(
			lc.create(set, lc.create(quote, b), lc.create(quote, new Pair(a, b)))
		)
	expect(p.parse("(some_function 'a)"))
		.toStrictEqual(lc.create(some_function, lc.create(quote, a)))
})