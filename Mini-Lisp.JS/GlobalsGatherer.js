module.exports = class GlobalsGatherer {
	constructor() {
		this._globals = []
	}

	getGlobals() {
		return this._globals
	}

	/* Engine Observer */
	globalAdded(globalAtom) {
		this._globals.push(globalAtom.getValue())
	}
}