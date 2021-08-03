const EvaluationError = require('./EvaluationError')
const S = require('./S')

module.exports = class TestUtils {
	expectException(f, s, kind) {
		expect(f).toThrow(new EvaluationError(kind ? s.cons(kind) : s))	
	}	

	expectEquals(s, t) {
		if ((s instanceof S) && (t instanceof S)) {
			expect(s.equals(t)).toBeTruthy()	
		} else {
			expect(s).toStrictEqual(t)
		}
	}
}

