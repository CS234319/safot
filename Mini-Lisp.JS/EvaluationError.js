module.exports = class EvaluationError extends Error {
	constructor(s) {
		super(s.toString())
		this.name = this.constructor.name
		this.s = s
	}
}