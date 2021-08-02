const p = require('./Parser')
const ListCreator = require('./ListCreator')
const Atom = require('./Atom')
const Pair = require('./Pair')

const lc = new ListCreator()
const a = new Atom('A')
const b = new Atom('B')
const c = new Atom('C')
const d = new Atom('D')
const e = new Atom('E')
const t = Atom.t
const nil = Atom.nil
const q = Atom.quote

test('parse accept', () => {
	const stringsArray = ["a.b", "(a.b)", "().()", "().NIL", "'a.b",
						 "'a.'b", "'(a.b)", "().'()", "().'NIL"]
	
	for (s of stringsArray) {
		expect(() => p.parse(s)).not.toThrow()
	}						 
})

test ('parse reject', () => {
	const stringsArray = Array.from("()[].'")
		.concat(['', '(()'])
	
	for (s of stringsArray) {
		expect(() => p.parse(s)).toThrow(p.SyntaxError)
	}
})

test('parse atoms', () => {
	expect(p.parse('z')).toStrictEqual(new Atom('Z'))
	expect(p.parse('a')).toStrictEqual(a)
	expect(p.parse('nil')).toStrictEqual(nil)
	expect(p.parse('t')).toStrictEqual(t)
})

test('parse lists', () => {
	expect(p.parse('()')).toStrictEqual(nil)
	expect(p.parse('(a)')).toStrictEqual(lc.create(a))
	expect(p.parse('(a b)')).toStrictEqual(lc.create(a, b))
	expect(p.parse('(a b c)')).toStrictEqual(lc.create(a, b ,c))
	expect(p.parse('(a b c d)')).toStrictEqual(lc.create(a, b ,c, d))
	
})

test('parse nested list', () => {
	const expected = lc.create(lc.create(a, b), lc.create(c, lc.create(d, e)))
	expect(p.parse('((a b) (c (d e)))')).toStrictEqual(expected)
})

test('parse pair', () => {
	expect(p.parse('(a . b)')).toStrictEqual(new Pair(a, b))
})

test('parse quote', () => {
	expect(p.parse("'a")).toStrictEqual(lc.create(q, a))
	expect(p.parse("'()")).toStrictEqual(lc.create(q, nil))
	expect(p.parse("'(a)")).toStrictEqual(lc.create(q, lc.create(a)))
	expect(p.parse("'(a 'b)"))
		.toStrictEqual(lc.create(q, lc.create(a, lc.create(q, b))))
	expect(p.parse("(a 'b c)"))
		.toStrictEqual(lc.create(a, lc.create(q, b), c))
	expect(p.parse("'(a 'b c 'd)"))
		.toStrictEqual(lc.create(q, lc.create(a, lc.create(q, b), c, lc.create(q, d))))
		
})
