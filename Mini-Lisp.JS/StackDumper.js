const Atom = require('./Atom')
const config = require('./Configuration').dump

module.exports = class StackDumper {
	constructor(stack) {
		this.stack = stack
	}

	apply(error) {
		error.prependDump(this._dump())
		throw error
	}

	_dump() {
		const { name, args, actuals } = this._extract()
		
		const argsStr = this._getArgsStr(args, actuals)
		return config.pattern
			.replace('{name}', name)
			.replace('{args}', argsStr)
	}

	_extract() {
		this.stack.popUntilReachingRecord()

		if (this.stack.checkTop(Atom.invocation)) {
			const nameAndArgs = this.stack.top()
			this.stack.pop()
			return { 
				name: nameAndArgs.car(),
				args: nameAndArgs.cdr(),
				actuals: Atom.nil
			 }
		} else if (!this.stack.checkTop(Atom.arguments)) {
			this._alist.error(Atom.bug)
		}

		const argsAndActuals = this.stack.top()
		this.stack.popUntilReachingInvocation()
		const name = this.stack.top().car()
		this.stack.pop()

		return {
			name: name,
			args: argsAndActuals.car(),
			actuals: argsAndActuals.cdr()
		}
	}

	_getArgsStr(args, actuals) {
		let array = actuals.getListAsArray()

		const argsArray = args.getListAsArray()
		const argsLength = argsArray?.length ?? 0
		if (argsLength !== 0) {
			argsArray[0] = config.args.failedPrefix + argsArray[0].toString()
			array = array.concat(argsArray)
		} 

		return array.join(config.args.delim)
	}
}
