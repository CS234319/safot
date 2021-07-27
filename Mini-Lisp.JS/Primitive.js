module.exports = class Primitive {
	constructor(name, numArgs, closure) {
		this.name = name
		this.numArgs = numArgs
		this.closure = closure
	}

	run(args) {
		const argsArray = args.getListAsArray()

		if (argsArray === undefined) {
			throw `EVAL: didn't use list form when calling ${this.name}`
		}

		if (this.numArgs) {
			if (argsArray.length < this.numArgs) {
				throw `EVAL: too few arguments given to ${this.name}`
			}

			if (argsArray.length > this.numArgs) {
				throw `EVAL: too many arguments given to ${this.name}`
			}

			return this.closure(...argsArray)
		}

		return this.closure(args)
	}

	isWithName(name) {
		return this.name.eq(name)
	}
}
