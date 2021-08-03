const TestUtils = require('./TestUtils')
const Pair = require('./Pair')
const Atom = require('./Atom')
const p = require('./Parser')

const utils = new TestUtils()

const pair = p.parse('(B . A)')
const list = p.parse('(B A X Y Z)')
const listAsArray = ['B', 'A', 'X', 'Y', 'Z'].map(val => new Atom(val))
const listTail = p.parse('(A X Y Z)')
const complexList = p.parse('((B A X Y Z) (A B C) (B . A))')
const a = p.parse('A')
const b = p.parse('B')
const c = p.parse('C')
const nil = p.parse('NIL')
const t = p.parse('T')

test('atom', () => {	
	expect(a.atom()).toBeTruthy()
	expect(pair.atom()).toBeFalsy()
	expect(list.atom()).toBeFalsy()
	expect(nil.atom()).toBeTruthy()
	expect(t.atom()).toBeTruthy()
})

test('car', () => {	
	utils.expectEquals(pair.car(), b)
	utils.expectEquals(list.car(), b)
	utils.expectException(() => Atom.atom.car(), Atom.atom, Atom.car)
	utils.expectException(() => a.car(), a, Atom.car)
	utils.expectException(() => nil.car(), nil, Atom.car)
})

test('cdr', () => {
	utils.expectEquals(pair.cdr(), a)
	utils.expectEquals(list.cdr(), listTail)
	utils.expectException(() => Atom.atom.cdr(), Atom.atom, Atom.cdr)
	utils.expectException(() => a.cdr(), a, Atom.cdr)
	utils.expectException(() => nil.cdr(), nil, Atom.cdr)
})

test('cons', () => {
	utils.expectEquals(a.cons(p.parse('(b c)')), p.parse('(a b c)'))
	utils.expectEquals(b.cons(nil), p.parse('(b)'))
	utils.expectEquals(a.cons(b), new Pair(a, b))
	utils.expectEquals(pair.cons(c), new Pair(pair, c))
})

test('eq', () => {
	expect(a.eq(a)).toBeTruthy()
	expect(a.eq(b)).toBeFalsy()
	expect(pair.eq(pair)).toBeFalsy()
	expect(list.eq(list)).toBeFalsy()
	expect(nil.eq(nil)).toBeTruthy()
	expect(t.eq(t)).toBeTruthy()
	expect(t.eq(nil)).toBeFalsy()
	expect(nil.eq(t)).toBeFalsy()
})

test('equals', () => {
	expect(a.equals(a)).toBeTruthy()
	expect(a.equals(b)).toBeFalsy()
	expect(pair.equals(pair)).toBeTruthy()
	expect(list.equals(list)).toBeTruthy()
	expect(nil.equals(nil)).toBeTruthy()
	expect(t.equals(t)).toBeTruthy()
	expect(t.equals(nil)).toBeFalsy()
	expect(nil.equals(t)).toBeFalsy()
	expect(p.parse('(a . (b c))').equals(p.parse('(a b c)'))).toBeTruthy()
	expect(p.parse('(a . (b . (c . d)))').equals(
		   p.parse('(a . (b . (c . d)))'))).toBeTruthy()
	expect(p.parse('(a . (b . (c . d)))').equals(
		   p.parse('(a . (b . (c . nil)))'))).toBeFalsy()
})

test('null', () => {
	expect(nil.null()).toBeTruthy()
	expect(t.null()).toBeFalsy()
	expect(pair.null()).toBeFalsy()
	expect(list.null()).toBeFalsy()
})

test('t', () => {
	expect(nil.t()).toBeFalsy()
	expect(t.t()).toBeTruthy()
	expect(pair.t()).toBeTruthy()
	expect(list.t()).toBeTruthy()
})

test('error', () => {
	utils.expectException(() => a.error(), a)
	utils.expectException(() => pair.error(), pair)
	utils.expectException(() => list.error(), list)
	utils.expectException(() => a.error(b), a, b)
	utils.expectException(() => a.error(Atom.invalid), a, Atom.invalid)
})

test('isList', () => {
	expect(nil.isList()).toBeTruthy()
	expect(t.isList()).toBeFalsy()
	expect(a.isList()).toBeFalsy()
	expect(list.isList()).toBeTruthy()
	expect(pair.isList()).toBeFalsy()
})

test('getListAsArray', () => {
	utils.expectEquals(nil.getListAsArray(), [])
	utils.expectEquals(list.getListAsArray(), listAsArray)
	utils.expectEquals(t.getListAsArray(), undefined)
	utils.expectEquals(a.getListAsArray(), undefined)
	utils.expectEquals(pair.getListAsArray(), undefined)
})

test('getListLength', () => {
	utils.expectEquals(nil.getListLength(), 0)
	utils.expectEquals(list.getListLength(), listAsArray.length)
	utils.expectEquals(t.getListLength(), undefined)
	utils.expectEquals(a.getListLength(), undefined)
	utils.expectEquals(pair.getListLength(), undefined)
})

test('toString', () => {
	utils.expectEquals(p.parse(nil.toString()), nil)
	utils.expectEquals(p.parse(t.toString()), t)
	utils.expectEquals(p.parse(a.toString()), a)
	utils.expectEquals(p.parse(pair.toString()), pair)
	utils.expectEquals(p.parse(list.toString()), list)
	utils.expectEquals(p.parse(complexList.toString()), complexList)
})

