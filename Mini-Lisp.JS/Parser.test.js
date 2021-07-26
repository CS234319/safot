const P = require('./Parser')
const ListCreator = require('./ListCreator')
const Atom = require('./Atom')
const Pair = require('./Pair')

const lc = new ListCreator()
const a = new Atom('A')
const b = new Atom('B')
const c = new Atom('C')
const set = new Atom('SET')
const quote = new Atom('QUOTE')

test('parse', () => {
	expect(P.parse('a')).toStrictEqual(a)
	expect(P.parse('(a . b)')).toStrictEqual(new Pair(a, b))
	expect(P.parse('(a b c)')).toStrictEqual(lc.create(a, b ,c))
	expect(P.parse("(set 'b '(a . b))"))
		.toStrictEqual(
			lc.create(set, lc.create(quote, b), lc.create(quote, new Pair(a, b)))
		)
})