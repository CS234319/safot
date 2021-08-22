const StackDumpNode = require('./StackDumpNode')

module.exports = class StackDumper {
	constructor() {
		this._stack = []
	}

	push(lambdaName, formals, args, actuals, body, delegate) {
		console.log("push")
		const sdn = new StackDumpNode(lambdaName, formals, args, actuals, body, delegate)
		this._stack.push(sdn)
		console.log(this._stack)
	}

	pop() {
		console.log("pop")
		this._stack.pop()
	}

	dump() {
		console.log("dump")
		console.log(this._stack)
		this._stack.reverse()
		const dumpResult = this._stack.join('\n')
		this._stack = []
		return dumpResult
	}
}