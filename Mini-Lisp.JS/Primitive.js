module.exports = class Primitive {
	constructor(name, numArgs, closure) {
		this.name = name
		this.numArgs = numArgs
		this.closure = closure
	}

	run(args) {
		const passedArgsLength = args.getListLength()
		if (passedArgsLength === undefined) {
			throw `EVAL: didn't use list form when calling ${this.name}`
		}

		if (passedArgsLength < this.numArgs) {
			`EVAL: too few arguments given to ${this.name}`
		}

		if (passedArgsLength > this.numArgs) {
			`EVAL: too many arguments given to ${this.name}`	
		}

		const firstArg = passedArgsLength >= 1 ? args.car() : undefined
		const secondArg = passedArgsLength >= 2 ? args.cdr().car() : undefined
		return this.closure(firstArg, secondArg)
	}

	isWithName(name) {
		return this.name.eq(name)
	}
}