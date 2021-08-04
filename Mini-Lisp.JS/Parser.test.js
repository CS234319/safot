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
const q = Atom.quote

const lc = new ListCreator()
const list = function() { return lc.create(...arguments) }
const parseEquals = (str, s) => utils.expectEquals(p.parse(str), s)

test ('parse reject', () => {
	const stringsArray = Array.from("()[].'")
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
	
})

test('parse nested list', () => {
	const expected = list(list(a, b), list(c, list(d, e)))
	parseEquals('((a b) (c (d e)))', expected)
})

test('parse pair', () => {
	parseEquals('(a . b)', new Pair(a, b))
	parseEquals('(a .b)', new Pair(a, b))
	parseEquals('(a. b)', new Pair(a, b))
	parseEquals('(a.b)', new Pair(a, b))
	parseEquals('(a\t.\nb)', new Pair(a, b))
})

test('parse quote', () => {
	parseEquals("'a", list(q, a))
	parseEquals("'()", list(q, nil))
	parseEquals("'(a)", list(q, list(a)))
	parseEquals("'(a 'b)", list(q, list(a, list(q, b))))
	parseEquals("(a 'b c)", list(a, list(q, b), c))
	parseEquals("'(a 'b c 'd)", list(q, list(a, list(q, b), c, list(q, d))))
})
