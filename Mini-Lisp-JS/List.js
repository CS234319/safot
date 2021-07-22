const Atom = require("./Atom")

module.exports = class List {
	static create() {		
		const args = Array.from(arguments)
		
		if (args.length === 0) {
			return Atom.nil
		}

		const carArg = args[0]
		const cdrArgs = args.slice(1)

		return carArg.cons(this.create(...cdrArgs))
	}	

	static isSameAList(a_list1, a_list2) {
		if (!a_list1.isList() || !a_list2.isList()) {
			return false
		}

		if (a_list1.isNil() && a_list2.isNil()) {
			return true
		}

		if (a_list1.isNil() || a_list2.isNil()) {
			return false
		}

		const first_pair1 = a_list1.car()
		const first_pair2 = a_list2.car()

		return (first_pair1.car().eq(first_pair2.car()) && 
				first_pair1.cdr().eq(first_pair2.cdr()) &&
				this.isSameAList(a_list1.cdr(), a_list2.cdr()))
	}
}
