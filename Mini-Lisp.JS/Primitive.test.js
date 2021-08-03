const TestUtils = require('./TestUtils')
const Primitive = require('./Primitive')
const Atom = require('./Atom')
const p = require('./Parser')

const utils = new TestUtils()

const b = p.parse('b')
const t = p.parse('t')
const nil = p.parse('nil')

const threeOfTheSame = new Primitive(p.parse('threeOfTheSame'), 3, (a, b ,c) => {	
	return a.eq(b) && a.eq(c) ? t : nil
})

const allOfTheSame = new Primitive(p.parse('allOfTheSame'), undefined, s => {
	const recurse = (xs, value) => {
		return ((xs.null()) || 
				(xs.car().eq(value) && recurse(xs.cdr(), value)))

	}

	return (s.null() || recurse(s.cdr(), s.car())) ? t : nil
})

test('checkNumberOfArgs', () => {
	s = p.parse('(a a a)')
	expect(() => threeOfTheSame.checkNumberOfArgs(s)).not.toThrow(s)

	s = p.parse('(a b a)')
	expect(() => threeOfTheSame.checkNumberOfArgs(s)).not.toThrow()

	s = p.parse('(threeOfTheSame a a)')
	utils.expectException(() => threeOfTheSame.checkNumberOfArgs(s.cdr()), s, Atom.missing)

	s = p.parse('(threeOfTheSame a a a a)')
	utils.expectException(() => threeOfTheSame.checkNumberOfArgs(s.cdr()), s, Atom.redundant)

	s = p.parse("(a a a a a)")
	expect(() => allOfTheSame.checkNumberOfArgs(s)).not.toThrow()

	s = p.parse("(a a b a)")
	expect(() => allOfTheSame.checkNumberOfArgs(s)).not.toThrow()

	s = p.parse("()")
	expect(() => allOfTheSame.checkNumberOfArgs(s)).not.toThrow()

	s = p.parse("(allOfTheSame . a)")
	utils.expectException(() => allOfTheSame.checkNumberOfArgs(s.cdr()), s, Atom.invalid)
})

test('run', () => {
	s = p.parse('(a a a)')
	expect(threeOfTheSame.run(s)).toStrictEqual(t)

	s = p.parse('(a b a)')
	expect(threeOfTheSame.run(s)).toStrictEqual(nil)
	
	s = p.parse('(threeOfTheSame a a)')
	utils.expectException(() => threeOfTheSame.run(s.cdr()), s, Atom.bug)

	s = p.parse('(threeOfTheSame a a a a)')
	utils.expectException(() => threeOfTheSame.run(s.cdr()), s, Atom.bug)

	s = p.parse("()")
	expect(allOfTheSame.run(s)).toStrictEqual(t)

	s = p.parse("()")
	expect(allOfTheSame.run(s)).toStrictEqual(t)

	s = p.parse("(a a a a a)")
	expect(allOfTheSame.run(s)).toStrictEqual(t)

	s = p.parse("(a a b a)")
	expect(allOfTheSame.run(s)).toStrictEqual(nil)
})

test('isWithName', () => {
	expect(threeOfTheSame.isWithName(p.parse('threeOfTheSame'))).toBeTruthy()
	expect(threeOfTheSame.isWithName(p.parse('someName'))).toBeFalsy()
	expect(allOfTheSame.isWithName(p.parse('allOfTheSame'))).toBeTruthy()
	expect(allOfTheSame.isWithName(p.parse('someName'))).toBeFalsy()
})

test('isNormal', () => {
	expect(threeOfTheSame.isNormal()).toBeFalsy()
	expect(allOfTheSame.isNormal()).toBeFalsy()
	
	expect((new Primitive(Atom.car)).isNormal()).toBeFalsy()
	expect((new Primitive(Atom.cdr)).isNormal()).toBeFalsy()
	expect((new Primitive(Atom.atom)).isNormal()).toBeFalsy()
	expect((new Primitive(Atom.cdr)).isNormal()).toBeFalsy()
	expect((new Primitive(Atom.error)).isNormal()).toBeFalsy()
	expect((new Primitive(Atom.eval)).isNormal()).toBeFalsy()
	expect((new Primitive(Atom.eq)).isNormal()).toBeFalsy()
	expect((new Primitive(Atom.set)).isNormal()).toBeFalsy()

	expect((new Primitive(Atom.cond)).isNormal()).toBeTruthy()
	expect((new Primitive(Atom.quote)).isNormal()).toBeTruthy()
	expect((new Primitive(Atom.lambda)).isNormal()).toBeTruthy()
	expect((new Primitive(Atom.nlambda)).isNormal()).toBeTruthy()
	expect((new Primitive(Atom.defun)).isNormal()).toBeTruthy()
	expect((new Primitive(Atom.ndefun)).isNormal()).toBeTruthy()
})
