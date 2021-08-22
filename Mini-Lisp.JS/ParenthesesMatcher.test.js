const ParenthesesMatcher = require('./ParenthesesMatcher')
const pm = new ParenthesesMatcher()

const testNoMatch = (text, pos) => {
	expect(pm.match(text, pos)).toBe(undefined)
}

const testMatch = (text, pos, expectedPos) => {
	expect(pm.match(text, pos)).toBe(expectedPos)
}

test('no match', () => {
	testNoMatch('', 0)
	testNoMatch('a', 0)
	testNoMatch('(', 0)
	testNoMatch('(()', 0)
	testNoMatch('((()', 1)
	testNoMatch('(a(b(c)', 2)
	testNoMatch('(()()', 0)
})

test('match open', () => {
	testMatch('()', 0, 1)
	testMatch('(())', 0, 3)
	testMatch('(())', 1, 2)
	testMatch('(())', 0, 3)
	testMatch('(())', 1, 2)
	testMatch('(a(b)c)', 0, 6)
	testMatch('(a(b)c)', 2, 4)
	testMatch('(()())', 0, 5)
	testMatch('(()())', 1, 2)
	testMatch('(()())', 3, 4)
})

test('match close', () => {
	testMatch('()', 1, 0)
	testMatch('(())', 3, 0)
	testMatch('(())', 2, 1)
	testMatch('(())', 3, 0)
	testMatch('(())', 2, 1)
	testMatch('(a(b)c)', 6, 0)
	testMatch('(a(b)c)', 4, 2)
	testMatch('(()())', 5, 0)
	testMatch('(()())', 2, 1)
	testMatch('(()())', 4, 3)
})
