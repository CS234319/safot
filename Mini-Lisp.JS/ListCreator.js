const Atom = require("./Atom")

module.exports = class ListCreator {
	create() {		
		const args = Array.from(arguments)
		
		if (args.length === 0) {
			return Atom.nil
		}

		const carArg = args[0]
		const cdrArgs = args.slice(1)

		return carArg.cons(this.create(...cdrArgs))
	}	
}
