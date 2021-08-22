module.exports = class StackDumpNode {
	constructor(functionName, formals, args, actuals, body, delegate) {
		this._functionName = functionName
		this._formals = formals
		this._args = args
		this._actuals = actuals
		this._body = body
		this._delegate = delegate
	}

	toString() {
		return `Function name: ${this._functionName}\n` +
				`Function body: ${this._body}\n` +
				`Formals:\n` +
				`\tBefore:\n` +
				`${StackDumpNode._formalsToString(this._formals, this._args)}\n` +
				`\tAfter:\n` +
				`${StackDumpNode._formalsToString(this._formals, this._actuals)}\n`

	}

	static _formalsToString(formals, passed) {
		if (formals.null() && passed.null()) {
			return ''
		}

		return `\t\t${formals.car()} = ${passed.car()}\n` +
	 			StackDumpNode._formalsToString(
	 				formals.cdr(),
	 				passed.cdr()
	 			)
	}
}