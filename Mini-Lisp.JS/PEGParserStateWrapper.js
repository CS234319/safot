module.exports = class PEGParserStateWrapper {
	static Accepted = "ACCEPTED"
	static ExpectedMore = "EXPECTED_MORE"
	static Rejected = "REJECTED"

	constructor(parser) {
		this.parser = parser
	}

	apply(str) {
		try {
			return { output: this.parser.parse(str), type: PEGParserStateWrapper.Accepted }
		} catch (e) {
			if (!(e instanceof this.parser.SyntaxError)) {
				throw e
			}

			const type = e.found === null
				? PEGParserStateWrapper.ExpectedMore
				: PEGParserStateWrapper.Rejected

			return { 
				found: e.found, 
				offset: e.location.start.offset,
				stack: e.stack,
				type: type
			}
		}
	}
}