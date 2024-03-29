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
	const lastIndex = this.findLastIndex(fn)
	return lastIndex > 0 ? this[lastIndex - 1] : undefined
}

Array.prototype.distinct = function() {
	return this.reduce((input, c) => {
		return input.includes(c) ? input : input.append(c)
	}, [])
}

Array.range = function(n) {
	return [...Array(n).keys()]
}

Array.zip = function(array1, array2) {
	return array1.slice(0, array2.length).map((e, i) => [e, array2[i]])
}
