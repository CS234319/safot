const p = require('./Parser')
const ListCreator = require('./ListCreator')
const Atom = require('./Atom')
const Pair = require('./Pair')
const TestUtils = require('./TestUtils')

const utils = new TestUtils()

const a = new Atom('A')
const b = new Atom('B')
const c = new Atom('C')
const d = new Atom('D')
const e = new Atom('E')
const t = Atom.t
const nil = Atom.nil

const lc = new ListCreator()
const list = function() { return lc.create(...arguments) }
const q = s => list(Atom.quote, s)
const parseEquals = (str, s) => {
	Reflect.get(utils, 'parseExpectEquals').call(utils, str, s)
}

test ('parse reject', () => {
	const stringsArray = Array.from("()[].';")
		.concat(['', '(()'])
	
	for (const s of stringsArray) {
		expect(() => p.parse(s)).toThrow(p.SyntaxError)
	}
})

test('parse atoms', () => {
	parseEquals('z', new Atom('Z'))
	parseEquals('a', a)
	parseEquals('nil', nil)
	parseEquals('t', t)
})

test('parse lists', () => {
	parseEquals('()', nil)
	parseEquals('(a)', list(a))
	parseEquals('(a b)', list(a, b))
	parseEquals('(a b c)', list(a, b ,c))
	parseEquals('(a b c d)', list(a, b ,c, d))
	parseEquals('(a . (b . (c . (d . nil))))', list(a, b ,c, d))
	
})

test('parse nested list', () => {
	parseEquals('((a b) (c (d e)))', list(list(a, b), list(c, list(d, e))))
})

test('parse pair', () => {
	const pair = new Pair(a, b)
	parseEquals('(a . b)', 		pair)
	parseEquals('(a .b)', 		pair)
	parseEquals('(a. b)', 		pair)
	parseEquals('(a.b)', 		pair)
	parseEquals('(a\t.\nb)', 	pair)
})

test('parse quote', () => {
	parseEquals("'a", q(a))
	parseEquals("'()", q(nil))
	parseEquals("'(a)", q(list(a)))
	parseEquals("'(a 'b)", q(list(a, q(b))))
	parseEquals("(a 'b c)", list(a, q(b), c))
	parseEquals("'(a 'b c 'd)", q(list(a, q(b), c, q(d))))
})

test('parse with whitespace', () => {
	parseEquals("\n a", a)
	parseEquals("a\n \n", a)
	parseEquals("\n\ta\n\n", a)
	parseEquals("\n\t'('a)\n\n", q(list(q(a))))
})

test('parse comment', () => {
	parseEquals(";\na", a)
	parseEquals(";comment\n\n\na", a)
	parseEquals(";comment\n\t\r ';another comment\na", q(a))
	parseEquals(";b\n(a 'b c);c;d\n;e", list(a, q(b), c))
	parseEquals(";b\n(a.\n('b.(c.nil)));c;d\n;e", list(a, q(b), c))
	parseEquals(";b\n(a . b);c;d\n;e", new Pair(a, b))
	parseEquals(";b\n(a.\n('b.; some comment \n(c.nil)));c;d\n;e", list(a, q(b), c))
})
