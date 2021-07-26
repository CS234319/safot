const Primitive = require('./Primitive')
const p = require('./Parser')

const b = p.parse('b')
const t = p.parse('t')
const nil = p.parse('nil')

const three_of_the_same = new Primitive(p.parse('three_of_the_same'), 3, function(a, b ,c) {	
	return a.eq(b) && a.eq(c) ? t : nil
})

const exists = new Primitive(p.parse('exists'), 2, function(x, xs) {
	const arrayList = xs.getListAsArray()
	
	for (elem of arrayList) {
		if (elem.eq(x)) {
			return t
		}
	}

	return nil
})

test('run', () => {
	expect(three_of_the_same.run(p.parse('(a a a)'))).toStrictEqual(t)
	expect(three_of_the_same.run(p.parse('(a b a)'))).toStrictEqual(nil)
	expect(exists.run(p.parse('(a (b a))'))).toStrictEqual(t)
	expect(exists.run(p.parse('(c (b a))'))).toStrictEqual(nil)
})

test('isWithName', () => {
	expect(three_of_the_same.isWithName(p.parse('three_of_the_same'))).toBeTruthy()
	expect(three_of_the_same.isWithName(p.parse('some_name'))).toBeFalsy()
	expect(exists.isWithName(p.parse('exists'))).toBeTruthy()
	expect(exists.isWithName(p.parse('some_name'))).toBeFalsy()
})
