const p = require('./Parser')
const ListCreator = require('./ListCreator')
const Atom = require('./Atom')
const Pair = require('./Pair')
const TestUtils = require('./TestUtils')

const utils = new TestUtils()

const lc = new ListCreator()
const a = new Atom('A')
const b = new Atom('B')
const c = new Atom('C')
const d = new Atom('D')
const e = new Atom('E')
const t = Atom.t
const nil = Atom.nil
const q = Atom.quote

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
	utils.expectEquals(p.parse('(a)'), lc.create(a))
	utils.expectEquals(p.parse('(a b)'), lc.create(a, b))
	utils.expectEquals(p.parse('(a b c)'), lc.create(a, b ,c))
	utils.expectEquals(p.parse('(a b c d)'), lc.create(a, b ,c, d))
	
})

test('parse nested list', () => {
	const expected = lc.create(lc.create(a, b), lc.create(c, lc.create(d, e)))
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
	utils.expectEquals(p.parse("'a"), lc.create(q, a))
	utils.expectEquals(p.parse("'()"), lc.create(q, nil))
	utils.expectEquals(p.parse("'(a)"), lc.create(q, lc.create(a)))
	utils.expectEquals(p.parse("'(a 'b)"), lc.create(q, lc.create(a, lc.create(q, b))))
	utils.expectEquals(p.parse("(a 'b c)"), lc.create(a, lc.create(q, b), c))
	utils.expectEquals(p.parse("'(a 'b c 'd)"), lc.create(q, lc.create(a, lc.create(q, b), c, lc.create(q, d))))
		
})
