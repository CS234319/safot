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

test ('parse reject', () => {
	const stringsArray = Array.from("()[].'")
		.concat(['', '(()'])
	
	for (const s of stringsArray) {
		expect(() => p.parse(s)).toThrow(p.SyntaxError)
	}
})

test('parse atoms', () => {
	utils.expectEquals(p.parse('z'), new Atom('Z'))
	utils.expectEquals(p.parse('a'), a)
	utils.expectEquals(p.parse('nil'), nil)
	utils.expectEquals(p.parse('t'), t)
})

test('parse lists', () => {
	utils.expectEquals(p.parse('()'), nil)
	utils.expectEquals(p.parse('(a)'), list(a))
	utils.expectEquals(p.parse('(a b)'), list(a, b))
	utils.expectEquals(p.parse('(a b c)'), list(a, b ,c))
	utils.expectEquals(p.parse('(a b c d)'), list(a, b ,c, d))
	
})

test('parse nested list', () => {
	const expected = list(list(a, b), list(c, list(d, e)))
	utils.expectEquals(p.parse('((a b) (c (d e)))'), expected)
})

test('parse pair', () => {
	utils.expectEquals(p.parse('(a . b)'), new Pair(a, b))
	utils.expectEquals(p.parse('(a .b)'), new Pair(a, b))
	utils.expectEquals(p.parse('(a. b)'), new Pair(a, b))
	utils.expectEquals(p.parse('(a.b)'), new Pair(a, b))
	utils.expectEquals(p.parse('(a\t.\nb)'), new Pair(a, b))
})

test('parse quote', () => {
	utils.expectEquals(p.parse("'a"), list(q, a))
	utils.expectEquals(p.parse("'()"), list(q, nil))
	utils.expectEquals(p.parse("'(a)"), list(q, list(a)))
	utils.expectEquals(p.parse("'(a 'b)"), list(q, list(a, list(q, b))))
	utils.expectEquals(p.parse("(a 'b c)"), list(a, list(q, b), c))
	utils.expectEquals(p.parse("'(a 'b c 'd)"), list(q, list(a, list(q, b), c, list(q, d))))
})
