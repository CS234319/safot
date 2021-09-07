const TestUtils = require('./TestUtils')
const Pair = require('./Pair')
const Atom = require('./Atom')
const parse = require('./Parser').parse

const utils = new TestUtils()

test('insert', () => {
	const applyTest = (str1, str2, str3) => {
		let pair = parse(str1)
		pair.insert(parse(str2))
		utils.expectEquals(pair, parse(str3))
	}

	applyTest('[a.b]', 'c', '[a.[c.b]]')
	applyTest('(a b)', 'c', '(a c b)')
	applyTest('([a.b] [c.d])', '[e.f]', '([a.b] [e.f] [c.d])')
})
