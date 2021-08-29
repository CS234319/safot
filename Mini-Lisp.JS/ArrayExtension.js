Array.prototype.append = function(element) {
	return this.concat([element])
}

Array.prototype.prepend = function(element) {
	return [element].concat(this)
}

Array.prototype.reversed = function() {
	return this.reduce((input, e) => input.prepend(e), [])
}

Array.prototype.findLastIndex = function(fn) {
	const indexOfReversed = this.reversed().findIndex(fn)
	return indexOfReversed !== -1 
		? this.length - 1 - indexOfReversed 
		: -1
}

Array.prototype.findSecondLast = function(fn) {
	const lastIndex = this.findLastIndex(s => s.didMatchParentheses)
	return lastIndex > 0 ? this[lastIndex - 1] : undefined
}

Array.prototype.filterNullish = function() {
	return this.filter(e => ![undefined, null].includes(e))
}