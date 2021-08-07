const EvaluationError = require('./EvaluationError')
const S = require('./S')
const parse = require('./Parser').parse

module.exports = class TestUtils {
	expectException(f, s, kind) {
		expect(f).toThrow(new EvaluationError(kind ? s.cons(kind) : s))	
	}	

	parseExpectException(f, str, kindStr) {
		this.expectException(f, parse(str), parse(kindStr))
	}

	expectEquals(s, t) {
		if ((s instanceof S) && (t instanceof S)) {
			expect(s.equals(t)).toBeTruthy()	
		} else {
			expect(s).toStrictEqual(t)
		}
	}

	parseExpectEquals(str, s) {
		this.expectEquals(parse(str), s)
	}
}

