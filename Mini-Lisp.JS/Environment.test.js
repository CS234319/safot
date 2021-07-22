const Atom = require('./Atom')
const Pair = require('./Pair')
const Environment = require('./Environment')
const ListCreator = require('./ListCreator')

const lc = new ListCreator()
const t = Atom.t
const nil = Atom.nil
const a = new Atom("a")
const b = new Atom("b")
const pair = Pair.ofAtoms("b", "a")
const list = lc.createAsAtoms("b", "a", "x", "y", "z")

test('set', () => {	
	const env = new Environment()
	
	var a_list = env.aList()
	var expected_list = lc.create(t.cons(t), nil.cons(nil))
	expect(a_list).toStrictEqual(expected_list)
	
	expect(env.set(a, pair)).toStrictEqual(pair)
	a_list = env.aList()
	expected_list = a.cons(pair).cons(expected_list)
	expect(a_list).toStrictEqual(expected_list)

	expect(env.set(b, list)).toStrictEqual(list)
	a_list = env.aList()
	expected_list = b.cons(list).cons(expected_list)
	expect(a_list).toStrictEqual(expected_list)
})
