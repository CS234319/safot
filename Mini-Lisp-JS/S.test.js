const Pair = require("./Pair")
const Atom = require("./Atom")
const List = require("./List")

const pair_as_array = ["b", "a"].map(val => new Atom(val))
const pair = new Pair(...pair_as_array)
const pair_copy = pair.deepCopy()
const list_as_array = ["b", "a", "x", "y", "z"].map(val => new Atom(val))
const list = List.create(...list_as_array)
const list_copy = list.deepCopy()
const list_tail = List.create(...list_as_array.slice(1))
const a = new Atom("a")
const b = new Atom("b")
const c = new Atom("c")
const a_copy = a.deepCopy()
const nil = Atom.nil
const t = Atom.t

test('deepCopy', () => {	
	expect(a).toStrictEqual(a_copy)
	expect(pair).toStrictEqual(pair_copy)
	expect(list).toStrictEqual(list_copy)
})

test('atom', () => {	
	expect(a.isAtom()).toBeTruthy()
	expect(pair.isAtom()).toBeFalsy()
	expect(list.isAtom()).toBeFalsy()
	expect(nil.isAtom()).toBeTruthy()
	expect(t.isAtom()).toBeTruthy()
})

test('car', () => {	
	expect(nil.car()).toStrictEqual(nil)
	expect(pair.car()).toStrictEqual(b)
	expect(list.car()).toStrictEqual(b)
	expect((new Pair(pair, a)).car()).toBe(pair)
	expect((new Pair(pair_copy, a)).car()).not.toBe(pair)
	expect((new Pair(list, a)).car()).toBe(list)
	expect((new Pair(list_copy, a)).car()).not.toBe(list)
})

test('cdr', () => {
	expect(nil.cdr()).toStrictEqual(nil)
	expect(pair.cdr()).toStrictEqual(a)
	expect(list.cdr()).toStrictEqual(list_tail)
	expect((new Pair(a, pair).cdr())).toBe(pair)
	expect((new Pair(a, pair_copy).cdr())).not.toBe(pair)
	expect((new Pair(a, list)).cdr()).toBe(list)
	expect((new Pair(a, list_copy)).cdr()).not.toBe(list)
})

test('cons', () => {
	expect(a.cons(List.create(b, c))).toStrictEqual(List.create(a, b, c))
	expect(b.cons(nil)).toStrictEqual(List.create(b))
	expect(a.cons(b)).toStrictEqual(new Pair(a, b))
	expect(pair.cons(c)).toStrictEqual(new Pair(pair, c))
})

test('eq', () => {
	expect(a.eq(a)).toBeTruthy()
	expect(a.eq(b)).toBeFalsy()
	expect(pair.eq(pair)).toBeTruthy()
	expect(pair.eq(pair_copy)).toBeFalsy()
	expect(list.eq(list)).toBeTruthy()
	expect(list.eq(list_copy)).toBeFalsy()
	expect(nil.eq(nil)).toBeTruthy()
	expect(t.eq(t)).toBeTruthy()
	expect(t.eq(nil)).toBeFalsy()
	expect(nil.eq(t)).toBeFalsy()
})

test('isNil', () => {
	expect(nil.isNil()).toBeTruthy()
	expect(t.isNil()).toBeFalsy()
	expect(pair.isNil()).toBeFalsy()
	expect(list.isNil()).toBeFalsy()
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
	expect(t.getListAsArray()).toBe(null)
	expect(a.getListAsArray()).toBe(null)
	expect(pair.getListAsArray()).toStrictEqual(null)
})

test('toString', () => {
	expect(nil.toString()).toBe("NIL")
	expect(t.toString()).toBe("T")
	expect(a.toString()).toBe("a")
	expect(pair.toString()).toBe("(b . a)")
	expect(list.toString()).toBe("(b a x y z)")
})
