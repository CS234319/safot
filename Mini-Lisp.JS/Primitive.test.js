const TestUtils = require('./TestUtils')
const Primitive = require('./Primitive')
const Atom = require('./Atom')
const parse = require('./Parser').parse

const utils = new TestUtils()

const threeOfTheSame = new Primitive(parse('threeOfTheSame'), 3, (a, b ,c) => {	
	return a.eq(b) && a.eq(c) ? Atom.t : Atom.nil
})

const allOfTheSame = new Primitive(parse('allOfTheSame'), undefined, s => {
	const recurse = (xs, value) => {
		return ((xs.null()) || 
				(xs.car().eq(value) && recurse(xs.cdr(), value)))

	}

	return (s.null() || recurse(s.cdr(), s.car())) ? Atom.t : Atom.nil
})

const expectCallEquals = (primitive, methodStr, argsStr, resStr) => {
	utils.expectEquals(
		Reflect.get(primitive, methodStr).call(primitive, parse(argsStr)),
		parse(resStr)
	)
}
const expectException = (primitive, methodStr, callExpStr, kindStr) => {
	const callExp = parse(callExpStr)

	utils.expectException(
		() => Reflect.get(primitive, methodStr).call(primitive, callExp.cdr()),
		callExp,
		parse(kindStr)
	)
}
const expectNotThrow = (primitive, methodStr, argsStr) => {
	expect(
		() => Reflect.get(primitive, methodStr).call(primitive, parse(argsStr))
	).not.toThrow()
}

test('checkNumberOfArgs', () => {
	expectNotThrow(threeOfTheSame, 'checkNumberOfArgs', '(a a a)')
	expectNotThrow(threeOfTheSame, 'checkNumberOfArgs', '(a b a)')
	
	expectException(threeOfTheSame, 'checkNumberOfArgs', 
		'(threeOfTheSame a a)', 'missing')
	expectException(threeOfTheSame, 'checkNumberOfArgs', 
		'(threeOfTheSame a a a a)', 'redundant')

	expectNotThrow(allOfTheSame, 'checkNumberOfArgs', '(a a a a a)')
	expectNotThrow(allOfTheSame, 'checkNumberOfArgs', '(a a b a)')
	expectNotThrow(allOfTheSame, 'checkNumberOfArgs', '()')
})

test('run', () => {
	expectCallEquals(threeOfTheSame, 'run', '(a a a)', 't')
	expectCallEquals(threeOfTheSame, 'run', '(a b a)', 'nil')
	
	expectException(threeOfTheSame, 'run', '(threeOfTheSame a a)', 'bug')
	expectException(threeOfTheSame, 'run', '(threeOfTheSame a a a a)', 'bug')

	expectCallEquals(allOfTheSame, 'run', '()', 't')
	expectCallEquals(allOfTheSame, 'run', '(a a a a a)', 't')
	expectCallEquals(allOfTheSame, 'run', '(a a b a)', 'nil')
})

test('getName', () => {
	expect(threeOfTheSame.getName().eq(parse('threeOfTheSame'))).toBeTruthy()
	expect(threeOfTheSame.getName().eq(parse('someName'))).toBeFalsy()
	expect(allOfTheSame.getName().eq(parse('allOfTheSame'))).toBeTruthy()
	expect(allOfTheSame.getName().eq(parse('someName'))).toBeFalsy()
})

test('isWithName', () => {
	expect(threeOfTheSame.isWithName(parse('threeOfTheSame'))).toBeTruthy()
	expect(threeOfTheSame.isWithName(parse('someName'))).toBeFalsy()
	expect(allOfTheSame.isWithName(parse('allOfTheSame'))).toBeTruthy()
	expect(allOfTheSame.isWithName(parse('someName'))).toBeFalsy()
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
	expect((new Primitive(Atom.SET)).isNormal()).toBeFalsy()

	expect((new Primitive(Atom.cond)).isNormal()).toBeTruthy()
	expect((new Primitive(Atom.lambda)).isNormal()).toBeTruthy()
	expect((new Primitive(Atom.nlambda)).isNormal()).toBeTruthy()
	expect((new Primitive(Atom.defun)).isNormal()).toBeTruthy()
	expect((new Primitive(Atom.ndefun)).isNormal()).toBeTruthy()
})

test('isEager', () => {
	expect(threeOfTheSame.isEager()).toBeTruthy()
	expect(allOfTheSame.isEager()).toBeTruthy()
	
	expect((new Primitive(Atom.car)).isEager()).toBeTruthy()
	expect((new Primitive(Atom.cdr)).isEager()).toBeTruthy()
	expect((new Primitive(Atom.atom)).isEager()).toBeTruthy()
	expect((new Primitive(Atom.cdr)).isEager()).toBeTruthy()
	expect((new Primitive(Atom.error)).isEager()).toBeTruthy()
	expect((new Primitive(Atom.eval)).isEager()).toBeTruthy()
	expect((new Primitive(Atom.eq)).isEager()).toBeTruthy()
	expect((new Primitive(Atom.SET)).isEager()).toBeTruthy()

	expect((new Primitive(Atom.cond)).isEager()).toBeFalsy()
	expect((new Primitive(Atom.lambda)).isEager()).toBeFalsy()
	expect((new Primitive(Atom.nlambda)).isEager()).toBeFalsy()
	expect((new Primitive(Atom.defun)).isEager()).toBeFalsy()
	expect((new Primitive(Atom.ndefun)).isEager()).toBeFalsy()
})
