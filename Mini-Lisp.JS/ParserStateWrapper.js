const parse = require('./Parser').parse
const ParserSyntaxError = require('./Parser').SyntaxError

module.exports = class ParserStateWrapper {
	static Accept = "ACCEPT"
	static ExpectMore = "EXPECT_MORE"
	static Reject = "REJECT"

	parse(str) {
		try {
			return { output: parse(str), type: ParserStateWrapper.Accept }
		} catch (e) {
			if (!(e instanceof ParserSyntaxError)) {
				throw e
			}

			return { 
				output: e.found, 
				type: e.found ? ParserStateWrapper.Reject : ParserStateWrapper.ExpectMore
			}
		}
	}
}