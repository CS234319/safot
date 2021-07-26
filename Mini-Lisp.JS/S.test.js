const Pair = require('./Pair')
const Atom = require('./Atom')
const p = require('./Parser')

const pair = p.parse('(B . A)')
const list = p.parse('(B A X Y Z)')
const list_as_array = ['B', 'A', 'X', 'Y', 'Z'].map(val => new Atom(val))
const list_tail = p.parse('(A X Y Z)')
const complex_list = p.parse('((B A X Y Z) (A B C) (B . A))')
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
	expect(pair.car()).toStrictEqual(b)
	expect(list.car()).toStrictEqual(b)
	expect((new Pair(pair, a)).car()).toBe(pair)
	expect((new Pair(list, a)).car()).toBe(list)
})

test('cdr', () => {
	expect(pair.cdr()).toStrictEqual(a)
	expect(list.cdr()).toStrictEqual(list_tail)
	expect((new Pair(a, pair).cdr())).toBe(pair)
	expect((new Pair(a, list)).cdr()).toBe(list)
})

test('cons', () => {
	expect(a.cons(p.parse('(b c)'))).toStrictEqual(p.parse('(a b c)'))
	expect(b.cons(nil)).toStrictEqual(p.parse('(b)'))
	expect(a.cons(b)).toStrictEqual(new Pair(a, b))
	expect(pair.cons(c)).toStrictEqual(new Pair(pair, c))
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

test('null', () => {
	expect(nil.null()).toBeTruthy()
	expect(t.null()).toBeFalsy()
	expect(pair.null()).toBeFalsy()
	expect(list.null()).toBeFalsy()
})

test('isList', () => {
	expect(nil.isList()).toBeTruthy()
	expect(t.isList()).toBeFalsy()
	expect(a.isList()).toBeFalsy()
	expect(list.isList()).toBeTruthy()
	expect(pair.isList()).toBeFalsy()
})

test('getListAsArray', () => {
	expect(nil.getListAsArray()).toStrictEqual([])
	expect(list.getListAsArray()).toStrictEqual(list_as_array)
	expect(t.getListAsArray()).toStrictEqual(undefined)
	expect(a.getListAsArray()).toStrictEqual(undefined)
	expect(pair.getListAsArray()).toStrictEqual(undefined)
})

test('getListLength', () => {
	expect(nil.getListLength()).toStrictEqual(0)
	expect(list.getListLength()).toStrictEqual(list_as_array.length)
	expect(t.getListLength()).toStrictEqual(undefined)
	expect(a.getListLength()).toStrictEqual(undefined)
	expect(pair.getListLength()).toStrictEqual(undefined)
})

test('toString', () => {
	expect(p.parse(nil.toString())).toStrictEqual(nil)
	expect(p.parse(t.toString())).toStrictEqual(t)
	expect(p.parse(a.toString())).toStrictEqual(a)
	expect(p.parse(pair.toString())).toStrictEqual(pair)
	expect(p.parse(list.toString())).toStrictEqual(list)
	expect(p.parse(complex_list.toString())).toStrictEqual(complex_list)
})

