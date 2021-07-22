const Pair = require("./Pair")
const Atom = require("./Atom")
const ListCreator = require("./ListCreator")

const lc = new ListCreator()
const pair_as_array = ["b", "a"].map(val => new Atom(val))
const pair = new Pair(...pair_as_array)
const list_as_array = ["b", "a", "x", "y", "z"].map(val => new Atom(val))
const list = lc.create(...list_as_array)
const list_tail = lc.create(...list_as_array.slice(1))
const a = new Atom("a")
const b = new Atom("b")
const c = new Atom("c")
const complex_list = lc.create(list, lc.create(a, b, c), pair)
const nil = Atom.nil
const t = Atom.t

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
	expect(a.cons(lc.create(b, c))).toStrictEqual(lc.create(a, b, c))
	expect(b.cons(nil)).toStrictEqual(lc.create(b))
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

test('equal', () => {
	expect(a.equal(a)).toBeTruthy()
	expect(a.eq(b)).toBeFalsy()
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
	expect(complex_list.toString()).toBe("((b a x y z) (a b c) (b . a))")
})
