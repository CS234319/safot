const p = require('./Parser')

module.exports = class ParserStateWrapper {
	static Accept = "ACCEPT"
	static ExpectMore = "EXPECT_MORE"
	static Reject = "REJECT"

	parse(str) {
		try {
			return { output: p.parse(str), type: ParserStateWrapper.Accept }
		} catch (e) {
			if (!(e instanceof p.SyntaxError)) {
				throw e
			}

			return { 
				output: e.found, 
				type: e.found ? ParserStateWrapper.Reject : ParserStateWrapper.ExpectMore
			}
		}
	}
}